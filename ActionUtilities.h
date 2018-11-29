#pragma once
#include <vector>
#include "AttackType.h"
#include "DataBase.h"

class Movement;
class AttackPattern;

class ActionUtilities {
	Movement *movement;
	AttackPattern *attack;
	std::vector<SpriteAnimation*> animations;

	int attackFrame = 0;
public:
	Movement* getMovement() { return movement; }
	AttackPattern* getAttack() { return attack; }
	std::vector<SpriteAnimation*>& getAnimations() { return animations; }
	int getAttackFrame() { return attackFrame; }

	void addMoveAndAttack(Movement* move, AttackPattern* attack, int attackFrame = -1);
	void addAnimations(std::array<AnimationDetails, Direction::enum_size>& animations, SDL_Rect& srcRectR);

	bool animationsExists();
	void updateFrame(const float& moveSpeedMult, const float& attackSpeedMult);

	ActionUtilities();
	ActionUtilities(Movement* move, AttackPattern* attack, int attackFrame);
	~ActionUtilities();
};