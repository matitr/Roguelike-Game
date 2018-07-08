#pragma once
#include "Animation.h"
#include "Map.h"
#include "Attacks.h"
#include "GameObject.h"
#include "Item.h"
#include "ActionsManager.h"


class AttackType;
class UnitAction;
class AttackPattern;
class Movement;

class Unit : public GameObject {
protected:
	ActionsManager actionsManager;

	Unit* closestEnemy = nullptr;
	double closestEnemyDist;

	float baseSpeed;
	float speed;
	float maxSpeed;
	float hp;
	float maxHp;

	ItemPassives staticPassives;
public:
	virtual bool update(std::list <AttackType*>& monsterAttacks, Map* map);
	virtual void draw(SDL_Point* startRender);

	void setClosestEnemy(Unit* u, double dist);

	void setHp(int _hp) { hp = float(hp); }
	void takeDamage(float damage) { hp -= damage; }
	ItemPassives& getPassives() { return staticPassives; }
	ActionsManager& getActiongManager() { return actionsManager; }

	float getBaseSpeed() { return baseSpeed; }
	void setMaxSpeed(float maxS) { maxSpeed = maxS; }
	void setSpeed(float s) { speed = s; }
	 
	Unit(TextureInfo& txtInfo);
	virtual ~Unit();

	// For testing
	void renderCircle(int _x, int _y, int radius);
};

