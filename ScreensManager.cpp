#include "ScreensManager.h"
#include "EndScreen.h"
#include "ScreenPauseGame.h"
#include "ScreenMainmenu.h"
#include "Game.h"
#include "Input.h"
#include "Button.h"
#include <iostream>


bool ScreensManager::update(Game* game) {
	Screen* presentMainScreen = nullptr;
	for (std::vector<Screen*>::iterator it = screens.begin(); it != screens.end(); it++) {
		if ((*it)->showing())
			presentMainScreen = (*it);
	}

	if (presentMainScreen) {
		Button* selectedButton = nullptr;
		Screen* presentSubScreen = presentMainScreen->getPresentSubScreen();
		selectedButton = presentSubScreen->selectedButton();
		presentSubScreen->update();

		// Go to prev screen
		if (goBackKeyPressed && (screens[MainScreenName::Death] != presentSubScreen && screens[MainScreenName::MainMenu] != presentSubScreen)) {
			presentSubScreen->setShowing(false);
		}
		else if (selectedButton) {
			if ((Input::mousePressed[SDL_BUTTON_LEFT] && selectedButton->mouseOverButton()) || Input::keyPressed[SDL_SCANCODE_SPACE]) {
				selectedButton->actionOnClick(presentSubScreen, this, game);
			}
		}
	}
	else {
		if (goBackKeyPressed) {
			screens[MainScreenName::Pause]->setShowing(true);
		}
	}

	goBackKeyPressed = false;

	if (presentMainScreen && presentMainScreen->showing())
		return true;
	return false;
}

void ScreensManager::draw() {
	for (std::vector<Screen*>::iterator it = screens.begin(); it != screens.end(); it++)
		if ((*it)->showing()) {
			Screen* presentSubScreen = (*it)->getPresentSubScreen();
			drawBackground(*it);
			presentSubScreen->draw();
			return;
		}
}

void ScreensManager::drawBackground(Screen* screen) {
	if (screen == screens[MainScreenName::MainMenu]) {
		SDL_Rect r = { 0,0,10000,10000 };
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(Game::renderer, &r);
	}
	if (screen == screens[MainScreenName::Pause]) {
		SDL_Rect r = { 0,0,10000,10000 };
		SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(0, 0, 0, 0, 180);
		SDL_RenderFillRect(Game::renderer, &r);
		SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_NONE);
	}
}

void ScreensManager::setScreenVisible(MainScreenName::MainScreenName screenName, bool visible) {
	screens[screenName]->setShowing(visible);
}

bool ScreensManager::getVisibleScreen(MainScreenName::MainScreenName screenName) {
	return screens[screenName]->showing();
}

bool ScreensManager::noScreensVisible() {
	for (std::vector<Screen*>::iterator it = screens.begin(); it != screens.end(); it++)
		if ((*it)->showing())
			return false;

	return true;
}

void ScreensManager::hideAllScreens() {
	for (std::vector<Screen*>::iterator it = screens.begin(); it != screens.end(); it++)
		(*it)->setShowing(false);
}

void ScreensManager::setEndScreenStats(bool win, int score) {
	endScreen->setStats(win, score);
}

void ScreensManager::newGame(Game* game) {
	hideAllScreens();
	game->newGame();
}

void ScreensManager::quitGame(Game* game) {
	hideAllScreens();
	game->quitGame();
}

ScreensManager::ScreensManager(int windowResX, int windowResY) {
	endScreen = new EndScreen(windowResX, windowResY);

	screens.resize(MainScreenName::enum_size);
	screens[MainScreenName::MainMenu] = new ScreenMainMenu(windowResX, windowResY);
	screens[MainScreenName::Pause] = new ScreenPauseGame(windowResX, windowResY);
	screens[MainScreenName::Death] = endScreen;
}


ScreensManager::~ScreensManager() {
	for (std::vector<Screen*>::iterator it = screens.begin(); it != screens.end(); it++)
		delete (*it);
}
