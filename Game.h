#pragma once
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <list>
#include "UpdateCollision.h"
#include "ScreensManager.h"

class InteractiveObject;
class Map;
class Player;
class GameObject;

class Game{

	SDL_Window* window;
	UpdateCollision collision;
	ScreensManager* screensManager;

	int FPS;
	Map* map;
	bool _running;
	
	SDL_Point windowResolution;

	Player* player;
	std::list <Unit*>* monsters;
	std::list <AttackType*> playerProjectiles;
	std::list <AttackType*> monsterAttacks;

	std::vector <GameObject*> gameObjects;
	std::vector <InteractiveObject*>* interactiveObjects;

	std::unordered_map <SDL_Scancode, InteractiveObject*> objectSelected;

	void handleEvents();
	void updateGame();
	void updateUnits();
	void updateGameProjectiles();

	inline bool running() { return _running; }
public:
	static SDL_Renderer* renderer;

	void run();

	void newGame();
	void quitGame();

	Game(int, int, bool);
	~Game();
};

