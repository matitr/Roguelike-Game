#include "Settings.h"



Settings* Settings::instance = nullptr;


Settings* Settings::get() {
	if (!instance)
		instance = new Settings;

	return instance;
}

void Settings::setSettingDisplay(SettingsDisplay::SettingsDisplay name, bool toSet) {
	displaySettings[name] = toSet;
}

Settings::Settings() {
	displaySettings.resize(SettingsDisplay::enum_size);

	displaySettings[SettingsDisplay::ShowPlayerHp] = false;
	displaySettings[SettingsDisplay::ShowEnemyHp] = true;
	displaySettings[SettingsDisplay::ShowDamage] = true;
	displaySettings[SettingsDisplay::ShowEnemyDamage] = true;
}


Settings::~Settings() {

}
