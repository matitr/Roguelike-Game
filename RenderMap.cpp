#include "RenderMap.h"
#include "Game.h"
#include "Field.h"
#include "SDL.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include "GameObject.h"
#include "Teleporter.h"


void RenderMap::initValues() {
	startRenderPos.xField = cameraPos.x / fieldRect.w - floor(fieldsToRender.x / 2);
	startRenderPos.xAdditionalPixels = cameraPos.x % fieldRect.w;

	startRenderPos.yField = cameraPos.y / fieldRect.h - floor(fieldsToRender.y / 2);
//	startRenderPos.yAdditionalPixels = cameraPos.y % fieldRect.h;
	startRenderPos.yAdditionalPixels = fieldRect.h * HEIGHT_SCALE * float(cameraPos.y % fieldRect.h) / fieldRect.h;

	// Render only room, not empty fields after room
	if (startRenderPos.xField < currRoom->x1) {
		startRenderPos.xField = currRoom->x1;
		startRenderPos.xAdditionalPixels = 0;
	}
	else if (startRenderPos.xField * fieldRect.w + startRenderPos.xAdditionalPixels > (currRoom->x2 + 1) * fieldRect.w - resolution.x) {
		startRenderPos.xField = ((currRoom->x2 * fieldRect.w) - resolution.x) / fieldRect.w + 1;
		startRenderPos.xAdditionalPixels = (currRoom->x2 * fieldRect.w - resolution.x) % fieldRect.w;
	}

	if (startRenderPos.yField + 1 < currRoom->y1) {
		startRenderPos.yField = currRoom->y1 - 1;
		startRenderPos.yAdditionalPixels = 0;
	}
	else if (startRenderPos.yField * fieldRect.h * HEIGHT_SCALE + startRenderPos.yAdditionalPixels > (currRoom->y2 + 1) * fieldRect.h  * HEIGHT_SCALE - resolution.y) {
		startRenderPos.yField = ((currRoom->y2 * fieldRect.h * HEIGHT_SCALE) - resolution.y) / (fieldRect.h * HEIGHT_SCALE) + 1;
		startRenderPos.yAdditionalPixels = int(currRoom->y2 * fieldRect.h * HEIGHT_SCALE - resolution.y) % int(fieldRect.h * HEIGHT_SCALE);
	}


	startRender.x = startRenderPos.xField * fieldRect.w + startRenderPos.xAdditionalPixels;
	startRender.y = startRenderPos.yField * fieldRect.h + startRenderPos.yAdditionalPixels / HEIGHT_SCALE;
//	startRenderPos.xField = 0;
//	startRenderPos.yField = 0;
//	startRenderPos.xAdditionalPixels = 0;
//	startRenderPos.yAdditionalPixels = 0;
}

void RenderMap::render(std::vector <GameObject*>& gameObjects) {
	if (!Game::renderer)
		return;

	int fieldRectH = fieldRect.h;
	fieldRect.h *= HEIGHT_SCALE;

	// Draw floor
	fieldY = startRenderPos.yField;
	for (fieldCounterY = 0; fieldCounterY <= fieldsToRender.y; fieldCounterY++, fieldY++) { // Y
 		fieldX = startRenderPos.xField;
		fieldRect.y = fieldCounterY * fieldRect.h - startRenderPos.yAdditionalPixels;
		for (fieldCounterX = 0; fieldCounterX <= fieldsToRender.x; fieldCounterX++, fieldX++) { // X
			fieldRect.x = fieldCounterX * fieldRect.w - startRenderPos.xAdditionalPixels;
			if (map[fieldX][fieldY] && map[fieldX][fieldY]->ground())
				map[fieldX][fieldY]->drawField(fieldRect.x, fieldRect.y);
		}
	}

	std::sort(gameObjects.begin(), gameObjects.end(),
		[](const GameObject* a, const GameObject* b)->bool 
	{return (a->flatTextureOnFloor() && !b->flatTextureOnFloor()) ||(a->flatTextureOnFloor() && b->flatTextureOnFloor() && a->getPositionY() < b->getPositionY()); });

	int numbOfGameObj = gameObjects.size(), iGameObject = 0;

	// Draw objects that are flat on floor
	while (iGameObject < numbOfGameObj && gameObjects[iGameObject]->flatTextureOnFloor()) {
		gameObjects[iGameObject]->draw(&startRender);
		iGameObject++;
	}

	// Draw rest
	fieldY = startRenderPos.yField;
	for (fieldCounterY = 0; fieldCounterY <= fieldsToRender.y; fieldCounterY++, fieldY++) { // Y
		fieldX = startRenderPos.xField;
		fieldRect.y = fieldCounterY * fieldRect.h - startRenderPos.yAdditionalPixels;

		// Draw gameObjects
		while (iGameObject < numbOfGameObj && gameObjects[iGameObject]->getPositionY() < fieldY * fieldRect.h) {
			gameObjects[iGameObject]->draw(&startRender);
			iGameObject++;
		}

		for (fieldCounterX = 0; fieldCounterX <= fieldsToRender.x; fieldCounterX++, fieldX++) { // X
			fieldRect.x = fieldCounterX * fieldRect.w - startRenderPos.xAdditionalPixels;
			if (map[fieldX][fieldY] && !map[fieldX][fieldY]->ground())
				map[fieldX][fieldY]->drawField(fieldRect.x, fieldRect.y);
		}
	}

	// Draw the remaining gameObjects
	while (iGameObject < numbOfGameObj) {
		gameObjects[iGameObject]->draw(&startRender);
		iGameObject++;
	}

	// Render minimap
	if (minimapSize != MinimapClosed) {
		SDL_RenderCopy(Game::renderer, minimapBackground, &minimapSrcRect, &minimapDstRect);
		SDL_RenderCopy(Game::renderer, minimap, &minimapSrcRect, &minimapDstRect);
		SDL_RenderDrawRect(Game::renderer, &minimapDstRect);
	}

	if (minimapSize == MinimapLarge)
		SDL_RenderDrawPoint(Game::renderer, minimapDstRect.x + cameraPos.x / fieldRect.w, minimapDstRect.y + cameraPos.y / fieldRect.h);
	else if (minimapSize == MinimapSmall)
		SDL_RenderDrawPoint(Game::renderer, minimapDstRect.x + MINIMAP_WIDTH / 2, minimapDstRect.y + MINIMAP_HEIGHT / 2);

	fieldRect.h = fieldRectH;
}

