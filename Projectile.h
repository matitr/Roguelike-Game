#pragma once
#include "SpriteAnimation.h"
#include "GameObject.h"
#include "Item.h"

class Map;
class AnimationDetails;

class Projectile : public GameObject {
	float speed;
	float direction;
	float angle; // starting in middle right. Upper "-", Bottom "+"
	float damage;
	bool enemyHitted;
	int heightFromGround;
	int frames, frameTime, currFrame, frameCounter;

	ItemPassives staticPassives;
public:
	void setDirection(float dir);
	void setAngle(float ang);
	void setPosition(int x, int y);

	bool update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit);
	void draw(SDL_Point* startRender);

	void homingShot(Unit* closestUnit);

	float getDamage() { return damage; }
	void setEnemyHitted(bool hitted) { enemyHitted = hitted; }
	bool isHoming() { return staticPassives[StaticPassiveName::homing]; }

	Projectile(AnimationDetails& animation, ItemPassives& passives);
	~Projectile();
};

