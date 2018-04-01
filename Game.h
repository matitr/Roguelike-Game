#pragma once
#include "SDL.h"
#include "Map.h"
#include <unordered_map>
#include <vector>
#include <list>
#include "Player.h"



class Game{

	SDL_Window* window;

	int FPS;
	Map* map;
	bool _running;
	const Uint8* keystates;
	int cameraMovePix;
	Player* player;
	std::list <Unit*> monsters;
	std::list <Projectile*> playerProjectiles;
	std::list <Projectile*> monsterAttacks;

	std::list<Projectile*>::iterator it = playerProjectiles.begin();
	std::list<Projectile*>::iterator tempItProjectile;
	std::list<Unit*>::iterator tempItMonster;
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

