#include "ScreenOptions.h"
#include "ScreenOptionsDisplay.h"
#include "SDL.h"
#include "Button.h"


ScreenOptions::ScreenOptions(int windowResX, int windowResY) {
	addSubScreen(SubScreenName::OptionsDisplay, new ScreenOptionsDisplay(windowResX, windowResY));
//	subScreens[SubScreenName::OptionsDisplay] = new ScreenOptionsDisplay();

	float yPos = windowResY * 0.35;

	SDL_Rect r = {
		windowResX / 2,
		int(yPos),
		int(windowResX * 0.2),
		int(windowResY * 0.05),
	};
	float spaceY = 0.1 * windowResY;

	addButton(new Button(r, "Display", [](Screen* parentScreen, ScreensManager* sM, Game* game)
		{ parentScreen->setShowingSubScreen(SubScreenName::OptionsDisplay, true); }));
	r.y = int(yPos + 1 * spaceY);
}


ScreenOptions::~ScreenOptions() {

}
