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
	
	bool mouseOverButton(); // Check if mouse if on button 
	void actionOnClick(ScreensManager* screenManager, Game* game); // Activate action

	Button(SDL_Rect dstR, const char* text, void (ScreensManager::*action)(Game*));
	~Button();
};

