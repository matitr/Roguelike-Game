#include "Movements.h"
#include "Map.h"
#include "Unit.h"
#include "Field.h"
#include <math.h>

Movement::Movement() {

}


Movement::~Movement() {

}

A_Star::A_Star(Map* _map, Unit* _player) {
	map = _map;
	player = _player;
//	roomW = map->currentRoom()->x1 - map->currentRoom()->x2 + 1;
//	room.resize(roomW * (map->currentRoom()->y1 - map->currentRoom()->y2 + 1));

}

A_Star::~A_Star() {

}

void A_Star::crearData() {
//	std::list<FieldA*>::iterator it = openSet.begin();
//
//	for (it; it != openSet.end(); it++)
//		delete (*it);
//
//	for (it = closedSet.begin(); it != closedSet.end(); it++)
//		delete (*it);
//
	openSet.clear();
	closedSet.clear();
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

SDL_Point* A_Star::getVelocityOfPath(Field* lastField, Field* start) {
	SDL_Point velocity;

	if (lastField == start) {
		velocity.x = 0;
		velocity.y = 0;
		return &velocity;
	}

	while (lastField->prevField && lastField->prevField != start)
		lastField = lastField->prevField;

	velocity.x = lastField->x() - start->x();
	velocity.y = lastField->y() - start->y();
	return &velocity;
}

SDL_Point A_Star::findPath(Unit* unitToMove) {
	openSet.clear();
	closedSet.clear();

	std::list<Field*>::iterator it = openSet.begin();
	Field* start = map->map[unitToMove->getPosMiddleX() / map->fieldWidth()][unitToMove->getPosMiddleY() / map->fieldHeight()];
	openSet.push_back(start);
	Field* lowestF;
	Field* neighbor;
	Field* end = map->map[player->getPosMiddleX() / map->fieldWidth()][player->getPosMiddleY() / map->fieldHeight()];

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
		
		if (lowestF == end)
			return *getVelocityOfPath(lowestF, start);

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


	return SDL_Point();
}

void MoveForwardPlayer::makeMove(Unit* unitToMove) {
	SDL_Point* velocityPath = &findPath(unitToMove);
	if (velocityPath) {
		unitToMove->velocity.x = velocityPath->x;
		unitToMove->velocity.y = velocityPath->y;
	}
	else {
		unitToMove->velocity.x = 0;
		unitToMove->velocity.y = 0;
	}
}

MoveForwardPlayer::MoveForwardPlayer(Map* _map, Unit* _player) : A_Star(_map, _player) {
	
}

MoveForwardPlayer::~MoveForwardPlayer() {

}





