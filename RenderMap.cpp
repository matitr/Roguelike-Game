#include "RenderMap.h"
#include "Game.h"
#include "Field.h"
#include "SDL.h"
#include <math.h>
#include <iostream>


void RenderMap::initValues() {
}

void RenderMap::render() {
	if (!Game::renderer)
		return;

//	fieldY = startRenderPos.yField;
	fieldY = 0;

	for (fieldCounterY = 0; fieldCounterY <= fieldsToRender.y; fieldCounterY++, fieldY++) { // Y
//		fieldX = startRenderPos.xField;
		fieldX = 0;
		fieldRect.y = fieldCounterY * fieldRect.h;
		for (fieldCounterX = 0; fieldCounterX <= fieldsToRender.x; fieldCounterX++, fieldX++) { // X
			fieldRect.x = fieldCounterX * fieldRect.w;
			if (map[fieldX][fieldY])
				SDL_RenderCopy(Game::renderer, map[fieldX][fieldY]->getBackground(), NULL, &fieldRect);


		}
	}

	SDL_RenderPresent(Game::renderer);
}

void RenderMap::setCamera(int x, int y) {
	cameraPos.x = x;
	cameraPos.y = y;
}

void RenderMap::moveCamera(int x, int y) {
	/*
	cameraPos.xAdditionalPixels += x;

	if (cameraPos.xAdditionalPixels < 0) {
		cameraPos.xField += (cameraPos.xAdditionalPixels / fieldRect.w) - 1;
		cameraPos.xAdditionalPixels = fieldRect.w + (cameraPos.xAdditionalPixels - (cameraPos.xAdditionalPixels / fieldRect.w) * fieldRect.w);
	}
	else if (cameraPos.xAdditionalPixels >= fieldRect.w) {
		cameraPos.xField += cameraPos.xAdditionalPixels / fieldRect.w + 1;
		cameraPos.xAdditionalPixels = cameraPos.xAdditionalPixels - (cameraPos.xAdditionalPixels / fieldRect.w) * fieldRect.w;
	}

	
	cameraPos.yAdditionalPixels += y;

	if (cameraPos.yAdditionalPixels < 0) {
		cameraPos.yField += (cameraPos.yAdditionalPixels / fieldRect.h) - 1;
		cameraPos.yAdditionalPixels = fieldRect.h + (cameraPos.yAdditionalPixels - (cameraPos.yAdditionalPixels / fieldRect.h) * fieldRect.h);
	}
	else if (cameraPos.yAdditionalPixels >= fieldRect.w) {
		cameraPos.yField += cameraPos.yAdditionalPixels / fieldRect.h + 1;
		cameraPos.yAdditionalPixels = cameraPos.yAdditionalPixels - (cameraPos.yAdditionalPixels / fieldRect.h) * fieldRect.h;
	}
	*/
	cameraPos.x += x;
	cameraPos.y += y;

	initValues();
}

RenderMap::RenderMap(int _hCenter, int _wCenter){
	map.resize(MAP_WIDTH);
	for (int i = 0; i < map.size(); i++)
		map[i].resize(MAP_HEIGHT);

	fieldRect.h = 80;
	fieldRect.w = 80;
	fieldsToRender.x = (_wCenter * 2) / fieldRect.w + 1;
	fieldsToRender.y = (_hCenter * 2) / fieldRect.h + 1;
/*
	cameraPos.xField = MAP_SIZE / 2;
	cameraPos.yField = MAP_SIZE / 2;//-1 2 3
	cameraPos.xAdditionalPixels = 0;
	cameraPos.yAdditionalPixels = 0;

	startRenderPos.xField = cameraPos.xField - fieldsToRender.x / 2;
	startRenderPos.yField = cameraPos.yField - fieldsToRender.y / 2;
	*/

}


RenderMap::~RenderMap(){

}
