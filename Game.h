#pragma once
#include "SDL.h"
#include "Map.h"
#include <unordered_map>
#include <vector>
#include <list>
#include "Player.h"
#include "UpdateCollision.h"

class InteractiveObject;

class Game{

	SDL_Window* window;
	UpdateCollision collision;

	int FPS;
	Map* map;
	bool _running;
	
	int cameraMovePix;
	SDL_Point windowResolution;

	Player* player;
	std::list <Unit*>* monsters;
	std::list <Projectile*> playerProjectiles;
	std::list <Projectile*> monsterAttacks;

	std::vector <GameObject*> gameObjects;
	std::vector <InteractiveObject*>* interactiveObjects;

	std::unordered_map <SDL_Scancode, InteractiveObject*> objectSelected;

public:
	static SDL_Renderer* renderer;

	void run();
	void handleEvents();
	void updateGame();
	void updateGameProjectiles();

	inline bool running() { return _running; }

	Game(const char* title, int, int, bool);
	~Game();
};

