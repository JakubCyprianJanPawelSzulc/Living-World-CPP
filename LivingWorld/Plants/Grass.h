#include "Utils/Position.h"
#include "Virtual/Plant.h"

class Grass : public Plant{
public:
    Grass(Position position);
    Grass* clone(Position position);
};

