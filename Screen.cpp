#include "Screen.h"
#include "Button.h"
#include "Game.h"


void Screen::draw() {
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->draw();
}

Button* Screen::buttonUnderMouse() {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->mouseOverButton())
			return buttons[i];
	}

	return nullptr;
}

Screen::Screen() {

}


Screen::~Screen() {
	for (size_t i = 0; i < buttons.size(); i++)
		delete buttons[i];

	buttons.clear();
}
