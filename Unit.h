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
	PointInt attackPos;

	float maxSpeed;
	float speed;
	bool isAlive = true;

	HealthBar* healthBar;

	ItemPassives staticPassives;
	PassivesManager* passivesManager;

	bool unitDetectedCollisionUnit;
	bool unitDetectedCollisionWall;
public:
	virtual bool update(std::list <AttackType*>& monsterAttacks, Map* map);
	virtual void draw(SDL_Point* startRender);

	void setClosestEnemy(Unit* u, double dist);

	void takeDamage(float& damage, DamageType damageType = DamageType::Physical);
	const UnitType& getUnitType() { return unitType; }
	ItemPassives& getPassives() { return staticPassives; }
	ActionsManager& getActiongManager() { return actionsManager; }
	PassivesManager* getPassivesManager() { return passivesManager; }
	const PointInt& getAttackPos() { return attackPos; }
	bool alive() { return isAlive; }

	void setCollisionWithUnit() { unitDetectedCollisionUnit = true; }
	void setHittedWall() { unitDetectedCollisionWall = true; }
	bool detectedCollisionUnit() { return unitDetectedCollisionUnit; }
	bool detectedCollisionWall() { return unitDetectedCollisionWall; }

	float getBaseSpeed() { return staticPassives[StaticPassiveName::unitSpeed]; }
	void setMaxSpeed(float maxS) { maxSpeed = maxS; }
	void setSpeed(float s) { speed = s; }
	 
	Unit(TextureInfo& txtInfo, UnitType uType);
	virtual ~Unit();

	// For testing
	void renderCircle(int _x, int _y, int radius);
};

