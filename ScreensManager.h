#pragma once
#include "SDL.h"

enum class ScreenName { Death };

class EndScreen;
class Game;
class ScreensManager {
	EndScreen* endScreen = nullptr;

public:
	EndScreen* getEndScreen() { return endScreen; }

	void update(Game* game);
	void draw();

	// Actions
	void newGame(Game* game);
	void quitGame(Game* game);

	ScreensManager(int windowResX, int windowResY);
	~ScreensManager();
};

typedef void (ScreensManager::*tP)(Game*);
