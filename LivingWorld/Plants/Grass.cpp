#include "Grass.h"

Grass::Grass(Position position) : Plant(position)
{
    setSpecies("G");
    setPower(0);
    setPowerToReproduce(3);
    setLifeTime(6);
}

Grass* Grass::clone(Position position)
{
    Grass* grass = new Grass(position);
    grass->setAncestors(getAncestors());
    return grass;
}