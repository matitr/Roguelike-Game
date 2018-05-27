#pragma once
#include <list>
#include "Projectile.h"

class Movement;
class AttackPattern;
class Unit;

class UnitAction {
	Movement *movement;
	AttackPattern *attack;
	int yPosTexture;
	int frames;
	int frameTime;

	int attackFrame = 0;
	int framesInRow;
public:
	inline int texturePosY() { return yPosTexture; }
	inline int textureFrames() { return frames; }
	inline int textureFrameTime() { return frameTime; }
	inline int makeAttackFrame() { return attackFrame; }
	inline bool movementExists() { return movement ? true : false; }
	inline bool attackExists() { return attack ? true : false; }

	void makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks, SDL_Point* attackPoint);
	void makeMove(Unit* unitToMove);

	UnitAction(Movement* move, AttackPattern* attack, int yPosTexture, int frames, int frameTime, int attackFrame);
	~UnitAction();
};

