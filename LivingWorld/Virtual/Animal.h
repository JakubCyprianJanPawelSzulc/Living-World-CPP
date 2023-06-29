#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
    Animal(Position position);
    void move(int dx, int dy);
    Organism* resultOfFight(Organism* org1, Organism* org2);
    virtual Animal* clone(Position position) = 0;
    bool isToxic();
};
