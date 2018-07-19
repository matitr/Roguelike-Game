#pragma once
#include "Map.h"
#include "Attacks.h"
#include "GameObject.h"
#include "Item.h"
#include "ActionsManager.h"


class AttackType;
class UnitAction;
class AttackPattern;
class Movement;
class PassivesManager;
class BuffsManager;
class HealthBar;

enum class UnitType { Monster, Boss, Player };

class Unit : public GameObject {
protected:
	UnitType unitType;

	ActionsManager actionsManager;

	Unit* closestEnemy = nullptr;
	double closestEnemyDist;

	float maxSpeed;
	float speed;

	HealthBar* healthBar;

	ItemPassives staticPassives;
	PassivesManager* passivesManager;
public:
	virtual bool update(std::list <AttackType*>& monsterAttacks, Map* map);
	virtual void draw(SDL_Point* startRender);

	void setClosestEnemy(Unit* u, double dist);

	void takeDamage(float damage);
	const UnitType& getUnitType() { return unitType; }
	ItemPassives& getPassives() { return staticPassives; }
	ActionsManager& getActiongManager() { return actionsManager; }
	PassivesManager* getPassivesManager() { return passivesManager; }

	float getBaseSpeed() { return staticPassives[StaticPassiveName::unitSpeed]; }
	void setMaxSpeed(float maxS) { maxSpeed = maxS; }
	void setSpeed(float s) { speed = s; }
	 
	Unit(TextureInfo& txtInfo, UnitType uType);
	virtual ~Unit();

	// For testing
	void renderCircle(int _x, int _y, int radius);
};

