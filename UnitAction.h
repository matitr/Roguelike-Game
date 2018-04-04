#pragma once
#include <list>
#include "Projectile.h"

class Movement;
class Attack;
class Unit;

class UnitAction {
	Movement *movement;
	Attack *attack;
	int yPosTexture;
	int frames;
	int frameTime;

	int attackFrame = 0;

public:
	inline int texturePosY() { return yPosTexture; }
	inline int textureFrames() { return frames; }
	inline int textureFrameTime() { return frameTime; }
	inline int makeAttackFrame() { return attackFrame; }
	inline bool movementExists() { return movement ? true : false; }
	inline bool attackExists() { return movement ? true : false; }

	void makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks);
	void makeMove(Unit* unitToMove);

	UnitAction(Movement* move, Attack* attack, int yPosTexture, int frames, int frameTime, int attackFrame);
	~UnitAction();
};

