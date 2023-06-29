#include <iostream>
#include "Animal.h"

Animal::Animal(Position position) : Organism(position) {
    setSpecies("P");
}

void Animal::move(int dx, int dy) {
    Organism::move(dx, dy);
}

Organism* Animal::resultOfFight(Organism* entity1, Organism* entity2){
	if(entity1->getPower() > entity2->getPower()){
		return entity1;
	}
	else{
		return entity2;
	}
}

bool Animal::isToxic() {
    return false;
}
