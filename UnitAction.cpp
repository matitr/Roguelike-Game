#include "UnitAction.h"
#include "Attacks.h"
#include "Movements.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"
#include <iostream>
#include "DataBase.h"


bool UnitAction::canDynamicActivation(double dist) {
	if (dynamicActivationOnly() && dist <= distActivationMax && dist >= distActivationMin && !presentCooldown)
		return true;

	return false;
}

void UnitAction::addAnimation(Direction::Name dir, AnimationDetails& animationData, SDL_Rect& srcRectR) {
	animations[dir] = new SpriteAnimation(animationData, srcRectR);
}

void UnitAction::addAnimations(std::array<AnimationDetails, Direction::enum_size>& animationsToAdd, SDL_Rect& srcRectR) {
	for (int i = 0; i < Direction::enum_size; i++) {
		animations[i] = new SpriteAnimation(animationsToAdd[i], srcRectR);
	}
}

bool UnitAction::animationsExists() {
	int animationsSize = animations.size();

	if (!animationsSize)
		return false;

	for (int i = 0; i < animationsSize; i++) {
		if (!animations[i])
			return false;
	}

	return true;
}

void  UnitAction::setFrameTime(int frameTime) {
	for (int i = 0; i < Direction::enum_size; i++) {
		animations[i]->setFrameTime(frameTime);
	}
}

void UnitAction::setDirection(Direction::Name dir) {
	if (dir == currentDirection)
		return;

	animations[dir]->setFrameCounter(*animations[currentDirection]);
	currentDirection = dir;
}

void UnitAction::setDirection(UnitAction& actionOther) {
	if (actionOther.currentDirection == currentDirection)
		return;

	animations[actionOther.currentDirection]->setFrameCounter(*animations[currentDirection]);
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
	animations[currentDirection]->setFirstFrame();
}

void UnitAction::setLastFrame() {
	animations[currentDirection]->setLastFrame();
}

bool UnitAction::actionEnded() {
	if (animations[currentDirection]->lastFrameEnded()) {
		if (!movement || movement->actionCanEnd())
			return true;
	}
	else if (movement && movement->actionMovementEnded())
		return true;
	
	return false;
}

void UnitAction::updateFrame(const float& moveSpeedMult, const float& attackSpeedMult) {
	if (attack)
		animations[currentDirection]->updateTexture(attackSpeedMult);
	else if (movement)
		animations[currentDirection]->updateTexture(moveSpeedMult);
	else
		animations[currentDirection]->updateTexture();
}

void UnitAction::updateCooldown() {
	if (presentCooldown > 0)
		presentCooldown--;
}

void UnitAction::resetMove() {
	if (movement)
		movement->resetMove();
}

void UnitAction::updateMove() {
	if (movement)
		movement->update();
}

void UnitAction::makeAttack(Unit* unit, std::list <AttackType*>& monsterAttacks, PointInt* attackPoint, float attackSpeedMult) {
	if (attack && animations[currentDirection]->firstTimuUnitOfFrame(attackFrame, attackSpeedMult))
		attack->makeAttack(unit, monsterAttacks, attackPoint);
}

void UnitAction::makeMove() {
	movement->makeMove();
}

UnitAction::UnitAction( Movement* _move, AttackPattern* _attack, int _attackFrame) : currentDirection(Direction::E){
	movement = _move;
	attack = _attack;
	attackFrame = _attackFrame;

	animations.resize(Direction::Name::enum_size);
}


UnitAction::~UnitAction() {
	std::vector<SpriteAnimation*>::iterator it = animations.begin();

	for (it; it != animations.end(); it++)
		delete *it;

	if (attack)
		delete attack;

	if (movement)
		delete movement;
}
