#include "Input.h"
#include <iostream>

int Input::numbOfKeys;
const Uint8* Input::keystates = SDL_GetKeyboardState(&Input::numbOfKeys);
std::vector<bool> Input::keyPressed(Input::numbOfKeys);

std::vector<bool> Input::mouseStates(4);
std::vector<bool> Input::mousePressed(4);

int Input::mousePosX;
int Input::mousePosY;

bool Input::quit;


void Input::update() {
	for (int i = 0; i < Input::numbOfKeys; i++) {
		keyPressed[i] = false;
	}

	SDL_Event event;
	event.key.repeat = 0;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit =1;
			break;
		case SDL_KEYDOWN:
			if (!event.key.repeat)
				keyPressed[event.key.keysym.scancode] = true;
			break;
		default:
			break;
		}
	}

	mousePressed[SDL_BUTTON_LEFT] = false;
	mousePressed[SDL_BUTTON_MIDDLE] = false;
	mousePressed[SDL_BUTTON_RIGHT] = false;
	bool mouseClick = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);

	if (mouseClick && !mouseStates[SDL_BUTTON_LEFT])
		mousePressed[SDL_BUTTON_LEFT] = true;
	mouseStates[SDL_BUTTON_LEFT] = mouseClick;
	
	mouseClick = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE);


	if (mouseClick && !mouseStates[SDL_BUTTON_MIDDLE])
		mousePressed[SDL_BUTTON_MIDDLE] = true;
	mouseStates[SDL_BUTTON_MIDDLE] = mouseClick;


	mouseClick = SDL_GetMouseState(&mousePosX, &mousePosY) & SDL_BUTTON(SDL_BUTTON_RIGHT);

	if (mouseClick && !mouseStates[SDL_BUTTON_RIGHT])
		mousePressed[SDL_BUTTON_RIGHT] = true;
	mouseStates[SDL_BUTTON_RIGHT] = mouseClick;
}

Input::Input() {

}


Input::~Input() {

}
