#pragma once
#include "SDL.h"
#include <unordered_map>


class Input {

public:
	static int numbOfKeys;

	static const Uint8* keystates;
	static std::vector<bool> keyPressed;

	static std::vector<bool> mouseStates;
	static std::vector<bool> mousePressed;

	static int mousePosX;
	static int mousePosY;
	static bool quit;

	static void update(); // Update mouse and keyboard events


	Input();
	~Input();
};

