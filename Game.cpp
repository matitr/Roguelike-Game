#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <time.h>

SDL_Renderer *Game::renderer = nullptr;;

void Game::run() {
	Uint32 frameStart;
	int frameTime;
	int frameDelay = 1000 / FPS;
	time_t timeCounter = clock();
	int frameCounter=0;
	TextureManager::loadAllTextures();

	map->generateNewMap();
	map->setFieldsPositions();
	player = new Player(TextureManager::textures[PLAYER], TextureManager::textures[PLAYER_STATS]);
	player->setPosition(map->getCameraX(), map->getCameraY());
	player->setAnimation(Walk);
	player->setAnimation(Stand);
	while (running()) {
		if (clock() - timeCounter > CLOCKS_PER_SEC) {
			std::cout << frameCounter << std::endl;
			frameCounter = 0;
			timeCounter = clock();
		}

		frameStart = SDL_GetTicks();
		handleEvents();
		render();

		frameCounter++;

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

}

void Game::handleEvents() {
	SDL_PumpEvents();
	
	player->velocity.x = 0;
	player->velocity.y = 0;

	if (keystates[SDL_SCANCODE_W]) {
		player->velocity.y += -1;
		player->setAnimation(Walk);
	}
	if (keystates[SDL_SCANCODE_S]) {
		player->velocity.y += 1;
		player->setAnimation(Walk);
	}
	if (keystates[SDL_SCANCODE_A]) {
		player->velocity.x += -1;
		player->setAnimation(Walk);
	}
	if (keystates[SDL_SCANCODE_D]) {
		player->velocity.x += 1;
		player->setAnimation(Walk);
	}
	if (keystates[SDL_SCANCODE_SPACE]) {
		player->setAnimation(Roll);
	}
	
	if (!player->velocity.y && !player->velocity.x)
		player->setAnimation(Stand);

	int x, y;

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if (player->attackPossible())
			player->attack(playerProjectiles, TextureManager::textures[PROJECTILES], x + map->startRender.x, y + map->startRender.y);
	}
}

void Game::render() {
	SDL_RenderClear(renderer);

	player->update(map, map->fieldRect);
	player->drawStatus();

	if (!map->currentRoom()->visited && map->currentRoom()->battle) {
		map->currentRoom()->setVisited(true);
		map->currentRoom()->spawnMonsters(monsters);
	}

	map->render();
	std::list <Unit*>::iterator it_monsters = monsters.begin();

	while (it_monsters != monsters.end()) {
		(*it_monsters)->update(monsterAttacks, map, map->fieldRect);
		(*it_monsters)->draw(&map->startRender);
		it_monsters++;
	}

	it = monsterAttacks.begin();
	while (it != monsterAttacks.end()) {
		if (*it) {
			if (!(*it)->update(map, map->fieldRect)) {
				delete (*it);
				tempItProjectile = it;
				it++;
				monsterAttacks.erase(tempItProjectile);
			}
			else {
				(*it)->draw(&map->startRender);
				it++;
			}
		}
	}

	player->draw(&map->startRender);

	it = playerProjectiles.begin();

	while (it != playerProjectiles.end()) {
		if (*it) {
			if (!(*it)->update(map, map->fieldRect)) {
				delete (*it);
				tempItProjectile = it;
				it++;
				playerProjectiles.erase(tempItProjectile);
			}
			else {
				(*it)->draw(&map->startRender);
				it++;
			}
		}
	}


	SDL_RenderPresent(renderer);
}

Game::Game(const char* title, int w, int h, bool fullscreen) {
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
	renderer = SDL_CreateRenderer(window, -1, 0);

	map = new Map(h / 2, w / 2);

	keystates = SDL_GetKeyboardState(NULL);
	FPS = 60;
	cameraMovePix = 5;
	_running = true;
}


Game::~Game() {

}