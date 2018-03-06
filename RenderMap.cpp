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

	SDL_RenderPresent(Game::renderer);
}

void RenderMap::setSpawn(float x, float y) {
	if (x == int(x))
		cameraPos.x = x * fieldRect.w + fieldRect.w / 2;
	else
		cameraPos.x = x * fieldRect.w;

	if (y == int(y))
		cameraPos.y = y * fieldRect.h + fieldRect.h / 2;
	else
		cameraPos.y = y * fieldRect.h;



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

	fieldRect.h = 50;
	fieldRect.w = 50;
	fieldsToRender.x = (_wCenter * 2) / fieldRect.w + 1;
	fieldsToRender.y = (_hCenter * 2) / fieldRect.h + 1;
	resolution.x = _wCenter * 2;
	resolution.y = _hCenter * 2;
}


RenderMap::~RenderMap(){

}
