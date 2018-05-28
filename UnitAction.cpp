#include "UnitAction.h"
#include "Attacks.h"
#include "Movements.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"
#include <iostream>


bool UnitAction::canForceActivation(double dist) {
	if (distanceActivation != -1 && dist <= distanceActivation)
		return true;

	return false;
}

void UnitAction::addAnimation(Direction::Name dir, AnimationDetails& animationData, SDL_Rect& srcRectR) {
	animations[dir] = new SpriteAnimation(animationData, srcRectR);
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

	int angle = atan2(y, x) * 180.0 / 3.14159265;
	std::cout << angle << std::endl;
	if (angle <= -135 || angle >= 135)
		dir = Direction::W;
	else if (angle < -45)
		dir = Direction::N;
	else if (angle <= 45)
		dir = Direction::E;
	else
		dir = Direction::S;


//	if (x > 0)
//		dir = Direction::E;
//	else if (x < 0)
//		dir = Direction::W;
//	else if (y > 0)
//		dir = Direction::S;
//	else if (y < 0)
//		dir = Direction::N;

	setDirection(dir);
}

void UnitAction::setFirstFrame() {
	animations[currentDirection]->setFirstFrame();
}

void UnitAction::setLastFrame() {
	animations[currentDirection]->setLastFrame();
}

bool UnitAction::actionEnded() {
	return animations[currentDirection]->lastFrameEnded();
}

void UnitAction::updateFrame() {
	animations[currentDirection]->updateTexture();
}

void UnitAction::makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks, SDL_Point* attackPoint) {
	if (animations[currentDirection]->getFrameCounter() == attackFrame && attack)
	attack->makeAttack(unit, monsterAttacks, attackPoint);
}

void UnitAction::makeMove(Unit* unitToMove) {
	movement->makeMove(unitToMove);
}

UnitAction::UnitAction( Movement* _move, AttackPattern* _attack, int _attackFrame) : currentDirection(Direction::E){
	movement = _move;
	attack = _attack;
	attackFrame = _attackFrame;

	animations.resize(Direction::Name::enum_size);
}


UnitAction::~UnitAction() {

}
