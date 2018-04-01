#pragma once
#include "Unit.h"

class Projectile;

class Player : public Unit {
	std::unordered_map <ActionType, Animation*> animations;
	ActionType unitActionName;

	float attackSpeed;
	int attackFrames;
	int attackFrame;

	int rollCooldown;
	int lastRollFramesAgo;

	int rollSpeed;
	SDL_Point rollVelocity;

	SDL_Texture* playerStatsTxt;
	SDL_Rect statusSrcRect, statusDstRest;
public:
	bool update(Map* map, SDL_Rect& fieldRect);
	void drawStatus();
	void movement(int x, int y);
	bool attackPossible();
	void attack(std::list <Projectile*>&, SDL_Texture*txt, int x, int y);

	void addAnimation(ActionType actionName, int _yPosTexture, int _frames, int _frameTime);
	void setAnimation(ActionType actionName);
	void resetAnimation();

	Player(SDL_Texture* txt, SDL_Texture* _playerStatsTxt);
	~Player();
};

