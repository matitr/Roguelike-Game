#pragma once
#include "SDL.h"
#include "Map.h"
#include <unordered_map>



class Game{

	SDL_Window* window;
	std::unordered_map <int, SDL_Texture*> textures;

	int FPS;
	Map* map;
	bool _running;
	const Uint8* keystates;
	int cameraMovePix;
public:
	static SDL_Renderer* renderer;

	void run();
	void handleEvents();
	void render();

	inline bool running() { return _running; }

	Game(const char* title, int, int, bool);
	~Game();
};

