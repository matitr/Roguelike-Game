#pragma once
#include <list>
#include <stack>
#include <vector>
#include "SDL.h"

class Map;
class Unit;
class Field;

class Movement {
protected:
	Unit * unitToMove;
public:
	virtual void makeMove() = 0;
	virtual void resetMove() {}

	Movement(Unit* unitToMove);
	virtual ~Movement();
};

class A_Star {
	std::list<Field*> openSet; // Fields to check
	std::list<Field*> closedSet; // Fields already checked
	Field* start;
	Field* end;
	Map* map;
	Unit* player;
	Unit* unitToMove;

	void createNeighbors(Field*, std::stack<Field*>&); // Create neighbors from field
	double distance(int x1, int y1, int x2, int y2);
	void getVelocityOfPath(Field*, Field* start);
public:
	SDL_Point velocity;
	void findPath();

	A_Star(Unit* unitToMove, Map* _map, Unit* _player);
	~A_Star();
};

class MoveForwardPlayer : public Movement {
	A_Star aStar;
	int moveCooldown = 0;
public:
	void makeMove();
	void resetMove();

	MoveForwardPlayer(Unit* unitToMove, Map* _map, Unit* _player);
	~MoveForwardPlayer();
};

class NoMoveFaceEnemy : public Movement {
	Unit* player;
public:
	void makeMove();

	NoMoveFaceEnemy(Unit* unitToMove, Unit* _player);
	~NoMoveFaceEnemy();
};