#pragma once
#include <list>
#include "Projectile.h"
#include "TextureManager.h"

class Movement;
class AttackPattern;
class Unit;

class UnitAction {
	Movement *movement;
	AttackPattern *attack;
	std::vector<SpriteAnimation*> animations;

	int attackFrame = 0;
	Direction::Name currentDirection;
public:
//	inline int texturePosY() { return yPosTexture; }
//	inline int textureFrames() { return frames; }
//	inline int textureFrameTime() { return frameTime; }

	inline int makeAttackFrame() { return attackFrame; }
	inline bool movementExists() { return movement ? true : false; }
	inline bool attackExists() { return attack ? true : false; }
	Direction::Name getDirection() { return currentDirection; }

	void addAnimation(Direction::Name dir, AnimationDetails& animationData, SDL_Rect& srcRectR);
	void setDirection(Direction::Name dir);
	void setFirstFrame();
	void setLastFrame();
	bool actionEnded();
	void updateFrame();

	void makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks, SDL_Point* attackPoint);
	void makeMove(Unit* unitToMove);

	UnitAction(Movement* move, AttackPattern* attack, int attackFrame);
	~UnitAction();
};

