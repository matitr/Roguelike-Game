#pragma once
#include <list>
#include <stack>
#include <vector>
#include "SDL.h"
#include "myMath.h"

class Map;
class Unit;
class Field;

class Movement {
	double speed = -1;
	double speedMultiplier = -1;

protected:
	Unit* unitToMove;

	bool movementCanEnd = true;
	bool movementEnded = false;
public:
	virtual void makeMove() = 0;
	virtual void resetMove() {}

	void setSpeed(double s) { speed = s; }
	void setSpeedMultiplier(double sM) { speedMultiplier = sM; }
	double movementSpeed(Unit* unitToMove);
	bool actionCanEnd() { return movementCanEnd; }
	bool actionMovementEnded() { return movementEnded; }

	Movement(Unit* unitToMove);
	virtual ~Movement();
};

class A_Star {
	std::list<Field*> openSet; // Fields to check
	std::list<Field*> closedSet; // Fields already checked
	Field* start;
	Field* end;
	int pathLength = 0;

	Map* map;
	Unit* player;
	Unit* unitToMove;

	void createNeighbors(Field*, std::stack<Field*>&); // Create neighbors from field
	double distance(int x1, int y1, int x2, int y2);
	void getVelocityOfPath(Field*, Field* start);
public:
	SDL_Point velocity;
	void findPath();
	float distanceEdgesUnits();

	A_Star(Unit* unitToMove, Map* _map, Unit* _player);
	~A_Star();
};

class MoveForwardPlayer : public Movement {
	A_Star aStar;
	int moveCooldown = 0;
public:
	void makeMove() override;
	void resetMove() override;

	MoveForwardPlayer(Unit* unitToMove, Map* _map, Unit* _player);
	~MoveForwardPlayer();
};

class NoMoveFaceEnemy : public Movement {
	Unit* player;
public:
	void makeMove() override;

	NoMoveFaceEnemy(Unit* unitToMove, Unit* _player);
	~NoMoveFaceEnemy();
};

class Charge : public Movement {
	Unit* player;
	PointInt chargeTargetPos;
	bool getChargeTargetPos = true;
public:
	void makeMove() override;
	void resetMove() override;

	Charge(Unit* unitToMove, Unit* _player);
	~Charge();
};