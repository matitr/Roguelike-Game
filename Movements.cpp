#include "Movements.h"
#include "Map.h"
#include "Unit.h"
#include "Field.h"
#include <math.h>

Movement::Movement() {

}


Movement::~Movement() {

}	

#pragma region A_Star
A_Star::FieldA::FieldA(int _x, int _y) {
	x = _x;
	x = _x;
}
bool A_Star::FieldA::operator==(const FieldA& f) {
	if (x == f.x && y == f.y)
		return true;
	return false;
}

void A_Star::createNeighbors(Field* field, std::stack<Field*>& neighbors) {

	Field* toAdd = map->map[field->x() + 1][field->y()];

	if (toAdd->ground() && std::find(closedSet.begin(), closedSet.end(), toAdd) == closedSet.end())
		neighbors.push(toAdd);

	toAdd = map->map[field->x() + 1][field->y() + 1];

	if (toAdd->ground() && std::find(closedSet.begin(), closedSet.end(), toAdd) == closedSet.end())
		neighbors.push(toAdd);

	toAdd = map->map[field->x() + 1][field->y() - 1];

	if (toAdd->ground() && std::find(closedSet.begin(), closedSet.end(), toAdd) == closedSet.end())
		neighbors.push(toAdd);

	toAdd = map->map[field->x() - 1][field->y()];

	if (toAdd->ground() && std::find(closedSet.begin(), closedSet.end(), toAdd) == closedSet.end())
		neighbors.push(toAdd);

	toAdd = map->map[field->x() - 1][field->y() + 1];

	if (toAdd->ground() && std::find(closedSet.begin(), closedSet.end(), toAdd) == closedSet.end())
		neighbors.push(toAdd);

	toAdd = map->map[field->x() - 1][field->y() - 1];

	if (toAdd->ground() && std::find(closedSet.begin(), closedSet.end(), toAdd) == closedSet.end())
		neighbors.push(toAdd);

	toAdd = map->map[field->x()][field->y() + 1];

	if (toAdd->ground() && std::find(closedSet.begin(), closedSet.end(), toAdd) == closedSet.end())
		neighbors.push(toAdd);

	toAdd = map->map[field->x()][field->y() - 1];

	if (toAdd->ground() && std::find(closedSet.begin(), closedSet.end(), toAdd) == closedSet.end())
		neighbors.push(toAdd);

}

double A_Star::distance(int x1, int y1, int x2, int y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void A_Star::getVelocityOfPath(Field* lastField, Field* start) {

	if (lastField == start) {
		velocity.x = 0;
		velocity.y = 0;
		return;
	}

	while (lastField->prevField && lastField->prevField != start)
		lastField = lastField->prevField;

	velocity.x = lastField->x() - start->x();
	velocity.y = lastField->y() - start->y();
	return;
}

void A_Star::findPath(Unit* unitToMove) {
	openSet.clear();
	closedSet.clear();

	std::list<Field*>::iterator it = openSet.begin();
	Field* start = map->map[unitToMove->getPositionX() / map->fieldWidth()][unitToMove->getPositionY() / map->fieldHeight()];
	openSet.push_back(start);
	Field *lowestF, *neighbor, *end = map->map[player->getPositionX() / map->fieldWidth()][player->getPositionY() / map->fieldHeight()];

	while (!openSet.empty()) {
		lowestF = (*openSet.begin());
		for (it = openSet.begin()++; it != openSet.end(); it++) {
			if ((*it)->f < lowestF->f)
				lowestF = (*it);
			else if ((*it)->f == lowestF->f) {
				if ((*it)->g > lowestF->g)
					lowestF = (*it);
				if ((*it)->g > lowestF->g)
					lowestF = (*it);
			}
		}
		
		if (lowestF == end) {
			getVelocityOfPath(lowestF, start);
			return;
		}

		openSet.remove(lowestF);
		closedSet.push_back(lowestF);

		std::stack<Field*> neighbors; createNeighbors(lowestF, neighbors);

		while (!neighbors.empty()){
			neighbor = neighbors.top();
			neighbors.pop();
		
			double tempG = lowestF->g + 1;

			if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
				openSet.push_back(neighbor);
			}
			else if (tempG >= neighbor->g)
				continue;

			neighbor->g = tempG;
			neighbor->h = distance(neighbor->x(), neighbor->y(), end->x(), end->y());

			neighbor->f = neighbor->g + neighbor->h;
			neighbor->prevField = lowestF;
		}
	}

	velocity.x = 0;
	velocity.y = 0;

	return;
}

A_Star::A_Star(Map* _map, Unit* _player) {
	map = _map;
	player = _player;
}

A_Star::~A_Star() {

}
#pragma endregion

#pragma region MoveForwardPlayer
void MoveForwardPlayer::makeMove(Unit* unitToMove) {
	aStar.findPath(unitToMove);
	SDL_Point* velocityPath = &aStar.velocity;
	if (velocityPath) {
		unitToMove->velocity.x = velocityPath->x;
		unitToMove->velocity.y = velocityPath->y;
	}
	else {
		unitToMove->velocity.x = 0;
		unitToMove->velocity.y = 0;
	}
}

MoveForwardPlayer::MoveForwardPlayer(Map* _map, Unit* _player) : aStar(_map, _player) {
	
}

MoveForwardPlayer::~MoveForwardPlayer() {

}
#pragma endregion

#pragma region MoveForwardPlayer
void NoMoveFaceEnemy::makeMove(Unit* unitToMove) {
	unitToMove->getActiongManager().setCurrentDirection(player->getPositionX() - unitToMove->getPositionX(), player->getPositionY() - unitToMove->getPositionY());
	unitToMove->velocity.x = 0;
	unitToMove->velocity.y = 0;
}

NoMoveFaceEnemy::NoMoveFaceEnemy(Unit* _player) : player(_player) {

}

NoMoveFaceEnemy::~NoMoveFaceEnemy() {

}
#pragma endregion

