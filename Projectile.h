#pragma once
#include "SpriteAnimation.h"
#include "GameObject.h"
#include "Item.h"

class Map;
class AnimationDetails;

class Projectile : public GameObject {
	float speed;
	double direction;
	double angle; // starting in middle right. Upper "-", Bottom "+"
	float damage;
	bool enemyHitted;
	bool destroyObj;
	int heightFromGround;
	int frames, frameTime, currFrame, frameCounter;

	ItemPassives staticPassives;
	std::vector<Unit*> unitsHitted;

	SpriteAnimation animation;
public:
	void setDirection(float dir);
	void setAngle(float ang);
	void setPosition(int x, int y);

	bool update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit);
	void draw(SDL_Point* startRender);

	void homingShot(Unit* closestUnit);

	void setEnemyHitted(Unit* u);
	bool canBeHitted(Unit* u);
	void delHittedUnitPointer(Unit* u);
	void destroy() { destroyObj = true; }

	float getDamage() { return damage; }
	bool isHoming() { return staticPassives[StaticPassiveName::homing]; }

	Projectile(AnimationDetails& animation, ItemPassives& passives);
	~Projectile();
};

