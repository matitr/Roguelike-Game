#pragma once
#include "Button.h"


class ButtonCheckBox : public Button {


public:
	void draw() override;

	ButtonCheckBox(SDL_Rect dstR, const char* text, void(*onClickAction)(Screen* parentScreen, ScreensManager* screenManager, Game*));
	~ButtonCheckBox();
};

