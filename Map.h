#pragma once
#include "Field.h"
#include "Room.h"
#include "RenderMap.h"
#include <vector>
#include <unordered_map>

#define ROOM_FIELD_MIN_RATIO 0.45
#define MAX_MAP_GEN_DEPTH 6

#define MIN_ROOM_SEPARATION 6
#define MAX_ROOM_SEPARATION 30


class Map: public RenderMap {
	int hCenter, wCenter;
	bool battle = false;
	SDL_Texture* levelTexture;
public:
	std::vector<Room*> rooms; // rooms[0] is spawn

	inline int fieldHeight() { return fieldRect.h; }
	inline int fieldWidth() { return fieldRect.w; }

	void setBattle(bool b) { battle = b; }
	Room* currentRoom() { return currRoom; }

	void generateNewMap();
	void generateSpecialRooms(int &roomNumber);
	void findPositionForRooms(int roomsNumber);
	void createRoom(Room* room);
	void generateHallways(int &roomsNumber);
	void createHallwayH(SDL_Point&, SDL_Point&); // Horizontal, (p1.y >= p2.y)
	void createHallwayV(SDL_Point&, SDL_Point&); // Vertical, (p1.y >= p2.y)
	void createRoomWalls(Room* room);

	void createMinimap();
	void addToMinimap(Room* room);

	void setFieldsPositions();
	void changeRoom(Room* room, Field* fieldToMove);

	Map(int _hCenter, int _wCenter);
	~Map();
};

