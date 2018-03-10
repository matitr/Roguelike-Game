#pragma once
#include <unordered_map>
#include "Room.h"

#define BORDER_SIZE 10
#define MAP_SIZE (800 + BORDER_SIZE + BORDER_SIZE)
#define MAP_WIDTH (600 + BORDER_SIZE + BORDER_SIZE)
#define MAP_HEIGHT (600 + BORDER_SIZE + BORDER_SIZE)


class SDL_Texture;

struct CameraPosition {
	int xField, yField, xAdditionalPixels, yAdditionalPixels;
};

class RenderMap{
protected:
	Room * currRoom;

private:
	SDL_Point cameraPos;
	CameraPosition startRenderPos;
	SDL_Point firstSpawnChunk; //cords
	SDL_Point fieldsToRender;
	SDL_Texture * texture;
	SDL_Point resolution;
	int fieldX, fieldY;
	int fieldCounterX, fieldCounterY;
	int i, j;


public:
	SDL_Rect fieldRect;
	std::vector<std::vector<Field*>> map;
	SDL_Point startRender;
	std::unordered_map <int, SDL_Texture*> textures;
	void initValues();
	void render();
	void setSpawn(Room* room, float fieldX, float fieldY);
	void setCamera(int x, int y);
	void moveCamera(int x, int y);
	int getCameraX() { return cameraPos.x; }
	int getCameraY() { return cameraPos.y; }

	RenderMap(int _hCenter, int _wCenter);
	~RenderMap();
};

