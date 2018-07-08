#pragma once
#include "SpriteAnimation.h"
#include "GameObject.h"
#include "Item.h"

class Map;
struct AnimationDetails;

class AttackType : public GameObject {
protected:
	float damage;
	bool enemyHitted;
	bool destroyObj;

	ItemPassives staticPassives;
	std::vector<Unit*> unitsHitted;

public:
	virtual bool update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit) = 0;
	virtual void draw(SDL_Point* startRender);

	void setEnemyHitted(Unit* u);
	bool canBeHitted(Unit* u);
	void delHittedUnitPointer(Unit* u);
	virtual void onWallHit();
	virtual bool collision(Unit* u) { return detectCollision(u); }

	float getDamage() { return damage; }
	const ItemPassives& getPassives() { return staticPassives; }

	AttackType(ItemPassives& passives, double attackDamage);
	virtual ~AttackType();
};

