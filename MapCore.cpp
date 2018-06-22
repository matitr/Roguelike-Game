#include "MapCore.h"
#include "Game.h"
#include "Field.h"
#include "SDL.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include "GameObject.h"
#include "Teleporter.h"


void MapCore::initValues() {
	startRenderPos.xField = int(cameraPos.x / fieldRect.w - floor(fieldsToRender.x / 2));
	startRenderPos.xAdditionalPixels = cameraPos.x % fieldRect.w;

	startRenderPos.yField = cameraPos.y / fieldRect.h - (int)floor(fieldsToRender.y / 2);
	startRenderPos.yAdditionalPixels = int(fieldRect.h * HEIGHT_SCALE * float(cameraPos.y % fieldRect.h) / fieldRect.h);

	// Render only room, not empty fields after room
	if (startRenderPos.xField < currRoom->x1) { // X
		startRenderPos.xField = currRoom->x1;
		startRenderPos.xAdditionalPixels = 0;
	}
	else if (startRenderPos.xField * fieldRect.w + startRenderPos.xAdditionalPixels > (currRoom->x2 + 1) * fieldRect.w - resolution.x) {
		startRenderPos.xField = ((currRoom->x2 * fieldRect.w) - resolution.x) / fieldRect.w + 1;
		startRenderPos.xAdditionalPixels = (currRoom->x2 * fieldRect.w - resolution.x) % fieldRect.w;
	}

	if (startRenderPos.yField + 2 < currRoom->y1) { // Y
		startRenderPos.yField = currRoom->y1 - 2;
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

void MapCore::setSpawn(Room* room, float x, float y) {
	if (x == int(x))
		cameraPos.x = int(x * fieldRect.w + fieldRect.w / 4);
	else
		cameraPos.x = int(x * fieldRect.w);

	if (y == int(y))
		cameraPos.y = int(y * fieldRect.h + fieldRect.h / 4);
	else
		cameraPos.y = int(y * fieldRect.h);

	currRoom = room;

	initValues();
}

void MapCore::setCamera(int x, int y) {
	cameraPos.x = x;
	cameraPos.y = y;

	initValues();
}

void MapCore::moveCamera(int x, int y) {
	cameraPos.x += x;
	cameraPos.y += y;

	initValues();
}

void MapCore::changeMinimapSize(MinimapSize showM){
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

void MapCore::upDateMinimapPos() {

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

MapCore::MapCore(int _hCenter, int _wCenter){
	map.resize(MAP_WIDTH * MAP_HEIGHT);

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


MapCore::~MapCore() {
	SDL_DestroyTexture(minimap);
	SDL_DestroyTexture(minimapBackground);
}
