#pragma once
#include "SDL.h"
#include "Map.h"
#include <unordered_map>
#include <vector>
#include "Player.h"



class Game{

	SDL_Window* window;

	int FPS;
	Map* map;
	bool _running;
	const Uint8* keystates;
	int cameraMovePix;
	SDL_Rect srcRectUnit, dstRectUnit;
	std::vector <Unit*> units;
public:
	static SDL_Renderer* renderer;

	void run();
	void handleEvents();
	void render();

	inline bool running() { return _running; }

	Game(const char* title, int, int, bool);
	~Game();
};

