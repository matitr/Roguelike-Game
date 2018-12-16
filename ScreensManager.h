#pragma once
#include "SDL.h"
#include <vector>


namespace MainScreenName {
	enum MainScreenName { MainMenu, Pause, Death, enum_size };
}

class Screen;
class EndScreen;
class Game;

class ScreensManager {
	EndScreen* endScreen = nullptr;

	std::vector<Screen*> screens;

	bool goBackKeyPressed = false;

	void drawBackground(Screen* screen);
public:
	bool update(Game* game);
	void draw();

	void setGoBackScreen() { goBackKeyPressed = true; }

	void setScreenVisible(MainScreenName::MainScreenName screenName, bool visible);
	bool getVisibleScreen(MainScreenName::MainScreenName screenName);
	bool noScreensVisible();
	void hideAllScreens();

	void setEndScreenStats(bool win, int score);

	// Actions
	void newGame(Game* game);
	void quitGame(Game* game);

	ScreensManager(int windowResX, int windowResY);
	~ScreensManager();
};

typedef void (ScreensManager::*tP)(Game*);
