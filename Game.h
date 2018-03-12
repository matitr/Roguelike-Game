#pragma once
#include "SDL.h"
#include "Map.h"
#include <unordered_map>
#include <vector>
#include <list>
#include "Player.h"
#include "Projectile.h"



class Game{

	SDL_Window* window;

	int FPS;
	Map* map;
	bool _running;
	const Uint8* keystates;
	int cameraMovePix;
	SDL_Rect srcRectUnit, dstRectUnit;
	Player* player;
	std::list <Unit*> units;
	std::list <Projectile*> playerProjectiles;
	std::list <Projectile*> mobsProjectiles;

	std::list<Projectile*>::iterator it = playerProjectiles.begin();
	std::list<Projectile*>::iterator tempItProjectile;
public:
	static SDL_Renderer* renderer;

	void run();
	void handleEvents();
	void render();

	inline bool running() { return _running; }

	Game(const char* title, int, int, bool);
	~Game();
};

