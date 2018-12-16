#include "ScreenPauseGame.h"
#include "SDL.h"
#include "Button.h"
#include "ScreensManager.h"
#include "ScreenOptions.h"
#include "Game.h"


void ScreenPauseGame::draw() {
	Screen::draw();
}

ScreenPauseGame::ScreenPauseGame(int windowResX, int windowResY) {
	addSubScreen(SubScreenName::Options, new ScreenOptions(windowResX, windowResY));
//	subScreens[SubScreenName::Options] = new ScreenOptions(windowResX, windowResY);

	float yPos = windowResY * 0.35;

	SDL_Rect r = {
		windowResX / 2,
		int(yPos),
		int(windowResX * 0.2),
		int(windowResY * 0.05),
	};
	float spaceY = 0.1 * windowResY;

	addButton(new Button(r, "Resume", [](Screen* parentScreen, ScreensManager* sM, Game* game) { parentScreen->setShowing(false); }));

	r.y = int(yPos + 1 * spaceY);
	addButton(new Button(r, "New game", [](Screen* parentScreen, ScreensManager* sM, Game* game) { sM->newGame(game); }));

	r.y = int(yPos + 2 * spaceY);
	addButton(new Button(r, "Options", [](Screen* parentScreen, ScreensManager* sM, Game* game)
		{ parentScreen->setShowingSubScreen(SubScreenName::Options, true); }));

	r.y = int(yPos + 3 * spaceY);
	addButton(new Button(r, "Main menu", [](Screen* parentScreen, ScreensManager* sM, Game* game)
	{ sM->setScreenVisible(MainScreenName::MainMenu, true); parentScreen->setShowing(false); }));

	r.y = int(yPos + 4 * spaceY);
	addButton(new Button(r, "Quit game", [](Screen* parentScreen, ScreensManager* sM, Game* game) { sM->quitGame(game); }));
}


ScreenPauseGame::~ScreenPauseGame() {

}
