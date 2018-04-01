#pragma once
#include "Field.h"
#include <unordered_map>
#include <list>


class SDL_Texture;
class Field;
class Unit;
class Map;

enum RoomType {Monsters, Boss, Treasure, Secret, Hallway, Spawn};

class Room {
private:

public:
	int x1, y1;
	int x2, y2;
	std::list<Room*> connectedRooms;
	std::list<Room*> hallways;
	std::unordered_map<Field*, Field*> doorsConnection;
	std::unordered_map<Field*, Room*> roomConnection;

	RoomType type;
	bool battle;
	bool visited;
	bool specialRoom;

	void setVisited(bool x) { visited = x; }
	void setBattle(bool x) { battle = x; }
	void changeValues(int _x1, int _y1, int _x2, int _y2);
	void changePosition(int _x1, int _y1);

	void addConnection(Field* fieldThisRoom, Field* fieldOtherRoom, Room* otherRoom);
	bool addConnectedRoom(Room* r);
	bool connectedRoom(Room* r);

	void addHallway(Room* otherRoom, SDL_Point&, SDL_Point&);

	void spawnMonsters(std::list <Unit*>& monsters, Map* _map, Unit* _player);

	Room(int _x1, int _y1, int _x2, int _y2, RoomType);
	~Room();
};

