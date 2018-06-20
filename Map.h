#pragma once
#include "Field.h"
#include "Room.h"
#include "MapCore.h"
#include "LevelGenerator.h"
#include <vector>
#include <unordered_map>

class Player;

#define ROOM_FIELD_MIN_RATIO 0.45
#define MAX_MAP_GEN_DEPTH 6

#define MIN_ROOM_SEPARATION 6
#define MAX_ROOM_SEPARATION 30

class Map: public MapCore {
	int hCenter, wCenter;
	bool battle = false;
	bool _roomChanged = false;

	Player* player = nullptr;
	SDL_Texture* teleportMap;

	LevelGenerator generator;
public:
	std::vector<Room*> rooms; // rooms[0] is spawn

	inline int fieldHeight() { return fieldRect.h; }
	inline int fieldWidth() { return fieldRect.w; }

	void setPlayerPointer(Player* p) { player = p; }
	Player* getPlayer() { return player; }
	SDL_Texture* getTeleportMap() { return teleportMap; }
	void setRoomChanged(bool changed) { _roomChanged = changed; }
	bool roomChanged() { return _roomChanged; }
	void setBattle(bool b) { battle = b; }
	Room* currentRoom() { return currRoom; }

	void generateNewLevel();

	void createMinimap();
	void addToMinimap(Room* room);

	void createTeleportMap();

	void render(std::vector <GameObject*>& gameObjects);

	void setFieldsPositions(); // Set fileds iterators. Coordinates (x,y)  (0...1...n, 0...1...m)
	void changeRoom(Room* room, Field* fieldToMove);
	void changeRoom(Room* room, Teleporter* tele);

	Map(Player* p, int _hCenter, int _wCenter);
	~Map();
};

