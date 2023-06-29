#include "Utils/Position.h"
#include "Virtual/Animal.h"

class Sheep : public Animal{
public:
    Sheep(Position position);
    Sheep* clone(Position position);
};

