#include "Sheep.h"

Sheep::Sheep(Position position) : Animal(position)
{
    setSpecies("S");
    setPower(4);
    setPowerToReproduce(6);
    setLifeTime(12);
}

Sheep* Sheep::clone(Position position)
{
    Sheep* sheep = new Sheep(position);
    sheep->setAncestors(getAncestors());
    return sheep;
}