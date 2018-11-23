#pragma once
#include <list>
#include "AttackType.h"
#include "TextureManager.h"

class Unit;
class Projectile;
class ProjectileEffect;

//All attacks
class ProjectilesAround;
class MultipleProjectiles;
class MeleeSwingAttack;


class AttackPattern {
	double damage = -1;
	double damageMultiplier = -1;
	std::vector<ProjectileEffect*> projectileEffects;
protected:
	AnimationDetails& animationD;
public:
	virtual void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, PointInt* attackPoint) = 0;

	void setDamage(double d) { damage = d; }
	void setDamageMultiplier(double dM) { damageMultiplier = dM; }
	double attackDamage(ItemPassives& unitPassives);
	void addProjectileEffect(ProjectileEffect* effect);
	Projectile* createProjectile(Unit* unit);

	AttackPattern(AnimationDetails& animationDetails);
	virtual ~AttackPattern();
};

class ProjectilesAround : public AttackPattern { // Projectiles around point
	float startAngle;
	float angle;
	int numbOfProj;

public:
	void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, PointInt* attackPoint) override;

	ProjectilesAround(AnimationDetails& animationDetails, float _angle, int _numbOfProj) : AttackPattern(animationDetails) {
		startAngle = _angle;
		numbOfProj = _numbOfProj;
	}

	~ProjectilesAround() {

	}
};

class MultipleProjectiles : public AttackPattern { // Multiple projectiles in one direction, seperated with a same angle.
	int numbOfProjectiles;
public:
	void setNumberOfProj(int i) { numbOfProjectiles = i; }
	void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, PointInt* attackPoint) override;

	MultipleProjectiles(AnimationDetails& animationDetails, int _numbOfProjectiles) : AttackPattern(animationDetails), numbOfProjectiles(_numbOfProjectiles) {}

	~MultipleProjectiles() { }
};

class MeleeSwingAttack : public AttackPattern {
	int attackWidthAngle;
	int radius;

public:
	void makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, PointInt* attackPoint) override;

	MeleeSwingAttack(AnimationDetails& animationDetails, int angleWidth, int _radius) 
		: AttackPattern(animationDetails), attackWidthAngle(angleWidth), radius(_radius) {}

	~MeleeSwingAttack() { }
};

