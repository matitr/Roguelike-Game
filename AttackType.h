#pragma once
#include "SpriteAnimation.h"
#include "GameObject.h"
#include "Item.h"

class Map;
class AnimationDetails;

class AttackType : public GameObject {
protected:
	float damage;
	bool enemyHitted;
	bool destroyObj;

	ItemPassives staticPassives;
	std::vector<Unit*> unitsHitted;

	SpriteAnimation animation;
public:
	void setPosition(int x, int y);

	virtual bool update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit) = 0;
	virtual void draw(SDL_Point* startRender);

	void setEnemyHitted(Unit* u);
	bool canBeHitted(Unit* u);
	void delHittedUnitPointer(Unit* u);
	void destroy() { destroyObj = true; }

	float getDamage() { return damage; }
	const ItemPassives& getPassives() { return staticPassives; }

	AttackType(AnimationDetails& animation, ItemPassives& passives);
	~AttackType();
};

