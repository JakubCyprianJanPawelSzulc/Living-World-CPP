#include <iostream>
#include <memory>
#include "Utils/World.h"
#include "Plants/Grass.h"
#include "Plants/Dandelion.h"
#include "Plants/Toadstool.h"
#include "Animals/Sheep.h"
#include "Animals/Wolf.h"

void runSimulation() {
    std::unique_ptr<World> world = std::make_unique<World>(8, 8);

    std::shared_ptr<Grass> grass = std::make_shared<Grass>(Position(4, 0));
    std::shared_ptr<Dandelion> dandelion = std::make_shared<Dandelion>(Position(0, 0));
    std::shared_ptr<Toadstool> toadstool = std::make_shared<Toadstool>(Position(0, 4));
    std::shared_ptr<Wolf> wolf = std::make_shared<Wolf>(Position(7, 7));
    std::shared_ptr<Sheep> sheep = std::make_shared<Sheep>(Position(4, 4));

    world->addOrganism(grass.get());
    world->addOrganism(dandelion.get());
    world->addOrganism(toadstool.get());
    world->addOrganism(sheep.get());
    world->addOrganism(wolf.get());

    std::cout << world->drawWorld();

    for (int i = 0; i < 20; i++) {
        std::cin.ignore();
        world->makeTurn();
        std::cout << world->drawWorld();
    }
}

int main() {
    runSimulation();

    char choice;
    do {
        std::cout << "Czy chcesz uruchomić symulację ponownie? (T/N): ";
        std::cin >> choice;

        if (choice == 'T' || choice == 't') {
            runSimulation();
        }
    } while (choice == 'T' || choice == 't');

    return 0;
}
