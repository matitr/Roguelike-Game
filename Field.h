#pragma once
#include "Item.h"
#include "SDL.h"

class Field{
	SDL_Texture* background;
	Item* itemOnField;

public:
	SDL_Texture* getBackground() { return background; }

	void addTexture(SDL_Texture* txt);

	Field();
	Field(SDL_Texture* txt);
	Field(SDL_Texture* txt, Item*);
	~Field();

};

