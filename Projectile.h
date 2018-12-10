#pragma once
#include "AttackType.h"

class ProjectileEffect;

class Projectile : public AttackType {
	float speedBasic;
	float speedMult;
	float speed;
	double direction;
	double angle; // starting in middle right. Upper "-", Bottom "+"
	double travelDist = 0;

	int heightFromGround;
	SpriteAnimation animation;

	std::vector<ProjectileEffect*> projectileEffects;
public:
	bool update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit) override;
	void draw(SDL_Point* startRender) override;

	double getTravelDist() { return travelDist; }

	void setDirection(double dir);
	void setAngle(double ang);
	void changeAngleBy(double ang);
	void addSpeedMult(float speedMultToAdd);

	void addEffects(std::vector<ProjectileEffect*>& effects);

	void homingShot(Unit* closestUnit);
	void onWallHit();

	Projectile(AnimationDetails& animation, PassivesManager* passivesManager, double attackDamage);
	~Projectile();
};

