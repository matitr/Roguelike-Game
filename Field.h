#pragma once
#include "Item.h"
#include "SDL.h"

class Room;

class Field{
	SDL_Texture* texture;
public:
	SDL_Texture * getTexture() { return texture; }

	Field();
	Field(SDL_Texture* txt);
	Field(SDL_Texture* txt, SDL_Rect* rectSize, int frames, int frameTime);
	~Field();

};

