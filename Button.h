#pragma once
#include "SDL.h"
#include <string>


class ScreensManager;
class Game;
class Screen;

class Button {
	SDL_Rect buttonRect;
	SDL_Rect dstRect;
	SDL_Texture* textTexture;

	std::string value;

	void(*onClickAction)(Screen* parentScreen, ScreensManager* screenManager, Game* game);

protected:
	void setTextDstRectX(int x) { dstRect.x = x; }
	void setTextDstRectY(int y) { dstRect.y = y; }
	SDL_Rect getTextDstRect() { return dstRect; }
	std::string getValue() { return value; }
public:
	virtual void draw();
	SDL_Rect getButtonRect() { return buttonRect; }
	void setValue(std::string valueToSet) { value = valueToSet; }
	
	bool mouseOverButton(); // Check if mouse if on button 
	void actionOnClick(Screen* parentScreen, ScreensManager* screenManager, Game* game); // Activate action

	Button(SDL_Rect dstR, const char* text, void(*onClickAction)(Screen* parentScreen, ScreensManager* screenManager, Game*));
	~Button();
};

