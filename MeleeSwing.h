#pragma once
#include "AttackType.h"

class Unit;

class MeleeSwing : public AttackType {
	int attackAngle;
	int attackWidthAngle;

	int frames, frameTime, frameCounter = 0;
public:
	bool update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit);
	void draw(SDL_Point* startRender) {}

	bool collision(Unit* u) override; // Collision type : sector
	void setAngles(int attackAngle, int attackWidthAngle);

	MeleeSwing(AnimationDetails& animation, PassivesManager* passivesManager, double attackDamage);
	~MeleeSwing();
};

