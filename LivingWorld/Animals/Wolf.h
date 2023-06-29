#include "Utils/Position.h"
#include "Virtual/Animal.h"

class Wolf : public Animal{
public:
    Wolf(Position position);
    Wolf* clone(Position position);
};

