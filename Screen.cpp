#include "Screen.h"
#include "Button.h"
#include "Game.h"
#include "Input.h"


void Screen::update() {
	if (Input::keyPressed[SDL_SCANCODE_W]) {
		if (selectedButtonIt - 1 >= 0)
			selectedButtonIt--;
	}
	if (Input::keyPressed[SDL_SCANCODE_S]) {
		if (selectedButtonIt + 1 < buttons.size())
			selectedButtonIt++;
	}

	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->mouseOverButton())
			selectedButtonIt = i;
	}
}

void Screen::draw() {
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->draw();


	// Draw rect on selected button
	if (!buttons.empty()) {
		SDL_SetRenderDrawColor(Game::renderer, 0, 153, 0, 255);
		SDL_Rect buttonRect = buttons[selectedButtonIt]->getButtonRect();
		SDL_RenderDrawRect(Game::renderer, &buttonRect);
	}
}

void Screen::setButtonValue(int buttonIt, std::string valueToSet) {
	buttons[buttonIt]->setValue(valueToSet);
}

void Screen::setShowing(bool toSet) {
	if (!toSet) {
		for (std::unordered_map<SubScreenName::SubScreenName, Screen*>::iterator it = subScreens.begin(); it != subScreens.end(); it++)
			it->second->setShowing(false);

		selectedButtonIt = 0;
	}

	isShowing = toSet;
}

void Screen::setShowingSubScreen(SubScreenName::SubScreenName name, bool toSet) {
	if (subScreens.find(name) != subScreens.end()) 
		subScreens[name]->setShowing(toSet);
}

Screen* Screen::getPresentSubScreen() {
	for (std::unordered_map<SubScreenName::SubScreenName, Screen*>::iterator it = subScreens.begin(); it != subScreens.end(); it++) {
		if (it->second->showing()) {
			return it->second->getPresentSubScreen();
		}
	}

	return this;
}

Button* Screen::selectedButton() {
	if (buttons.empty())
		return nullptr;
	else
		return buttons[selectedButtonIt];
}

Screen::Screen() {

}


Screen::~Screen() {
	for (size_t i = 0; i < buttons.size(); i++)
		delete buttons[i];

	for (auto it = subScreens.begin(); it != subScreens.end(); it++)
		delete (it->second);
}
