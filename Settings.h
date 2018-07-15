#pragma once
#include "myMath.h"


class Settings {
	static Settings* instance;

	Settings();
	Settings(const Settings&) {}
public:
	static Settings* get();

	PointInt resolution;
	bool showPlayerHp;
	bool showEnemyHp;





	~Settings();
};

