#include <algorithm>
#include <iostream>
#include <cmath>
#include "World.h"

World::World(int width, int height) {
    setWidth(width);
    setHeight(height);
}

int World::getWidth() {
    return this->width;
}

void World::setWidth(int width) {
    this->width = width;
}

int World::getHeight() {
    return this->height;
}

void World::setHeight(int height) {
    this->height = height;
}

int World::getTurn() {
    return this->turn;
}

void World::addOrganism(Organism* organism) {
    organism->setBorn(getTurn());
    organisms.push_back(organism);
}

bool World::isPositionOnWorld(int x, int y) {
    return (x >= 0 && y >= 0 && x < getWidth() && y < getHeight());
}

bool World::isPositionFree(Position position) {
    return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

string World::getOrganismFromPosition(int x, int y) {
    for (Organism *org: organisms)
        if (org->getPosition().getX() == x && org->getPosition().getY() == y)
            return org->getSpecies();
    return "";
}

vector<Position> World::filterPositionFromBorn(vector<Position> freePositions, vector<Organism *> newOrganisms) {
    for (auto &newOrg: newOrganisms) {
        auto iter = remove_if(freePositions.begin(), freePositions.end(),
                              [newOrg](Position pos) {
                                  return pos.getX() == newOrg->getPosition().getX() &&
                                         pos.getY() == newOrg->getPosition().getY();
                              });
        freePositions.erase(iter, freePositions.end());
    }

    return freePositions;
}

vector<Position> World::getFreePositionsAround(Position position) {
    int pos_x = position.getX();
    int pos_y = position.getY();
    std::vector<Position> result;

    for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
            if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y) && isPositionFree(Position(pos_x + x, pos_y + y))) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
        }
    }

    return result;
}


vector<Position> World::getAdjacentOrganisms(Position position) {
    int pos_x = position.getX(), pos_y = position.getY();
    vector<Position> result;
    for (int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) &&
                isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
    auto iter = remove_if(result.begin(), result.end(),
                          [this](Position pos) { return getOrganismFromPosition(pos.getX(), pos.getY()).empty(); });
    result.erase(iter, result.end());
    return result;
}

string World::drawWorld() {
    std::string result = "\ntura: " + std::to_string(getTurn()) + "\n";

    for (int wY = 0; wY < getHeight(); ++wY) {
        for (int wX = 0; wX < getWidth(); ++wX) {
            std::string spec = getOrganismFromPosition(wX, wY);
            result += (spec.empty() ? "." : spec);
        }
        result += "\n";
    }

    return result;
}


