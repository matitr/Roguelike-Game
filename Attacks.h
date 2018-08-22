#pragma once
#include <list>
#include "AttackType.h"
#include "TextureManager.h"

class Unit;

//All attacks
class ProjectileDirection;
class MultipleProjectiles;
class MeleeSwingAttack;


class AttackPattern {
	double damage = -1;
	double damageMultiplier = -1;
public:
	virtual void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, PointInt* attackPoint) = 0;

	void setDamage(double d) { damage = d; }
	void setDamageMultiplier(double dM) { damageMultiplier = dM; }
	double attackDamage(ItemPassives& unitPassives);

	AttackPattern();
	virtual ~AttackPattern();
};

class ProjectileDirection : public AttackPattern { // Projectiles around point
	float startAngle;
	float angle;
	int numbOfProj;
	AnimationDetails& animationD;

public:
	void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, PointInt* attackPoint) override;

	ProjectileDirection(AnimationDetails& animationDetails, float _angle, int _numbOfProj) : animationD(animationDetails) {
		startAngle = _angle;
		numbOfProj = _numbOfProj;
	}

	~ProjectileDirection() {

	}
};

class MultipleProjectiles : public AttackPattern { // Multiple projectiles in one direction, seperated with a same angle.
	int numbOfProjectiles;
	AnimationDetails& animationD;
public:
	void setNumberOfProj(int i) { numbOfProjectiles = i; }
	void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, PointInt* attackPoint) override;

	MultipleProjectiles(AnimationDetails& animationDetails, int _numbOfProjectiles) : animationD(animationDetails), numbOfProjectiles(_numbOfProjectiles) {}

	~MultipleProjectiles() { }
};

class MeleeSwingAttack : public AttackPattern {
	int attackWidthAngle;
	AnimationDetails& animationD;
	int radius;

public:
	void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, PointInt* attackPoint) override;

	MeleeSwingAttack(AnimationDetails& animationDetails, int angleWidth, int _radius) 
		: animationD(animationDetails), attackWidthAngle(angleWidth), radius(_radius) {}

	~MeleeSwingAttack() { }
};

