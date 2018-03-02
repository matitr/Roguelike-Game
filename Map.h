#pragma once
#include "Field.h"
#include "Room.h"
#include "RenderMap.h"
#include <vector>
#include <unordered_map>

#define ROOM_FIELD_MIN_RATIO 0.45
#define MAX_MAP_GEN_DEPTH 6

#define MAP_SEPARATION_SIZE 6

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
	void generateNewMap(int);
	void generateMapField(int _x, int _y, int _width, int _height, bool divideWidth, int);
	void createRoom(Room* room);
	void createFieldWalls(Room* room);
	void createRoomConectionsX(Room* room, int xSeparation);
	void createRoomConectionsY(Room* room, int ySeparation);

	Map(int _hCenter, int _wCenter);
	~Map();
};

