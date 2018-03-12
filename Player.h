#pragma once
#include "Unit.h"

class Projectile;

class Player : public Unit {
	float attackSpeed;
	int attackFrames;
	int attackFrame;

	int rollCooldown;
	int lastRollFramesAgo;

	int rollSpeed = 10;
	SDL_Point rollVelocity;

	SDL_RendererFlip flip;
	SDL_Texture* playerStatsTxt;
	SDL_Rect statusSrcRect, statusDstRest;
public:
	void update(Map* map, SDL_Rect& fieldRect);
	void draw(SDL_Point* startRender) override;
	void movement(int x, int y);
	bool attackPossible();
	void attack(std::list <Projectile*>&, SDL_Texture*txt, int x, int y);

	void setAnimation(ActionType actionName);
	void resetAnimation();

	Player(SDL_Texture* txt, SDL_Texture* _playerStatsTxt);
	~Player();
};

