#pragma once
#include "Unit.h"
#include "Inventory.h"

#define ATTACK_POSSIBLE -1

class AttackType;

class Player : public Unit {
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
	MultipleProjectiles* attackP;
	bool attackCancel = false;
	bool attackSkip = false;

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

	void setAnimation(ActionType actionName);

	void changeInteractionBlock(bool block) { isInteractionBlocked = block; }
	bool interactionBlocked() { return isInteractionBlocked; }
	void cancelAttack();
	void skipAttack() { attackSkip = true; }

	Inventory& inventory() { return playerIntentory; }

	void addMoney(int m) { money += m; }
	int getMoney() { return money; }
	void takeMoney(int& m);

	Player(SDL_Texture* txt, SDL_Point& windowResolution);
	~Player();
};

