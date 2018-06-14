#include "ScreensManager.h"
#include "EndScreen.h"
#include "Game.h"
#include "Input.h"
#include "Button.h"
#include <iostream>

void ScreensManager::update(Game* game) {
	if (endScreen->showing()) {
		Button* buttonUnderMouse = endScreen->buttonUnderMouse();

		if (buttonUnderMouse) {
			if (Input::mousePressed[SDL_BUTTON_LEFT]) {
				buttonUnderMouse->actionOnClick(this, game);
			}
		}
	}
}

void ScreensManager::draw() {
	if (endScreen->showing())
		endScreen->draw();
}

void ScreensManager::newGame(Game* game) {
	game->newGame();
	endScreen->setShowing(false);
}

void ScreensManager::quitGame(Game* game) {
	game->quitGame();
	endScreen->setShowing(false);
}

ScreensManager::ScreensManager(int windowResX, int windowResY) {
	endScreen = new EndScreen(windowResX, windowResY);
}


ScreensManager::~ScreensManager() {
	delete endScreen;
}
