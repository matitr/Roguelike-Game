#pragma once
#include "myMath.h"
#include <vector>

namespace SettingsDisplay {
	enum SettingsDisplay { ShowPlayerHp, ShowEnemyHp, ShowDamage, ShowEnemyDamage, enum_size };
}

class Settings {
	static Settings* instance;

	Settings();
	Settings(const Settings&) {}

	PointInt resolution;
	std::vector<bool> displaySettings;
public:
	static Settings* get();

	bool getSettingDisplay(SettingsDisplay::SettingsDisplay name) { return displaySettings[name]; }
	void setSettingDisplay(SettingsDisplay::SettingsDisplay name, bool toSet);

	~Settings();
};

