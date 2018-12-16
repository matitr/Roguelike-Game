#include "ScreenOptionsDisplay.h"
#include "SDL.h"
#include "ButtonCheckBox.h"
#include "Settings.h"


void ScreenOptionsDisplay::update() {
	setButtonValue(0, std::to_string((int)Settings::get()->getSettingDisplay(SettingsDisplay::ShowPlayerHp)));
	setButtonValue(1, std::to_string((int)Settings::get()->getSettingDisplay(SettingsDisplay::ShowEnemyHp)));
	setButtonValue(2, std::to_string(Settings::get()->getSettingDisplay(SettingsDisplay::ShowDamage)));
	setButtonValue(3, std::to_string(Settings::get()->getSettingDisplay(SettingsDisplay::ShowEnemyDamage)));

	Screen::update();
}

ScreenOptionsDisplay::ScreenOptionsDisplay(int windowResX, int windowResY) {
	float yPos = windowResY * 0.35;

	SDL_Rect r = {
		windowResX / 2,
		int(yPos),
		int(windowResX * 0.25),
		int(windowResY * 0.05),
	};
	float spaceY = 0.1 * windowResY;

	Button* button1 = new ButtonCheckBox(r, "Show player hp", [](Screen* parentScreen, ScreensManager* sM, Game* game)
	{ Settings::get()->setSettingDisplay(SettingsDisplay::ShowPlayerHp, !Settings::get()->getSettingDisplay(SettingsDisplay::ShowPlayerHp)); });
	addButton(button1);

	r.y = int(yPos + 1 * spaceY);
	Button* button2 = new ButtonCheckBox(r, "Show enemy hp", [](Screen* parentScreen, ScreensManager* sM, Game* game)
	{ Settings::get()->setSettingDisplay(SettingsDisplay::ShowEnemyHp, !Settings::get()->getSettingDisplay(SettingsDisplay::ShowEnemyHp)); });
	addButton(button2);

	r.y = int(yPos + 2 * spaceY);
	Button* button3 = new ButtonCheckBox(r, "Show damage", [](Screen* parentScreen, ScreensManager* sM, Game* game)
	{ Settings::get()->setSettingDisplay(SettingsDisplay::ShowDamage, !Settings::get()->getSettingDisplay(SettingsDisplay::ShowDamage)); });
	addButton(button3);

	r.y = int(yPos + 3 * spaceY);
	Button* button4 = new ButtonCheckBox(r, "Show enemy damage", [](Screen* parentScreen, ScreensManager* sM, Game* game)
	{ Settings::get()->setSettingDisplay(SettingsDisplay::ShowEnemyDamage, !Settings::get()->getSettingDisplay(SettingsDisplay::ShowEnemyDamage)); });
	addButton(button4);
}


ScreenOptionsDisplay::~ScreenOptionsDisplay() {

}
