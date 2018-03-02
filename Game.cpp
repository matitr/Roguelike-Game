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

	map->generateNewMap();//temp
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
	SDL_Event event;
	SDL_PollEvent(&event);

	if (keystates[SDL_SCANCODE_W]) {
		if (keystates[SDL_SCANCODE_A])
			map->moveCamera(-1 * cameraMovePix, -1 * cameraMovePix);
		else if (keystates[SDL_SCANCODE_D])
			map->moveCamera(cameraMovePix, -1 * cameraMovePix);
		else
			map->moveCamera(0, -1 * cameraMovePix);
	}
	else if (keystates[SDL_SCANCODE_S]) {
		if (keystates[SDL_SCANCODE_A])
			map->moveCamera(-1 * cameraMovePix, cameraMovePix);
		else if (keystates[SDL_SCANCODE_D])
			map->moveCamera(cameraMovePix, cameraMovePix);
		else
			map->moveCamera(0, cameraMovePix);
	}
	else if (keystates[SDL_SCANCODE_A]) {
		if (keystates[SDL_SCANCODE_W])
			map->moveCamera(-1* cameraMovePix, -1 * cameraMovePix);
		else if (keystates[SDL_SCANCODE_S])
			map->moveCamera(-1 * cameraMovePix, cameraMovePix);
		else
			map->moveCamera(-1 * cameraMovePix, 0);
	}
	else if (keystates[SDL_SCANCODE_D]) {
		if (keystates[SDL_SCANCODE_W])
			map->moveCamera(cameraMovePix, -1 * cameraMovePix);
		else if (keystates[SDL_SCANCODE_S])
			map->moveCamera(cameraMovePix, cameraMovePix);
		else
			map->moveCamera(cameraMovePix, 0);
	}


	switch (event.type) {
		case SDL_QUIT:
			break;
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->render();



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
	FPS = 6;
	cameraMovePix = 5;
	_running = true;
}


Game::~Game() {

}