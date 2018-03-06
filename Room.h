#pragma once
#include "Field.h"
#include <unordered_map>
#include <list>


#define WOOD_FLOOR 0
#define WATER 1
#define STONE 2
#define PLAYER 3
#define WALL_SIDE 4
#define WALL_TOP_T 5
#define WALL_TOP_R 6
#define WALL_TOP_B 7
#define WALL_TOP_L 8


class SDL_Texture;
class FIELD;

class Room {

public:
	int x1, y1;
	int x2, y2;
	std::list<Room*> connectedRooms;

	bool specialRoom;
	void changeValues(int _x1, int _y1, int _x2, int _y2);
	void changePosition(int _x1, int _y1);

	bool addConnectedRoom(Room* r);
	bool connectedRoom(Room* r);

	Room(int _x1, int _y1, int _x2, int _y2, bool);
	~Room();
};

