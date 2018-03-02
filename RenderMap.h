#pragma once
#include <unordered_map>
#include "Room.h"

#define BORDER_SIZE 10
#define MAP_SIZE (800 + BORDER_SIZE + BORDER_SIZE)
#define MAP_WIDTH (600 + BORDER_SIZE + BORDER_SIZE)
#define MAP_HEIGHT (300 + BORDER_SIZE + BORDER_SIZE)


class SDL_Texture;

struct CameraPosition {
	int xField, yField, xAdditionalPixels, yAdditionalPixels;
};

class RenderMap{

private:
	SDL_Rect fieldRect;
	SDL_Point cameraPos;
	CameraPosition startRenderPos;
	SDL_Point firstSpawnChunk; //cords
	SDL_Point fieldsToRender;
	SDL_Texture * texture;

	int fieldX, fieldY;
	int fieldCounterX, fieldCounterY;
	int i, j;

protected:
	std::vector<std::vector<Field*>> map;
	std::unordered_map <int, SDL_Texture*> textures;

public:
	void initValues();
	void render();
	void setCamera(int x, int y);
	void moveCamera(int x, int y);

	RenderMap(int _hCenter, int _wCenter);
	~RenderMap();
};

