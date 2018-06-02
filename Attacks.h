#pragma once
#include <list>
#include "AttackType.h"
#include "TextureManager.h"

class Unit;

class AttackPattern {

public:
	virtual void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, SDL_Point* attackPoint) = 0;

	AttackPattern();
	~AttackPattern();
};

class ProjectileDirection : public AttackPattern {
	float startAngle;
	float angle;
	int numbOfProj;
	AnimationDetails& animationD;

public:
	void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, SDL_Point* attackPoint);

	ProjectileDirection(AnimationDetails& animationDetails, float _angle, int _numbOfProj) : animationD(animationDetails) {
		startAngle = _angle;
		numbOfProj = _numbOfProj;
	}

	~ProjectileDirection() {

	}
};

class MultipleProjectiles : public AttackPattern {
	int numbOfProjectiles;
	AnimationDetails& animationD;
public:
	void setNumberOfProj(int i) { numbOfProjectiles = i; }
	void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, SDL_Point* attackPoint);

	MultipleProjectiles(AnimationDetails& animationDetails, int _numbOfProjectiles) : animationD(animationDetails), numbOfProjectiles(_numbOfProjectiles) {

	}

	~MultipleProjectiles() { }
};