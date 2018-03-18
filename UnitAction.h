#pragma once
#include <list>
#include "Projectile.h"

enum ActionType;
class Movement;
class Attack;
class Unit;

class UnitAction {

	ActionType action;
	Movement *movement;
	Attack *attack;
	int yPosTexture;
	int frames;
	int frameTime;

	int attackFrame = 0;
	int currLoop = 0, loops;

public:
	inline int texturePosY() { return yPosTexture; }
	inline int textureFrames() { return frames; }
	inline int textureFrameTime() { return frameTime; }
	inline int makeAttackFrame() { return attackFrame; }
	void makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks);

	UnitAction(ActionType action, Movement* move, Attack* attack, int yPosTexture, int frames, int frameTime, int attackFrame, int loops);
	~UnitAction();
};

