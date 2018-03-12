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

	map->generateNewMap();
	map->setFieldsPositions();
	player = new Player(map->textures[PLAYER], map->textures[PLAYER_STATS]);
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
			player->attack(playerProjectiles, map->textures[PROJECTILES], x + map->startRender.x, y + map->startRender.y);
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->render();


	player->update(map, map->fieldRect);
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