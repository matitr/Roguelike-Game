#pragma once
#include "Screen.h"


class ScreenOptionsDisplay : public Screen {

public:
	void update() override;

	ScreenOptionsDisplay(int windowResX, int windowResY);
	~ScreenOptionsDisplay();
};

