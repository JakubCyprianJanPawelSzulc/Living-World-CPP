#pragma once

#include <string>
#include <array>
#include "Utils/Position.h"

using namespace std;

class Organism {
private:
    int power;
    Position position;
    string species;
    int powerToReproduce;
    int lifeTime;
    int born = 0;
    array<array<int, 2>, 500> ancestors = {};


public:
    Organism(Position position);
    int getBorn();
    void setBorn(int born);
    string getSpecies();
    void setSpecies(string spec);
    Position getPosition();
    void setPosition(Position position);
    int getPower();
    void setPower(int power);
    int getPowerToReproduce();
    void setPowerToReproduce(int powerToReproduce);
    int getLifeTime();
    void setLifeTime(int lifeTime);
    string toString();
    virtual void move(int dx, int dy) = 0;
    virtual Organism* clone(Position position) = 0;
    virtual Organism* resultOfFight(Organism* org1, Organism* org2) = 0;
    virtual bool isToxic() = 0;
    array<array<int, 2>, 500> getAncestors();
    void setAncestors(array<array<int, 2>, 500> ancestors);
    string printAncestors();
    void addAncestor(int born, int died);
    ~Organism();
};
