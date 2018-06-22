#pragma once
#include <unordered_map>
#include "Room.h"

#define BORDER_SIZE 10
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

	SDL_Texture* minimapBackground;
	std::list<Room*> roomsOnMiniman;
	SDL_Point startRender;

	std::vector<Field*> map;
public:
	SDL_Texture* minimap;

	SDL_Rect fieldRect;

	inline Field*& getField(int x, int y) { return map[y * MAP_WIDTH + x]; }

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
	SDL_Point getStartRender() { return startRender; }

	MapCore(int _hCenter, int _wCenter);
	~MapCore();
};

