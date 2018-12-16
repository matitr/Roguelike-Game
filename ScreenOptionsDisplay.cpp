#include "ScreenOptionsDisplay.h"
#include "SDL.h"
#include "Button.h"
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
		int(windowResX * 0.2),
		int(windowResY * 0.05),
	};
	float spaceY = 0.1 * windowResY;

	Button* button1 = new Button(r, "Show player hp", [](Screen* parentScreen, ScreensManager* sM, Game* game)
	{ Settings::get()->setSettingDisplay(SettingsDisplay::ShowPlayerHp, !Settings::get()->getSettingDisplay(SettingsDisplay::ShowPlayerHp)); });
	button1->setButtonType(ButtonType::Boolean);
	addButton(button1);

	r.y = int(yPos + 1 * spaceY);
	Button* button2 = new Button(r, "Show enemy hp", [](Screen* parentScreen, ScreensManager* sM, Game* game)
	{ Settings::get()->setSettingDisplay(SettingsDisplay::ShowEnemyHp, !Settings::get()->getSettingDisplay(SettingsDisplay::ShowEnemyHp)); });
	button2->setButtonType(ButtonType::Boolean);
	addButton(button2);

	r.y = int(yPos + 2 * spaceY);
	Button* button3 = new Button(r, "Show damage", [](Screen* parentScreen, ScreensManager* sM, Game* game)
	{ Settings::get()->setSettingDisplay(SettingsDisplay::ShowDamage, !Settings::get()->getSettingDisplay(SettingsDisplay::ShowDamage)); });
	button3->setButtonType(ButtonType::Boolean);
	addButton(button3);

	r.y = int(yPos + 3 * spaceY);
	Button* button4 = new Button(r, "Show enemy damage", [](Screen* parentScreen, ScreensManager* sM, Game* game)
	{ Settings::get()->setSettingDisplay(SettingsDisplay::ShowEnemyDamage, !Settings::get()->getSettingDisplay(SettingsDisplay::ShowEnemyDamage)); });
	button4->setButtonType(ButtonType::Boolean);
	addButton(button4);
}


ScreenOptionsDisplay::~ScreenOptionsDisplay() {

}
