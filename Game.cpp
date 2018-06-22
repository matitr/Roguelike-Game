#include "Game.h"
#include "TextureManager.h"
#include "DataBase.h"
#include <iostream>
#include <time.h>
#include "Monsters.h"
#include "InteractiveObject.h"
#include "Input.h"
#include "GameObject.h"
#include <chrono>
#include <typeinfo>
#include <thread>
#include "Player.h"
#include "Map.h"
#include "EndScreen.h"

#include "Money.h"
#include "Chest.h"
#include "Item.h"

typedef std::chrono::high_resolution_clock Clock;
SDL_Renderer *Game::renderer = nullptr;

void Game::run() {
	srand(88888888);
	auto frameStart = Clock::now();
	double frameTime;
	double frameDelay = 1000000000.0 / FPS;
	time_t timeCounter = clock();
	int frameCounter=0;
	TextureManager::loadAllTextures();
	DataBase::loadAllDataBases();
	screensManager = new ScreensManager(windowResolution.x, windowResolution.y);

	player = new Player(TextureManager::textures[TextureFile::PLAYER], windowResolution);
	map = new Map(player, windowResolution.y / 2, windowResolution.x / 2);

	map->generateNewLevel();
	map->currentRoom()->getRoomObjects(monsters, interactiveObjects);
	map->setFieldsPositions();
	player->setPosition(map->getCameraX(), map->getCameraY());

	interactiveObjects->push_back(new Item(ItemName::Item3, player->getPositionX() + 5, player->getPositionY() + 5));

	while (running()) {
		if (clock() - timeCounter > CLOCKS_PER_SEC) {
			std::cout << frameCounter << std::endl;
			frameCounter = 0;
			timeCounter = clock() - timeCounter - CLOCKS_PER_SEC + clock();
		}

		frameStart = Clock::now();
		handleEvents();
		if (player->alive()) 
			updateGame();

		screensManager->update(this);
		screensManager->draw();
		SDL_RenderPresent(renderer);

		frameCounter++;

		frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - frameStart).count();
		if (frameDelay > frameTime) { // Frames limit
			std::this_thread::sleep_for(std::chrono::nanoseconds(int(frameDelay - frameTime) + 100000));
		}
	}
	TextureManager::clearData();
	DataBase::clearData();
	TTF_Quit();
	SDL_Quit();
}

void Game::handleEvents() {
	std::unordered_map <SDL_Scancode, InteractiveObject*>::iterator it_objectSelected;
	Input::update();

	if( Input::quit)
		_running = 0;
	else {
		for (it_objectSelected = objectSelected.begin(); it_objectSelected != objectSelected.end(); it_objectSelected++) {
			if (Input::keyPressed[it_objectSelected->first]) { // Interaction on key detected
				if (objectSelected.find(it_objectSelected->first) != objectSelected.end() && objectSelected[it_objectSelected->first] && !objectSelected[it_objectSelected->first]->interacting()) {
					objectSelected[it_objectSelected->first]->onPlayerInteract(map, (*interactiveObjects), player);
				}
			}
		}
		if (Input::keyPressed[SDL_SCANCODE_I]) {
			if (player->inventory().isOpened()) {
				player->inventory().close();
			}
			else
				player->inventory().open();
		}
	}
	

	player->velocity.x = 0;
	player->velocity.y = 0;

	if (Input::keystates[SDL_SCANCODE_W]) {
		player->velocity.y += -1;
		player->setAnimation(Walk);
	}
	if (Input::keystates[SDL_SCANCODE_S]) {
		player->velocity.y += 1;
		player->setAnimation(Walk);
	}
	if (Input::keystates[SDL_SCANCODE_A]) {
		player->velocity.x += -1;
		player->setAnimation(Walk);
	}
	if (Input::keystates[SDL_SCANCODE_D]) {
		player->velocity.x += 1;
		player->setAnimation(Walk);
	}
	if (Input::keystates[SDL_SCANCODE_SPACE]) {
		player->setAnimation(Dash);
	}
	if (Input::keystates[SDL_SCANCODE_TAB]) {
		if (map->getMinimapSize() != MinimapClosed)
			map->changeMinimapSize(MinimapLarge);
	}
	else if (map->getMinimapSize() == MinimapLarge)
		map->changeMinimapSize(MinimapSmall);

	if (Input::mouseStates[SDL_BUTTON_LEFT]) {
		if (player->attackPossible()) {
			int mouseX = Input::mousePosX, mouseY = Input::mousePosY;
			player->attackPressed(mouseX + map->getStartRender().x, mouseY / HEIGHT_SCALE + map->getStartRender().y);
		}
	}
}

