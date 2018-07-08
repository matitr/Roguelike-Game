#include "Movements.h"
#include "Map.h"
#include "Unit.h"
#include "Field.h"
#include "UpdateCollision.h"
#include <math.h>


double Movement::movementSpeed(Unit* unitToMove) {
	if (speed >= 0)
		return speed;

	if (speedMultiplier >= 0)
		return unitToMove->getPassives()[StaticPassiveName::unitSpeed] * unitToMove->getBaseSpeed() * speedMultiplier;

	return unitToMove->getPassives()[StaticPassiveName::unitSpeed] * unitToMove->getBaseSpeed();
}

Movement::Movement(Unit* _unitToMove) : unitToMove(_unitToMove) {

}


Movement::~Movement() {

}	

#pragma region A_Star
void A_Star::createNeighbors(Field* field, std::stack<Field*>& neighbors) {

	for (int y = -1; y < 2; y++) {
		for (int x = -1; x < 2; x++) {
			if (std::find(closedSet.begin(), closedSet.end(), map->getField(field->x() + x, field->y() + y)) == closedSet.end()) {
				unitToMove->setPosition(field->x() * map->fieldRect.w + map->fieldRect.w / 2 + x * map->fieldRect.w
					, field->y() * map->fieldRect.h + map->fieldRect.h / 2 + y * map->fieldRect.h);

				if  (!UpdateCollision::detectCollisionWithField(unitToMove, map))
					neighbors.push(map->getField(field->x() + x, field->y() + y));

				else if (map->getField(field->x() + x, field->y() + y) == end && field->prevField)
					neighbors.push(map->getField(field->x() + x, field->y() + y));
			}
		}
	}
}

double A_Star::distance(int x1, int y1, int x2, int y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void A_Star::getVelocityOfPath(Field* lastField, Field* start) {
	pathLength = 0;
	if (lastField == start) {
		float distUnits = unitToMove->distanceEdges(player);
		if (distUnits < 3.0f) {
			velocity.x = 0;
			velocity.y = 0;
		}
		else {
			velocity.x = player->getPositionX() - unitToMove->getPositionX();
			velocity.y = player->getPositionY() - unitToMove->getPositionY();
			unitToMove->setMaxSpeed(distUnits - distUnits * 0.2f);
		}
		return;
	}

	while (lastField->prevField && lastField->prevField != start) {
		lastField = lastField->prevField;
		pathLength++;
	}

	// No collisions on the way
	if ((int)start->distanceEdgesX(end) / map->fieldRect.w == pathLength || (int)start->distanceEdgesY(end) / map->fieldRect.h == pathLength) {
		float distUnits = unitToMove->distanceEdges(player);
		if (distUnits < 3.0f) {
			velocity.x = 0;
			velocity.y = 0;
		}
		else {
			unitToMove->setMaxSpeed(distUnits - distUnits * 0.2f);
			velocity.x = player->getPositionX() - unitToMove->getPositionX();
			velocity.y = player->getPositionY() - unitToMove->getPositionY();
		}
		// toDo if collision with wall after move 

	}
	else {
		velocity.x = lastField->x() - start->x();
		velocity.y = lastField->y() - start->y();
	}
}

void A_Star::findPath() {
	openSet.clear();
	closedSet.clear();

	PointDouble unitStartPos(unitToMove->getPositionX(), unitToMove->getPositionY());

	std::list<Field*>::iterator it = openSet.begin();
	start = map->getField((int)unitToMove->getPositionX() / map->fieldWidth(), (int)unitToMove->getPositionY() / map->fieldHeight());
	start->prevField = nullptr;
	openSet.push_back(start);
	Field *lowestF, *neighbor;
	end = map->getField((int)player->getPositionX() / map->fieldWidth(), (int)player->getPositionY() / map->fieldHeight());

	while (!openSet.empty()) {
		lowestF = (*openSet.begin()); // Set lowestF to the best field in openSet
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
		
		if (lowestF == end) { // Path was found
			unitToMove->setPosition(unitStartPos.x, unitStartPos.y);
			getVelocityOfPath(end, start);
			return;
		}

		openSet.remove(lowestF);
		closedSet.push_back(lowestF);

		std::stack<Field*> neighbors; 
		createNeighbors(lowestF, neighbors);

		while (!neighbors.empty()){ // Calculate values for neighbors
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
	// Path was not found
	velocity.x = 0;
	velocity.y = 0;
	unitToMove->setPosition(unitStartPos.x, unitStartPos.y);

	return;
}

float A_Star::distanceEdgesUnits() {
	return unitToMove->distanceEdges(player);
}

A_Star::A_Star(Unit* _unitToMove, Map* _map, Unit* _player) : unitToMove(_unitToMove) {
	map = _map;
	player = _player;
}

A_Star::~A_Star() {

}
#pragma endregion

#pragma region MoveForwardPlayer
void MoveForwardPlayer::makeMove() {
	if (!moveCooldown || aStar.distanceEdgesUnits() < 50) {
		aStar.findPath();
		SDL_Point velocityPath = aStar.velocity;
		unitToMove->velocity.x = velocityPath.x;
		unitToMove->velocity.y = velocityPath.y;

		moveCooldown = 6 + rand() % 3;
	}
	moveCooldown--;
}

void MoveForwardPlayer::resetMove() {
	moveCooldown = 0;
}

MoveForwardPlayer::MoveForwardPlayer(Unit* _unitToMove, Map* _map, Unit* _player) : Movement(_unitToMove), aStar(_unitToMove, _map, _player) {
	
}

MoveForwardPlayer::~MoveForwardPlayer() {

}
#pragma endregion

#pragma region MoveForwardPlayer
void NoMoveFaceEnemy::makeMove() {
	unitToMove->getActiongManager().setCurrentDirection(player->getPositionX() - unitToMove->getPositionX(), player->getPositionY() - unitToMove->getPositionY());
	unitToMove->velocity.x = 0;
	unitToMove->velocity.y = 0;
}

NoMoveFaceEnemy::NoMoveFaceEnemy(Unit* _unitToMove, Unit* _player) : Movement(_unitToMove), player(_player) {

}

NoMoveFaceEnemy::~NoMoveFaceEnemy() {

}
#pragma endregion


#pragma region Charge
void Charge::makeMove() {

}

Charge::Charge(Unit* _unitToMove, Unit* _player) : Movement(_unitToMove), player(_player) {

}

Charge::~Charge() {

}
#pragma endregion