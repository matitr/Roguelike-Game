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

	float speed;
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

	Unit(TextureInfo& txtInfo);
	~Unit();
	void renderCircle(int _x, int _y, int radius);
};

