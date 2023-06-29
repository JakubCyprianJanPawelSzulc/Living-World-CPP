#pragma once
#include <vector>
#include <ctime>
#include "Virtual/Organism.h"

using namespace std;

class World
{
private:
	int width;
	int height;
	int turn = 0;
	vector<Organism *> organisms;
	bool isPositionOnWorld(int x, int y);
	bool isPositionFree(Position position);
	string getOrganismFromPosition(int x, int y);

public:
	World(int width, int height);
	World() : World(10, 10) {};
	void setWidth(int width);
	void setHeight(int height);
	int getWidth();
	int getHeight();
	void addOrganism(Organism *organism);
	int getTurn();
	vector<Position> filterPositionFromBorn(vector<Position> freePositions, vector<Organism *> newOrganisms);
	vector<Position> getFreePositionsAround(Position position);
	vector<Position> getAdjacentOrganisms(Position position);
	Organism* getOrganismFromPosition(Position position);
	void makeTurn();
	string drawWorld();
	vector<Position> filterSpecies(vector<Position> freePositions, string species);
	Organism* getWeakestAdjacentOrganism(Position position, string species);
};

