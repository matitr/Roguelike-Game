#pragma once
#include "Unit.h"

class Player : public Unit {

public:
	void update(Map* map, SDL_Rect& fieldRect);

	void movement(int x, int y);

	Player(SDL_Texture* txt);
	~Player();
};

