#pragma once
#include "Unit.h"
class Player : public Unit {

public:
	void movement(int x, int y);

	Player(SDL_Texture* txt);
	~Player();
};

