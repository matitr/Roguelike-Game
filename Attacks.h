#pragma once
#include <list>
#include "Projectile.h"
#include "TextureManager.h"

class Unit;

class AttackPattern {

public:
	virtual void makeAttack(Unit* unit, std::list <Projectile*>& attacksContainer, SDL_Point* attackPoint) = 0;

	AttackPattern();
	~AttackPattern();
};

class ProjectileDirection : public AttackPattern {
	float startAngle;
	float angle;
	int numbOfProj;

public:
	void makeAttack(Unit* unit, std::list <Projectile*>& attacksContainer, SDL_Point* attackPoint);

	ProjectileDirection(float _angle, int _numbOfProj) {
		startAngle = _angle;
		numbOfProj = _numbOfProj;
	}

	~ProjectileDirection() {

	}
};

class MultipleProjectiles : public AttackPattern {
	int numbOfProjectiles;

public:
	void setNumberOfProj(int i) { numbOfProjectiles = i; }
	void makeAttack(Unit* unit, std::list <Projectile*>& attacksContainer, SDL_Point* attackPoint);

	MultipleProjectiles(int _numbOfProjectiles) : numbOfProjectiles(_numbOfProjectiles) {

	}

	~MultipleProjectiles() { }
};