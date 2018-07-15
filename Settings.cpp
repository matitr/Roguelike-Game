#include "Settings.h"



Settings* Settings::instance = nullptr;


Settings* Settings::get() {
	if (!instance)
		instance = new Settings;

	return instance;
}

Settings::Settings() {
	showPlayerHp = 0;
	showEnemyHp = 1;
}


Settings::~Settings() {

}
