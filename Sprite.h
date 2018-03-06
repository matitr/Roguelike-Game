#pragma once
#include "SDL.h"



class Sprite {
protected:

	SDL_Texture* texture;

public:
	virtual void draw(SDL_Rect& disRect);

	Sprite(SDL_Texture* txt);
	~Sprite();
};

