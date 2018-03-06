#pragma once
#include "Field.h"
#include "Room.h"
#include "RenderMap.h"
#include <vector>
#include <unordered_map>
#include "Player.h"

#define ROOM_FIELD_MIN_RATIO 0.45
#define MAX_MAP_GEN_DEPTH 6

#define ROOM_SEPARATION 6
#define MAX_ROOM_SEPARATION 20

struct MapDivideField {
	int x, y, w, h;
};

class Map: public RenderMap {
	int hCenter, wCenter;
	int min, max;
public:

	bool openMap(); // todo
	bool saveMap(); // todo

	std::vector<Room*> rooms;
	void generateNewMap();
	void generateSpecialRooms(int &roomNumber);
	void createRoom(Room* room);
	void generateHallways(int &roomsNumber);
	void createHallwayH(SDL_Point&, SDL_Point&); // Horizontal
	void createHallwayV(SDL_Point&, SDL_Point&); // Vertical
	void createHallwayAngle(SDL_Point&, SDL_Point&);
	void createRoomWalls(Room* room);
	void createFieldWalls(Room* room);

	Map(int _hCenter, int _wCenter);
	~Map();
};