void Game::updateGame() {
	std::vector <InteractiveObject*>::iterator it_interactiveObj;
	std::vector <InteractiveObject*>::iterator itTemp_interactiveObj;
	std::unordered_map <SDL_Scancode, InteractiveObject*>::iterator it_objectSelected;

	SDL_RenderClear(renderer);
	gameObjects.clear();

	if (player->inventory().isOpened())
		player->inventory().update(map, player);

	player->update(playerProjectiles, map, map->fieldRect);
	gameObjects.push_back(player);

	if (map->roomChanged()) {
		map->currentRoom()->getRoomObjects(monsters, interactiveObjects);
		map->setRoomChanged(false);
		player->inventory().close();
	}

	if (!map->currentRoom()->visited && map->currentRoom()->battle) {
		map->currentRoom()->setVisited(true);
	}

	updateUnits();
	it_interactiveObj = (*interactiveObjects).begin();

	// Update interactiveObj
	while (it_interactiveObj != (*interactiveObjects).end()) {
		if (!(*it_interactiveObj)->update(player)) {
			itTemp_interactiveObj = it_interactiveObj;
			delete(*itTemp_interactiveObj);
			it_interactiveObj = (*interactiveObjects).erase(itTemp_interactiveObj);
		}
		else {
			gameObjects.push_back(*it_interactiveObj);
			it_interactiveObj++;
		}
	}

	collision.updateAllUnits(player, (*monsters), map, map->fieldRect);
	collision.projectilesWithUnits(playerProjectiles, monsterAttacks, player, (*monsters));
	collision.updateInteractiveObjects((*interactiveObjects), objectSelected, player);
	collision.projectilesWithWalls(playerProjectiles, map);
	collision.projectilesWithWalls(monsterAttacks, map);

	map->setCamera(int(player->getPositionX()), int(player->getPositionY()));
	map->upDateMinimapPos();

	updateGameProjectiles();

	map->render(gameObjects);
	player->drawStatus();

	for (it_objectSelected = objectSelected.begin(); it_objectSelected != objectSelected.end(); it_objectSelected++)
		if ((*it_objectSelected).second && (*it_objectSelected).second->interacting())
			(*it_objectSelected).second->updateInteraction(map, *interactiveObjects, player);

	if (player->inventory().isOpened())
		player->inventory().draw();

	if (!player->alive()) {
		screensManager->getEndScreen()->setShowing(true);
		screensManager->getEndScreen()->setStats(false, player->getMoney());
	}
}