void World::makeTurn() {
    vector<Position> freePositions;
    int numberOfPositions;
    int randomIdx;
    vector<Organism *> newOrganisms;

    srand(time(NULL));
    for (auto it = organisms.begin(); it != organisms.end();) {
        auto &org = *it;

        if (org == nullptr) {
            ++it;
            continue;
        }

        org->setPower(org->getPower() + 1);

        if (org->getLifeTime()<= 0) {
            cout << org->getSpecies() << org->getPosition().toString() << " umarl ze starosci" << endl;
            for(Organism *organism : organisms){
                if(organism->getSpecies() == org->getSpecies()){
                    organism->addAncestor(org->getBorn(), turn);
                }
            }
            it = organisms.erase(it);
        } else {
            org->setLifeTime(org->getLifeTime() - 1);
            ++it;
        }

        int action;
        bool canMove = false;
        bool canReproduce = false;
        bool canFight = false;

        freePositions = getFreePositionsAround(org->getPosition());
        freePositions = filterPositionFromBorn(freePositions, newOrganisms);
        numberOfPositions = freePositions.size();
        if (numberOfPositions > 0) {
            canMove = true;
        }

        if (org->getPower() >= org->getPowerToReproduce()) {
            freePositions = getFreePositionsAround(org->getPosition());
            freePositions = filterPositionFromBorn(freePositions, newOrganisms);
            numberOfPositions = freePositions.size();
            if (numberOfPositions > 0) {
                canReproduce = true;
            }
        }

        vector<Position> adjacentOrganisms = getAdjacentOrganisms(org->getPosition());
        adjacentOrganisms = filterSpecies(adjacentOrganisms, org->getSpecies());
        int numberOfAdjacentOrganisms = adjacentOrganisms.size();
        if (numberOfAdjacentOrganisms > 0) {
            canFight = true;
        }

        if (!canMove && !canReproduce && !canFight) {
            continue;
        } else if (canMove && canReproduce && canFight) {
            action = rand() % 3;
        } else if (canMove && canReproduce) {
            action = rand() % 2;
        } else if (canMove && canFight) {
            action = (rand() % 2 == 0) ? 0 : 2;
        } else if (canReproduce && canFight) {
            action = (rand() % 2 == 0) ? 1 : 2;
        } else if (canMove) {
            action = 0;
        } else if (canReproduce) {
            action = 1;
        } else {
            action = 2;
        }

        if (action == 0 && canMove) {
            numberOfPositions = freePositions.size();
            randomIdx = rand() % numberOfPositions;
            org->move(freePositions[randomIdx].getX() - org->getPosition().getX(),
                      freePositions[randomIdx].getY() - org->getPosition().getY());
        } else if (action == 1 && canReproduce) {
            numberOfPositions = freePositions.size();
            randomIdx = rand() % freePositions.size();
            cout << org->getSpecies() << " urodzil sie w " << freePositions[randomIdx].toString() << endl;
            Organism *newOrg = org->clone(freePositions[randomIdx]);
            newOrganisms.push_back(newOrg);
            org->setPower(org->getPower() / 2);
        } else if (action == 2 && canFight) {
            Organism *orgToFight = getWeakestAdjacentOrganism(org->getPosition(), org->getSpecies());
            Organism *winner = org->resultOfFight(org, orgToFight);
            if (winner != nullptr) {
                if (org != winner) {
                    cout << orgToFight->getSpecies() << " pokonal " << org->getSpecies() << endl;
                } else {
                    cout << org->getSpecies() << " pokonal " << orgToFight->getSpecies() << endl;
                }
                if (orgToFight->isToxic()) {
                    cout << org->getSpecies() << " zostal zatruty" << endl;
                    org->setLifeTime(2);
                    org->setPower(0);
                }

                Organism *defeated = (org == winner) ? orgToFight : org;

                for(Organism *org : organisms){
                    if(org->getSpecies() == defeated->getSpecies()){
                        org->addAncestor(defeated->getBorn(), turn);
                    }
                }
                // delete defeated;
                organisms.erase(remove(organisms.begin(), organisms.end(), defeated), organisms.end());
            }
        }
    }

    for (Organism *org: newOrganisms){
        org->setBorn(getTurn());
    }

    for (Organism *org: organisms){
       cout<<org->toString()<<endl;
    }
    organisms.insert(organisms.end(), newOrganisms.begin(), newOrganisms.end());
    turn++;
}


Organism* World::getOrganismFromPosition(Position position){
    for (Organism *org: organisms)
        if (org->getPosition().getX() == position.getX() && org->getPosition().getY() == position.getY())
            return org;
    return nullptr;
}

vector<Position> World::filterSpecies(vector<Position> positions, string species) {
    auto iter = remove_if(positions.begin(), positions.end(), [this, species](Position pos) {
        Organism* organism = getOrganismFromPosition(pos);
        return organism != nullptr && organism->getSpecies() == species;
    });
    positions.erase(iter, positions.end());
    return positions;
}


Organism* World::getWeakestAdjacentOrganism(Position position, string species) {
    vector<Position> adjacentOrganisms = getAdjacentOrganisms(position);
    adjacentOrganisms = filterSpecies(adjacentOrganisms, species);
    int numberOfAdjacentOrganisms = adjacentOrganisms.size();
    if (numberOfAdjacentOrganisms == 0) {
        return nullptr;
    }

    Organism *weakest = getOrganismFromPosition(adjacentOrganisms[0]);
    for (int i = 1; i < numberOfAdjacentOrganisms; ++i) {
        Organism *org = getOrganismFromPosition(adjacentOrganisms[i]);
        if (org->getPower() < weakest->getPower()) {
            weakest = org;
        }
    }
    return weakest;
}



