#include "RenderMap.h"
#include "Game.h"
#include "Field.h"
#include "SDL.h"
#include <math.h>
#include <iostream>


void RenderMap::initValues() {
	startRenderPos.xField = cameraPos.x / fieldRect.w - floor(fieldsToRender.x / 2);
	startRenderPos.xAdditionalPixels = cameraPos.x % fieldRect.w;

	startRenderPos.yField = cameraPos.y / fieldRect.h - floor(fieldsToRender.y / 2);
	startRenderPos.yAdditionalPixels = cameraPos.y % fieldRect.h;

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
	else if (startRenderPos.yField * fieldRect.h + startRenderPos.yAdditionalPixels > (currRoom->y2 + 1) * fieldRect.h - resolution.y) {
		startRenderPos.yField = ((currRoom->y2 * fieldRect.h) - resolution.y) / fieldRect.h + 1;
		startRenderPos.yAdditionalPixels = (currRoom->y2 * fieldRect.h - resolution.y) % fieldRect.h;
	}


	startRender.x = startRenderPos.xField * fieldRect.w + startRenderPos.xAdditionalPixels;
	startRender.y = startRenderPos.yField * fieldRect.h + startRenderPos.yAdditionalPixels;
//	startRenderPos.xField = 0;
//	startRenderPos.yField = 0;
//	startRenderPos.xAdditionalPixels = 0;
//	startRenderPos.yAdditionalPixels = 0;
}

void RenderMap::render() {
	if (!Game::renderer)
		return;

	fieldY = startRenderPos.yField;

	for (fieldCounterY = 0; fieldCounterY <= fieldsToRender.y; fieldCounterY++, fieldY++) { // Y
 		fieldX = startRenderPos.xField;
		fieldRect.y = fieldCounterY * fieldRect.h - startRenderPos.yAdditionalPixels;
		for (fieldCounterX = 0; fieldCounterX <= fieldsToRender.x; fieldCounterX++, fieldX++) { // X
			fieldRect.x = fieldCounterX * fieldRect.w - startRenderPos.xAdditionalPixels;
			if (map[fieldX][fieldY])
				SDL_RenderCopy(Game::renderer, map[fieldX][fieldY]->getTexture(), NULL, &fieldRect);


		}
	}
	minimapSrcRect.x = cameraPos.x / fieldRect.w - MINIMAP_WIDTH / 2;
	minimapSrcRect.y = cameraPos.y / fieldRect.h - MINIMAP_HEIGHT / 2;
	SDL_RenderCopy(Game::renderer, minimap, &minimapSrcRect, &minimapDstRect);
	SDL_RenderDrawRect(Game::renderer, &minimapDstRect);
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

RenderMap::RenderMap(int _hCenter, int _wCenter){
	map.resize(MAP_WIDTH);
	for (int i = 0; i < map.size(); i++)
		map[i].resize(MAP_HEIGHT);

	minimap = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, MAP_WIDTH, MAP_HEIGHT);
	SDL_SetTextureBlendMode(minimap, SDL_BLENDMODE_BLEND);

	fieldRect.h = 60;
	fieldRect.w = 60;
	fieldsToRender.x = (_wCenter * 2) / fieldRect.w + 1;
	fieldsToRender.y = (_hCenter * 2) / fieldRect.h + 1;
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
