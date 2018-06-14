#pragma once
#include "Unit.h"
#include "Inventory.h"

#define ATTACK_POSSIBLE -1

class AttackType;

class Player : public Unit {
	std::unordered_map <ActionType, Animation*> animations;
	int textureY = 0, textureFrame = 0, textureFrameTime = 100, textureFrames = 2, frameCounter = 0, textureFramesInRow;

	float attackSpeed;
	int attackFrames;
	int attackFrame;

	int rollCooldown;
	int lastRollFramesAgo;

	int rollSpeed;
	PointDouble rollVelocity;

	SDL_Texture* playerStatsTxt;
	SDL_Rect statusSrcRect, statusDstRest;

	int attack;
	SDL_Point attackPos;
	MultipleProjectiles* attackP;
	bool attackCancel = false;

	bool isInteractionBlocked = false;

	Inventory playerIntentory;
	int money;
public:
	bool update(std::list <AttackType*>&, Map* map, SDL_Rect& fieldRect);
	void drawStatus();
	void movement(int x, int y);
	bool attackPossible();
	void attackPressed(int x, int y);
	void makeAttack(std::list <AttackType*>&, AnimationDetails& animationD);

//	void addAnimation(ActionType actionName, int _yPosTexture, int _frames, int _frameTime);
	void setAnimation(ActionType actionName);
	void resetAnimation();

	void changeInteractionBlock(bool block) { isInteractionBlocked = block; }
	bool interactionBlocked() { return isInteractionBlocked; }
	void cancelAttack();

	Inventory& inventory() { return playerIntentory; }

	bool alive() { return hp > 0 ? true : false; }
	void addMoney(int m) { money += m; }
	int getMoney() { return money; }
	void takeMoney(int& m);

	Player(SDL_Texture* txt, SDL_Point& windowResolution);
	~Player();
};

