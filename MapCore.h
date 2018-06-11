#pragma once
#include <unordered_map>
#include "Room.h"

#define BORDER_SIZE 10
#define MAP_SIZE (800 + BORDER_SIZE + BORDER_SIZE)
#define MAP_WIDTH (600 + BORDER_SIZE + BORDER_SIZE)
#define MAP_HEIGHT (600 + BORDER_SIZE + BORDER_SIZE)


#define MINIMAP_HEIGHT 140
#define MINIMAP_WIDTH 180

#define HEIGHT_SCALE 1

struct SDL_Texture;
class GameObject;

struct CameraPosition {
	int xField, yField, xAdditionalPixels, yAdditionalPixels;
};

enum MinimapSize { MinimapLarge, MinimapSmall, MinimapClosed };

class MapCore{

protected:
	Room * currRoom;

	SDL_Point cameraPos;
	CameraPosition startRenderPos;
	SDL_Point fieldsToRender;
	SDL_Point resolution;

	SDL_Rect minimapSrcRect, minimapDstRect;
	MinimapSize minimapSize;
public:
	SDL_Texture* minimap;
	SDL_Texture* minimapBackground;

	std::list<Room*> roomsOnMiniman;

	SDL_Rect fieldRect;
	std::vector<std::vector<Field*>> map;
	SDL_Point startRender;

	void initValues();
	void setSpawn(Room* room, float fieldX, float fieldY);
	void setCamera(int x, int y);
	void moveCamera(int x, int y);
	int getCameraX() { return cameraPos.x; }
	int getCameraY() { return cameraPos.y; }
	void changeMinimapSize(MinimapSize show);
	void upDateMinimapPos();
	MinimapSize getMinimapSize() { return minimapSize; }
	SDL_Rect& getMinimapDstRect() { return minimapDstRect; }

	SDL_Point getResolution() { return resolution; }

	MapCore(int _hCenter, int _wCenter);
	~MapCore();
};

