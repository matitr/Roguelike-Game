#pragma once
#include "SDL.h"
#include "Field.h"
#include "myMath.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <list>


struct SDL_Texture;
class Field;
class Unit;
class Map;
class Teleporter;
class InteractiveObject;

enum RoomType {Monsters, Boss, Treasure, Secret, Hallway, Spawn};

class Room {
private:

public:
	std::list <Unit*> monsters;
	std::vector <InteractiveObject*> interactiveObjects;

	int x1, y1;
	int x2, y2;
	std::list<Room*> connectedRooms;
	std::list<Room*> hallways;

	std::map<PointInt, PointInt, PointInt_cmp> doorsConnection;
	std::map<PointInt, Room*, PointInt_cmp> roomConnection;


	Teleporter* telporter;

	RoomType type;
	bool battle;
	bool visited;
	bool specialRoom;

	void setVisited(bool x) { visited = x; }
	void setBattle(bool x) { battle = x; }
	void changeValues(int _x1, int _y1, int _x2, int _y2);
	void changePosition(int _x1, int _y1);
	double roomCenterX(int fieldW) { return (x1 + (x2 - x1) / 2.0) * fieldW + fieldW / 2.0; }
	double roomCenterY(int fieldY) { return (y1 + (y2 - y1) / 2.0) * fieldY + fieldY / 2.0; }

	void addConnection(const PointInt& fieldThisRoom, const PointInt& fieldOtherRoom, Room* otherRoom);
	bool addConnectedRoom(Room* r);
	bool connectedRoom(Room* r);

	void addHallway(Room* otherRoom, PointInt&, PointInt&);

	void spawnMonsters(Map* _map, Unit* _player);
	void getRoomObjects(std::list <Unit*>*& monsters, std::vector <InteractiveObject*>*& interactiveObjects);

	Room(int _x1, int _y1, int _x2, int _y2, RoomType);
	~Room();
};