void RenderMap::setSpawn(Room* room, float x, float y) {
	if (x == int(x))
		cameraPos.x = x * fieldRect.w + fieldRect.w / 4;
	else
		cameraPos.x = x * fieldRect.w;

	if (y == int(y))
		cameraPos.y = y * fieldRect.h + fieldRect.h / 4;
	else
		cameraPos.y = y * fieldRect.h;




	currRoom = room;

	initValues();
}

void RenderMap::setCamera(int x, int y) {
	cameraPos.x = x;
	cameraPos.y = y;

	initValues();
}

void RenderMap::moveCamera(int x, int y) {
	cameraPos.x += x;
	cameraPos.y += y;

	initValues();
}

void RenderMap::changeMinimapSize(MinimapSize showM){
	minimapSize = showM;

	if (minimapSize == MinimapLarge || minimapSize == MinimapClosed) {
		minimapDstRect.x = resolution.x / 2 - MAP_WIDTH / 2;
		minimapDstRect.y = resolution.y / 2 - MAP_HEIGHT / 2;
		minimapDstRect.w = MAP_WIDTH;
		minimapDstRect.h = MAP_HEIGHT;

		minimapSrcRect.w = MAP_WIDTH;
		minimapSrcRect.h = MAP_HEIGHT;
		minimapSrcRect.x = 0;
		minimapSrcRect.y = 0;
	}
	else if (minimapSize == MinimapSmall) {
		minimapDstRect.x = resolution.x - MINIMAP_WIDTH - 20;
		minimapDstRect.y = 20;
		minimapDstRect.w = MINIMAP_WIDTH;
		minimapDstRect.h = MINIMAP_HEIGHT;

		minimapSrcRect.w = MINIMAP_WIDTH;
		minimapSrcRect.h = MINIMAP_HEIGHT;
		minimapSrcRect.x = cameraPos.x / fieldRect.w - MINIMAP_WIDTH / 2;
		minimapSrcRect.y = HEIGHT_SCALE * cameraPos.y / fieldRect.h - MINIMAP_HEIGHT / 2;
	}
}

void RenderMap::upDateMinimapPos() {

	if (minimapSize == MinimapLarge) {
		minimapDstRect.x = resolution.x / 2 - MAP_WIDTH / 2;
		minimapDstRect.y = resolution.y / 2 - MAP_HEIGHT / 2;

		minimapSrcRect.x = 0;
		minimapSrcRect.y = 0;
	}
	else if (minimapSize == MinimapSmall) {
		minimapDstRect.x = resolution.x - MINIMAP_WIDTH - 20;
		minimapDstRect.y = 20;

		minimapSrcRect.x = cameraPos.x / fieldRect.w - MINIMAP_WIDTH / 2;
		minimapSrcRect.y = HEIGHT_SCALE * cameraPos.y / fieldRect.h - MINIMAP_HEIGHT / 2;
	}
}

RenderMap::RenderMap(int _hCenter, int _wCenter){
	map.resize(MAP_WIDTH);
	for (int i = 0; i < map.size(); i++)
		map[i].resize(MAP_HEIGHT);

	minimap = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, MAP_WIDTH, MAP_HEIGHT);
	SDL_SetTextureBlendMode(minimap, SDL_BLENDMODE_BLEND);

	minimapBackground = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, MAP_WIDTH, MAP_HEIGHT);
	SDL_SetTextureBlendMode(minimapBackground, SDL_BLENDMODE_BLEND);

	fieldRect.h = 60;
	fieldRect.w = 60;
	fieldsToRender.x = (_wCenter * 2) / fieldRect.w + 1;
	fieldsToRender.y = (_hCenter * 2) / (fieldRect.h * HEIGHT_SCALE) + 1;
	resolution.x = _wCenter * 2;
	resolution.y = _hCenter * 2;

	minimapDstRect.x = resolution.x - MINIMAP_WIDTH - 20;
	minimapDstRect.y = 20;
	minimapDstRect.w = MINIMAP_WIDTH;
	minimapDstRect.h = MINIMAP_HEIGHT;

	minimapSrcRect.w = MINIMAP_WIDTH;
	minimapSrcRect.h = MINIMAP_HEIGHT;
}


RenderMap::~RenderMap(){

}
