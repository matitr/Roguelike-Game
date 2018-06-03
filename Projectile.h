#pragma once
#include "AttackType.h"


class Projectile : public AttackType {
	float speed;
	double direction;
	double angle; // starting in middle right. Upper "-", Bottom "+"

	int heightFromGround;
	SpriteAnimation animation;
public:
	bool update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit) override;
	void draw(SDL_Point* startRender) override;

	void setDirection(float dir);
	void setAngle(float ang);

	void homingShot(Unit* closestUnit);
	void onWallHit();

	Projectile(AnimationDetails& animation, ItemPassives& passives);
	~Projectile();
};

