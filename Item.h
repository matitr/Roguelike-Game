#pragma once
#include "SDL.h"

class Item{
	SDL_Texture* texture;
	int quantity, maxQuantity;

public:

	Item(SDL_Texture*, int numberOfItems, int maxNumber);
	~Item();
};

