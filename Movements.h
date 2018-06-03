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

	Movement(Unit* unitToMove);
	~Movement();
};

class A_Star {
	struct FieldA {
		int f = 0, g = 0, h = 0;
		int x, y;

		std::list<FieldA*> neighbors;

		FieldA(int _x, int _y);
		inline bool operator==(const FieldA& f);
	};

	std::list<Field*> openSet;
	std::list<Field*> closedSet;
	Map* map;
	Unit* player;


	void createNeighbors(Field*, std::stack<Field*>&);
	double distance(int x1, int y1, int x2, int y2);
	void getVelocityOfPath(Field*, Field* start);
public:
	SDL_Point velocity;
	void findPath(Unit* unitToMove);

	A_Star(Map* _map, Unit* _player);
	~A_Star();
};

class MoveForwardPlayer : public Movement {
	A_Star aStar;
public:
	void makeMove();

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