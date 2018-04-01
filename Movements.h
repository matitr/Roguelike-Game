#pragma once
#include <list>
#include <stack>
#include <vector>
#include "SDL.h"

class Map;
class Unit;
class Field;

class Movement {

public:
	virtual void makeMove(Unit* unitToMove) = 0;

	Movement();
	~Movement();
};

class A_Star {
	struct FieldA {
		int f = 0, g = 0, h = 0;
		int x, y;

		std::list<FieldA*> neighbors;

		FieldA(int _x, int _y) {
			x = _x;
			x = _x;
		}
		inline bool operator==(const FieldA& f) {
			if (x == f.x && y == f.y)
				return true;
			return false;
		}
	};

	std::list<Field*> openSet;
	std::list<Field*> closedSet;
	Map* map;
	Unit* player;
//	int roomW;
//	std::vector<FieldA*> room;

	void createNeighbors(Field*, std::stack<Field*>&);
	double distance(int x1, int y1, int x2, int y2);
	SDL_Point* getVelocityOfPath(Field*, Field* start);
public:
	SDL_Point findPath(Unit* unitToMove);

	A_Star(Map* _map, Unit* _player);
	~A_Star();
};

class MoveForwardPlayer : A_Star, public Movement {

public:
	void makeMove(Unit* unitToMove);

	MoveForwardPlayer(Map* _map, Unit* _player);
	~MoveForwardPlayer();
};