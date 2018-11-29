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
		return (1 + unitToMove->getPassives()[StaticPassiveName::unitSpeedMult]) * unitToMove->getBaseSpeed() * speedMultiplier;

	return (1 + unitToMove->getPassives()[StaticPassiveName::unitSpeedMult]) * unitToMove->getBaseSpeed();
}

Movement::Movement(Unit* _unitToMove) : unitToMove(_unitToMove) {

}


Movement::~Movement() {

}	

#pragma region A_Star
void A_Star::createNeighbors(Field* field, std::stack<Field*>& neighbors) {

	for (int y = -1; y < 2; y += 2) {
		if (std::find(closedSet.begin(), closedSet.end(), map->getField(field->x(), field->y() + y)) == closedSet.end()) {
			unitToMove->setPosition(field->x() * map->fieldRect.w + map->fieldRect.w / 2, field->y() * map->fieldRect.h + map->fieldRect.h / 2 + y * map->fieldRect.h);

			if (!UpdateCollision::detectCollisionWithField(unitToMove, map))
				neighbors.push(map->getField(field->x(), field->y() + y));
			else if (map->getField(field->x(), field->y() + y) == end)
				neighbors.push(map->getField(field->x(), field->y() + y));
		}
	}

	for (int x = -1; x < 2; x += 2) {
		if (std::find(closedSet.begin(), closedSet.end(), map->getField(field->x() + x, field->y())) == closedSet.end()) {
			unitToMove->setPosition(field->x() * map->fieldRect.w + map->fieldRect.w / 2 + x * map->fieldRect.w, field->y() * map->fieldRect.h + map->fieldRect.h / 2);

			if (!UpdateCollision::detectCollisionWithField(unitToMove, map))
				neighbors.push(map->getField(field->x() + x, field->y()));
			else if (map->getField(field->x() + x, field->y()) == end)
				neighbors.push(map->getField(field->x() + x, field->y()));
		}
	}

	// Check diagonal fields
	for (int y = -1; y < 2; y += 2) {
		for (int x = -1; x < 2; x += 2) {
			if (std::find(closedSet.begin(), closedSet.end(), map->getField(field->x() + x, field->y() + y)) == closedSet.end()) {

				// Check between 2 fields
				unitToMove->setPosition(field->getPositionX() + x * (map->fieldRect.w * 0.5), field->getPositionY() + y * (map->fieldRect.h * 0.5));

				// Check diagonal field
				if (!UpdateCollision::detectCollisionWithField(unitToMove, map)) {
					unitToMove->setPosition(field->x() * map->fieldRect.w + map->fieldRect.w / 2 + x * map->fieldRect.w
						, field->y() * map->fieldRect.h + map->fieldRect.h / 2 + y * map->fieldRect.h);

					if (!UpdateCollision::detectCollisionWithField(unitToMove, map))
						neighbors.push(map->getField(field->x() + x, field->y() + y));
				}

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
	if (((int)start->distanceEdgesX(end) / map->fieldRect.w == pathLength && lastField->getPositionY() == start->getPositionY()) 
		|| (int)start->distanceEdgesY(end) / map->fieldRect.h == pathLength && lastField->getPositionX() == start->getPositionX()) {

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
//		unitToMove->velocity.x = lastField->x() - start->x();
//		unitToMove->velocity.y = lastField->y() - start->y();
//		unitToMove->setPosition(unitStartPos.x, unitStartPos.y);
//		unitToMove->makeMove();
//		PointDouble unitPosAfterMove(unitToMove->getPositionX(), unitToMove->getPositionY());
//		unitToMove->collisionUnitFields(map, map->fieldRect);
//		if (unitToMove->getPositionX() != unitPosAfterMove.x || unitToMove->getPositionY() != unitPosAfterMove.y) {
//			velocity.x = unitToMove->getPositionX() - unitStartPos.x;
//			velocity.y = unitToMove->getPositionY() - unitStartPos.y;
//
////			velocity.x = lastField->getPositionX() - unitStartPos.x;
////			velocity.y = lastField->getPositionY() - unitStartPos.y;
//		}
//		unitToMove->setPosition(unitStartPos.x, unitStartPos.y);


	}

	unitToMove->velocity.x = velocity.x;
	unitToMove->velocity.y = velocity.y;
	unitToMove->setPosition(unitStartPos.x, unitStartPos.y);
	unitToMove->makeMove();

	if (UpdateCollision::detectCollisionWithField(unitToMove, map)) {
		if (velocity.x) {
			for (int yIt = -1; yIt < 2; yIt += 2) {
				if (map->getField(lastField->x(), lastField->y() + yIt)->type() == FieldType::Wall) {
					Field* fieldToCheck = map->getField(lastField->x(), lastField->y() + yIt);
					if (map->getField(start->x(), start->y() + yIt)->type() == FieldType::Wall)
						fieldToCheck = map->getField(start->x(), start->y() + yIt);

					if (velocity.x > 0)
						velocity.x = (fieldToCheck->getPositionX() - fieldToCheck->getRadius()) - unitStartPos.x;
					else
						velocity.x = (fieldToCheck->getPositionX() + fieldToCheck->getRadius()) - unitStartPos.x;

					if ((unitToMove->velocity.x > 0 && velocity.x <= 0) || (unitToMove->velocity.x < 0 && velocity.x >= 0))
						velocity.x = unitToMove->velocity.x;

					if (yIt > 0)
						velocity.y = (fieldToCheck->getPositionY() - fieldToCheck->getRadius() - unitToMove->getRadius()) - unitStartPos.y;
					else
						velocity.y = (fieldToCheck->getPositionY() + fieldToCheck->getRadius() + unitToMove->getRadius()) - unitStartPos.y;
				}
			}
		}
		if (velocity.y) {
			for (int xIt = -1; xIt < 2; xIt += 2) {
				if (map->getField(lastField->x() + xIt, lastField->y())->type() == FieldType::Wall) {
					Field* fieldToCheck = map->getField(lastField->x() + xIt, lastField->y());
					if (map->getField(start->x() + xIt, start->y())->type() == FieldType::Wall)
						fieldToCheck = map->getField(start->x() + xIt, start->y());

					if (velocity.y > 0)
						velocity.y = (fieldToCheck->getPositionY() - fieldToCheck->getRadius()) - unitStartPos.y;
					else
						velocity.y = (fieldToCheck->getPositionY() + fieldToCheck->getRadius()) - unitStartPos.y;

					if ((unitToMove->velocity.y > 0 && velocity.y <= 0) || (unitToMove->velocity.y < 0 && velocity.y >= 0))
						velocity.y = unitToMove->velocity.y;

					if (xIt > 0)
						velocity.x = (fieldToCheck->getPositionX() - fieldToCheck->getRadius() - unitToMove->getRadius()) - unitStartPos.x;
					else
						velocity.x = (fieldToCheck->getPositionX() + fieldToCheck->getRadius() + unitToMove->getRadius()) - unitStartPos.x;
				}
			}
		}
	}
	unitToMove->setPosition(unitStartPos.x, unitStartPos.y);
}

void A_Star::findPath() {
	openSet.clear();
	closedSet.clear();

	unitStartPos.x = unitToMove->getPositionX();
	unitStartPos.y = unitToMove->getPositionY();

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

		moveCooldown = 1;
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

#pragma region NoMoveFaceEnemy
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
	unitToMove->velocity.x = chargeVelocity.x;
	unitToMove->velocity.y = chargeVelocity.y;
}

void Charge::resetMove() {
	getChargeTargetPos = false;

	chargeTargetPos.x = player->getPositionX();
	chargeTargetPos.y = player->getPositionY();

	chargeVelocity.x = chargeTargetPos.x - unitToMove->getPositionX();
	chargeVelocity.y = chargeTargetPos.y - unitToMove->getPositionY();

	chargeAngleRadians = atan2(chargeTargetPos.y - unitToMove->getPositionY(), chargeTargetPos.x - unitToMove->getPositionX());

	movementCanEnd = false;
	movementEnded = false;
}

void Charge::update() {
	double currentAngleRadians = atan2(chargeTargetPos.y - unitToMove->getPositionY(), chargeTargetPos.x - unitToMove->getPositionX());

	if ((!unitToMove->velocity.x && !unitToMove->velocity.y) || abs((currentAngleRadians + M_PI) - (chargeAngleRadians + M_PI)) > 0.6 
		|| unitToMove->detectedCollisionUnit() || unitToMove->detectedCollisionWall())
 		movementEnded = true;
}

Charge::Charge(Unit* _unitToMove, Unit* _player) : Movement(_unitToMove), player(_player) {

}

Charge::~Charge() {

}
#pragma endregion