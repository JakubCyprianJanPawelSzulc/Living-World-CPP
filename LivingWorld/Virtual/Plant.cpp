#include <iostream>
#include "Plant.h"

Plant::Plant(Position position) : Organism(position) {
    setSpecies("P");
}

void Plant::move(int dx, int dy) {
    Organism::move(0, 0);
}

bool Plant::isToxic() {
    return false;
}

Organism* Plant::resultOfFight(Organism* org1, Organism* org2) {
    return nullptr;
}
