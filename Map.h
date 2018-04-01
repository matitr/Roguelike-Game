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
public:
	inline int fieldHeight() { return fieldRect.h; }
	inline int fieldWidth() { return fieldRect.w; }

	bool openMap(); // todo
	bool saveMap(); // todo

	void setBattle(bool b) { battle = b; }
	Room* currentRoom() { return currRoom; }

	std::vector<Room*> rooms; // rooms[0] is spawn

	void generateNewMap();
	void generateSpecialRooms(int &roomNumber);
	void createRoom(Room* room);
	void generateHallways(int &roomsNumber);
	void generateHallwaysAngle(int &roomsNumber);
	void createHallwayH(SDL_Point&, SDL_Point&); // Horizontal, (p1.y >= p2.y)
	void createHallwayV(SDL_Point&, SDL_Point&); // Vertical, (p1.y >= p2.y)
	void createHallwayAngleH(SDL_Point& p1, SDL_Point& p2); // First line is Horizontal
	void createHallwayAngleV(SDL_Point& p1, SDL_Point& p2); // First line is Vertical
	void createRoomWalls(Room* room);
	void createFieldWalls(Room* room);

	void createMinimap();
	void addToMinimap(Room* room);

	void setFieldsPositions();
	void changeRoom(Room* room, Field* fieldToMove);

	Map(int _hCenter, int _wCenter);
	~Map();
};