void Game::updateUnits() {
	std::list<Unit*>::iterator tempItMonster;
	std::list <Unit*>::iterator it_monsters = (*monsters).begin();

	while (it_monsters != (*monsters).end()) {
		if (!(*it_monsters)->update(monsterAttacks, map)) {
			(*interactiveObjects).push_back(new Money((*it_monsters)->getPositionX(), (*it_monsters)->getPositionY())); // drop money	
			std::list<AttackType*>::iterator it_projPlayer = playerProjectiles.begin(); // Delete Unit pointers in projectiles
			while (it_projPlayer != playerProjectiles.end()) {
				if (*it_projPlayer)
					(*it_projPlayer)->delHittedUnitPointer(*it_monsters);
				it_projPlayer++;
			}

			tempItMonster = it_monsters;
			it_monsters++;
			delete(*tempItMonster);
			(*monsters).erase(tempItMonster);
			if ((*monsters).empty())
				map->currentRoom()->setBattle(false);

			if (map->currentRoom()->type == Boss && monsters->empty()) { // Boss killed
				screensManager->getEndScreen()->setShowing(true);
				screensManager->getEndScreen()->setStats(true, player->getMoney());
			}
		}
		else {
			gameObjects.push_back((*it_monsters));
			it_monsters++;
		}
	}
}

void Game::updateGameProjectiles() {
	std::list<AttackType*>::iterator it = playerProjectiles.begin();
	std::list<AttackType*>::iterator tempItProjectile;
	std::list<Unit*>::iterator itMonster;

	it = monsterAttacks.begin();
	while (it != monsterAttacks.end()) {
		if (*it) {
			if (!(*it)->update(map, map->fieldRect, player)) {
				delete (*it);
				tempItProjectile = it;
				it++;
				monsterAttacks.erase(tempItProjectile);
			}
			else {
				gameObjects.push_back((*it));
				it++;
			}
		}
	}

	it = playerProjectiles.begin();

	while (it != playerProjectiles.end()) {
		if (*it) {
			// Find closest monster
			float closest = 9999999;
			float tempDist;
			Unit* closestMonster = nullptr; // Homing projectile
			if ((*it)->getPassives()[StaticPassiveName::homing]) {
				for (itMonster = monsters->begin(); itMonster != monsters->end(); itMonster++)
					if ((tempDist = (*it)->distanceEdges(*itMonster)) < closest) {
						closestMonster = *itMonster;
						closest = tempDist;
					}
			}

			if (!(*it)->update(map, map->fieldRect, closestMonster)) {
				delete (*it);
				tempItProjectile = it;
				it++;
				playerProjectiles.erase(tempItProjectile);
			}
			else {
				gameObjects.push_back((*it));
				it++;
			}
		}
	}
}

void Game::newGame() {
	delete player;
	delete map;
	std::list <AttackType*>::iterator it;

	for (it = playerProjectiles.begin(); it != playerProjectiles.end(); it++)
		delete *it;
	playerProjectiles.clear();

	for (it = monsterAttacks.begin(); it != monsterAttacks.end(); it++)
		delete *it;
	monsterAttacks.clear();

	player = new Player(TextureManager::textures[TextureFile::PLAYER], windowResolution);
	map = new Map(player, windowResolution.y / 2, windowResolution.x / 2);

	map->generateNewLevel();
	map->currentRoom()->getRoomObjects(monsters, interactiveObjects);
	map->setFieldsPositions();
	player->setPosition(map->getCameraX(), map->getCameraY());
}

void Game::quitGame() {
	_running = false;
}

Game::Game(int w, int h, bool fullscreen) : windowResolution{ w, h } {
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow("Roguelike Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
	renderer = SDL_CreateRenderer(window, -1, 0);

	windowResolution.x = w;
	windowResolution.y = h;
	map = nullptr;

	
	FPS = 60;
	_running = true;
	gameObjects.reserve(1000);
	objectSelected.reserve(20);

	// Keys that interact with objects
	objectSelected[SDL_SCANCODE_E]; // Pick up
	objectSelected[SDL_SCANCODE_T]; // Teleport
}


Game::~Game() {
	delete map;
	delete player;
	delete screensManager;

	std::list <AttackType*>::iterator it;

	for (it = playerProjectiles.begin(); it != playerProjectiles.end(); it++)
		delete *it;
	playerProjectiles.clear();

	for (it = monsterAttacks.begin(); it != monsterAttacks.end(); it++)
		delete *it;
	monsterAttacks.clear();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}