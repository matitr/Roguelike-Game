#include "ActionUtilities.h"
#include "Attacks.h"
#include "Movements.h"


void ActionUtilities::addMoveAndAttack(Movement* move, AttackPattern* _attack, int _attackFrame) {
	movement = move;
	attack = _attack;
	attackFrame = _attackFrame;
}

void ActionUtilities::addAnimations(std::array<AnimationDetails, Direction::enum_size>& animationsToAdd, SDL_Rect& srcRectR) {
	for (int i = 0; i < Direction::enum_size; i++) {
		animations[i] = new SpriteAnimation(animationsToAdd[i], srcRectR);
	}
}

bool ActionUtilities::animationsExists() {
	int animationsSize = animations.size();

	if (!animationsSize)
		return false;

	for (int i = 0; i < animationsSize; i++) {
		if (!animations[i])
			return false;
	}

	return true;
}

void ActionUtilities::setFrameTime() {

}

void ActionUtilities::updateFrame(const float& moveSpeedMult, const float& attackSpeedMult) {

}

ActionUtilities::ActionUtilities() : animations(Direction::enum_size) {

}

ActionUtilities::ActionUtilities(Movement* _move, AttackPattern* _attack, int _attackFrame) : animations(Direction::enum_size) {
	movement = _move;
	attack = _attack;
	attackFrame = _attackFrame;
}

ActionUtilities::~ActionUtilities() {
	std::vector<SpriteAnimation*>::iterator it = animations.begin();

	for (it; it != animations.end(); it++)
		delete *it;

	if (attack)
		delete attack;

	if (movement)
		delete movement;
}
