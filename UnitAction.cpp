#include "UnitAction.h"
#include "Attacks.h"
#include "Movements.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"
#include <iostream>
#include "DataBase.h"


bool UnitAction::canDynamicActivation(double dist) {
	if (_clearPathRequired) {
		int ite = 0;
		int nes = 0;
	}

	if (dynamicActivationOnly() && dist <= distActivationMax && dist >= distActivationMin && !presentCooldown)
		return true;

	return false;
}

void UnitAction::addActionUtilities(ActionUtilities* actionUtilitiesToAdd){
	if (actionUtilities.empty()) {
		actionUtilities.push_back(actionUtilitiesToAdd);
		currentActionUtility = actionUtilities.begin();
	}
	else
		actionUtilities.push_back(actionUtilitiesToAdd);
}

void UnitAction::addAnimations(std::array<AnimationDetails, Direction::enum_size>& animationsToAdd, SDL_Rect& srcRectRef) {
	(*currentActionUtility)->addAnimations(animationsToAdd, srcRectRef);
}

bool UnitAction::animationsExists() {
	return (*currentActionUtility)->animationsExists();
}

void  UnitAction::setFrameTime(int frameTime) {
	for (int i = 0; i < Direction::enum_size; i++) {
		(*currentActionUtility)->getAnimations()[i]->setFrameTime(frameTime);
	}
}

void UnitAction::setDirection(Direction::Name dir) {
	if (dir == currentDirection)
		return;

	(*currentActionUtility)->getAnimations()[dir]->setFrameCounter(*(*currentActionUtility)->getAnimations()[currentDirection]);
	currentDirection = dir;
}

void UnitAction::setDirection(UnitAction& actionOther) {
	if (actionOther.currentDirection == currentDirection)
		return;

	(*currentActionUtility)->getAnimations()[actionOther.currentDirection]->setFrameCounter(*(*currentActionUtility)->getAnimations()[currentDirection]);
	currentDirection = actionOther.currentDirection;
}

void UnitAction::setDirection(double x, double y) {
	Direction::Name dir = Direction::S;

	int angle = int(atan2(y, x) * 180.0 / 3.14159265);
	if (angle <= -135 || angle >= 135)
		dir = Direction::W;
	else if (angle < -45)
		dir = Direction::N;
	else if (angle <= 45)
		dir = Direction::E;
	else
		dir = Direction::S;

	setDirection(dir);
}

void UnitAction::setFirstFrame() {
	currentActionUtility = actionUtilities.begin();
	(*currentActionUtility)->getAnimations()[currentDirection]->setFirstFrame();
}

void UnitAction::setLastFrame() {
	(*currentActionUtility)->getAnimations()[currentDirection]->setLastFrame();
}

bool UnitAction::actionEnded() {
	if ((*currentActionUtility)->getAnimations()[currentDirection]->lastFrameEnded()) {
		if (!(*currentActionUtility)->getMovement() || (*currentActionUtility)->getMovement()->actionCanEnd()) {
				return true;
		}
	}
	else if ((*currentActionUtility)->getMovement() && (*currentActionUtility)->getMovement()->actionMovementEnded())
		return true;
	
	return false;
}

void UnitAction::updateFrame(const float& moveSpeedMult, const float& attackSpeedMult) {
	(*currentActionUtility)->updateFrame(moveSpeedMult, attackSpeedMult);
	if ((*currentActionUtility)->getAttack())
		(*currentActionUtility)->getAnimations()[currentDirection]->updateTexture(attackSpeedMult);
	else if ((*currentActionUtility)->getMovement())
		(*currentActionUtility)->getAnimations()[currentDirection]->updateTexture(moveSpeedMult);
	else
		(*currentActionUtility)->getAnimations()[currentDirection]->updateTexture();
}

bool UnitAction::nextActionUtilities() {
	currentActionUtility++;
	if (currentActionUtility != actionUtilities.end()) {
		setFirstFrame();
		setDirection(currentDirection);
		resetCooldown();
		resetMove();
		return true;
	}
	return false;
}

void UnitAction::updateCooldown() {
	if (presentCooldown > 0)
		presentCooldown--;
}

void UnitAction::resetMove() {
	if ((*currentActionUtility)->getMovement())
		(*currentActionUtility)->getMovement()->resetMove();

	currentActionUtility = actionUtilities.begin();
}

void UnitAction::updateMove() {
	if ((*currentActionUtility)->getMovement())
		(*currentActionUtility)->getMovement()->update();
}

void UnitAction::makeAttack(Unit* unit, std::list <AttackType*>& monsterAttacks, PointInt* attackPoint, float attackSpeedMult) {
	if ((*currentActionUtility)->getAttack() && (*currentActionUtility)->getAnimations()[currentDirection]->firstTimuUnitOfFrame((*currentActionUtility)->getAttackFrame(), attackSpeedMult))
		(*currentActionUtility)->getAttack()->makeAttack(unit, monsterAttacks, attackPoint);
}

void UnitAction::makeMove() {
	(*currentActionUtility)->getMovement()->makeMove();
}

UnitAction::UnitAction(Movement* _move, AttackPattern* _attack, int _attackFrame) : currentDirection(Direction::E){
	ActionUtilities* actionU = new ActionUtilities(_move, _attack, _attackFrame);
	actionUtilities.push_back(actionU);
	currentActionUtility = actionUtilities.begin();
}


UnitAction::~UnitAction() {
	std::vector<ActionUtilities*>::iterator it = actionUtilities.begin();

	for (it; it != actionUtilities.end(); it++)
		delete *it;
}
