#include "Wolf.h"

Wolf::Wolf(Position position) : Animal(position)
{
    setSpecies("W");
    setPower(9);
    setPowerToReproduce(10);
    setLifeTime(14);
}

Wolf* Wolf::clone(Position position)
{
    Wolf* wolf = new Wolf(position);
    wolf->setAncestors(getAncestors());
    return wolf;
}

