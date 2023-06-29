#include "Utils/Position.h"
#include "Virtual/Plant.h"

class Dandelion : public Plant{
public:
    Dandelion(Position position);
    Dandelion* clone(Position position);
};

