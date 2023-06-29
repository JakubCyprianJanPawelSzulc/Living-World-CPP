#include "Utils/Position.h"
#include "Virtual/Plant.h"

class Toadstool : public Plant {
    public: 
        Toadstool(Position position);
        Toadstool* clone(Position position);
        bool isToxic();
};