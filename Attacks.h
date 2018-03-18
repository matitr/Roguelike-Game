#pragma once
#include <list>
#include "Projectile.h"
#include "TextureManager.h"

class Unit;

class Attack {

public:
	virtual void makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks) = 0;

	Attack();
	~Attack();
};

class ProjectileDirection : public Attack {
	float startAngle;
	float angle;
	int numbOfProj;

public:
	void makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks);

	ProjectileDirection(float _angle, int _numbOfProj) {
		startAngle = _angle;
		numbOfProj = _numbOfProj;
	}

	~ProjectileDirection() {

	}
};