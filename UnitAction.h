#pragma once
#include <list>
#include "AttackType.h"
#include "TextureManager.h"

class Movement;
class AttackPattern;
class Unit;

class UnitAction {
	Movement *movement;
	AttackPattern *attack;
	std::vector<SpriteAnimation*> animations;
	bool actionEnable;
	double distActivationMax = -1;
	double distActivationMin = -1;
	bool dynamicEnableOnly = false;

	int attackFrame = 0;
	Direction::Name currentDirection;
public:
	bool dynamicActivationOnly() { return (dynamicEnableOnly || distActivationMax != -1); }
	void setDistActivationMax(double dist) { distActivationMax = dist; }
	void setDistActivationMin(double dist) { distActivationMin = dist; }
	bool canDynamicActivation(double dist); // Check distActivationMax && distActivationMin
	void setDynamicActivationOnly() { dynamicEnableOnly = true; }

	inline int makeAttackFrame() { return attackFrame; }
	inline bool movementExists() { return movement ? true : false; }
	inline bool attackExists() { return attack ? true : false; }
	Direction::Name getDirection() { return currentDirection; }

	void addAnimation(Direction::Name dir, AnimationDetails& animationData, SDL_Rect& srcRectR);
	void setDirection(Direction::Name dir);
	void setDirection(UnitAction& actionOther);
	void setDirection(double x, double y);
	void setFirstFrame();
	void setLastFrame();
	bool actionEnded();
	void updateFrame();

	void resetMove();

	void makeAttack(Unit* unit, std::list <AttackType*>& monsterAttacks, SDL_Point* attackPoint);
	void makeMove();

	UnitAction(Movement* move, AttackPattern* attack, int attackFrame);
	~UnitAction();
};

