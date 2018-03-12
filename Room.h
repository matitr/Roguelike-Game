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
#define PROJECTILES 9
#define DOORS 10
#define PLAYER_STATS 11


class SDL_Texture;
class FIELD;

class Room {
private:

public:
	int x1, y1;
	int x2, y2;
	std::list<Room*> connectedRooms;
	std::list<Room*> hallways;
	std::unordered_map<Field*, Field*> doorsConnection;
	std::unordered_map<Field*, Room*> roomConnection;

	bool battle;
	bool visited;
	bool specialRoom;

	void setVisited(bool x) { visited = x; }
	void changeValues(int _x1, int _y1, int _x2, int _y2);
	void changePosition(int _x1, int _y1);

	void addConnection(Field* fieldThisRoom, Field* fieldOtherRoom, Room* otherRoom);
	bool addConnectedRoom(Room* r);
	bool connectedRoom(Room* r);

	void addHallway(Room* otherRoom, SDL_Point&, SDL_Point&);

	Room(int _x1, int _y1, int _x2, int _y2, bool sp);
	Room(int _x1, int _y1, int _x2, int _y2, bool sp, bool battle);
	~Room();
};

