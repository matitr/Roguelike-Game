#pragma once
#include "Screen.h"


class ScreenPauseGame : public Screen {

public:
	void draw() override;

	ScreenPauseGame(int windowResX, int windowResY);
	~ScreenPauseGame();
};

