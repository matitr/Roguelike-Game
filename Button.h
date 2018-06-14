#pragma once
#include "SDL.h"

class ScreensManager;
class Game;

class Button {
	SDL_Rect buttonRect;
	SDL_Rect dstRect;
	SDL_Texture* textTexture;

	void (ScreensManager::*onClickAction)(Game*);
public:
	void draw();
	
	bool mouseOverButton();
	void actionOnClick(ScreensManager* screenManager, Game* game);

	Button(SDL_Rect dstR, const char* text, void (ScreensManager::*action)(Game*));
	~Button();
};

