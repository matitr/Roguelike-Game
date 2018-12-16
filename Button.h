#pragma once
#include "SDL.h"
#include <string>

namespace ButtonType {
	enum ButtonType { Text, Boolean };
}

class ScreensManager;
class Game;
class Screen;

class Button {
	SDL_Rect buttonRect;
	SDL_Rect dstRect;
	SDL_Texture* textTexture;

	std::string value;
	ButtonType::ButtonType buttonType;

	void(*onClickAction)(Screen* parentScreen, ScreensManager* screenManager, Game* game);
//	void (ScreensManager::*onClickAction)(Game*);
public:
	void draw();
	SDL_Rect getButtonRect() { return buttonRect; }
	void setValue(std::string valueToSet) { value = valueToSet; }
	void setButtonType(ButtonType::ButtonType type);
	
	bool mouseOverButton(); // Check if mouse if on button 
	void actionOnClick(Screen* parentScreen, ScreensManager* screenManager, Game* game); // Activate action

//	Button(SDL_Rect dstR, const char* text, void (ScreensManager::*action)(Game*));
	Button(SDL_Rect dstR, const char* text, void(*onClickAction)(Screen* parentScreen, ScreensManager* screenManager, Game*));
	~Button();
};

