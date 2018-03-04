#pragma once
#include "Item.h"
#include "SDL.h"

class Room;

class Field{
	SDL_Texture* background;
	Item* itemOnField;
	Room* roomParent;
public:
	SDL_Texture* getBackground() { return background; }

	void addTexture(SDL_Texture* txt);

	Field();
	Field(SDL_Texture* txt);
	Field(SDL_Texture* txt, Room* parent);
	Field(SDL_Texture* txt, Item*);
	~Field();

};

