#include "Toadstool.h"

Toadstool::Toadstool(Position position) : Plant(position)
{
    setSpecies("T");
    setPower(1);
    setPowerToReproduce(3);
    setLifeTime(5);
}

Toadstool* Toadstool::clone(Position position)
{
    Toadstool* toadstool = new Toadstool(position);
    toadstool->setAncestors(getAncestors());
    return toadstool;
}

bool Toadstool::isToxic() {
    return true;
}