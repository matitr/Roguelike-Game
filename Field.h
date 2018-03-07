#pragma once
#include "Item.h"
#include "SDL.h"

class Room;

class Field{
	SDL_Texture* texture;
	bool isGround = false;
public:
	SDL_Texture * getTexture() { return texture; }
	bool ground() { return isGround; }

	Field();
	Field(SDL_Texture* txt);
	Field(SDL_Texture* txt, bool _ground);
	Field(SDL_Texture* txt, SDL_Rect* rectSize, int frames, int frameTime);
	~Field();

};

