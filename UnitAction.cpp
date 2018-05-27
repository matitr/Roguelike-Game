#include "UnitAction.h"
#include "Attacks.h"
#include "Movements.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"


void UnitAction::addAnimation(Direction::Name dir, AnimationDetails& animationData, SDL_Rect& srcRectR) {
	animations[dir] = new SpriteAnimation(animationData, srcRectR);
}

void UnitAction::setDirection(Direction::Name dir) {
	if (dir == currentDirection)
		return;

	animations[dir]->setFrameCounter(*animations[currentDirection]);
	currentDirection = dir;
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
