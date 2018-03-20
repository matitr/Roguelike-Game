#include "Room.h"
#include "SDL.h"
#include "Monsters.h"
#include "Map.h"


void Room::changeValues(int _x1, int _y1, int _x2, int _y2) {
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;
}

void Room::changePosition(int _x1, int _y1) {
	x2 = _x1 + (x2 - x1);
	y2 = _y1 + (y2 - y1);

	x1 = _x1;
	y1 = _y1;
}

bool Room::addConnectedRoom(Room* r) {
	if ((std::find(connectedRooms.begin(), connectedRooms.end(), r) != connectedRooms.end()))
		return false;

	connectedRooms.push_back(r);
	r->connectedRooms.push_back(this);
	return true;
}

void Room::addConnection(Field* fieldThisRoom, Field* fieldOtherRoom, Room* otherRoom) {
	doorsConnection[fieldThisRoom] = fieldOtherRoom;
	roomConnection[fieldThisRoom] = otherRoom;

	otherRoom->doorsConnection[fieldOtherRoom] = fieldThisRoom;
	otherRoom->roomConnection[fieldOtherRoom] = this;
}

bool Room::connectedRoom(Room* r) {
	if ((std::find(connectedRooms.begin(), connectedRooms.end(), r) != connectedRooms.end()))
		return true;

	return false;
}

void Room::addHallway(Room* otherRoom, SDL_Point& p1, SDL_Point& p2) {
	Room* hallway = new Room(p1.x, p1.y, p2.x, p2.y, Hallway);

	hallways.push_back(hallway);
	otherRoom->hallways.push_back(hallway);

	hallway->connectedRooms.push_back(this);
	hallway->connectedRooms.push_back(otherRoom);
}

void Room::spawnMonsters(std::list <Unit*>& monsters, Map* _map, Unit* _player) {
	Unit *m = new MonRandMoveProjAround(_map, _player);
	monsters.push_back(m);
	m->setPosition((x1 + (x2 - x1) / 2) * 60, (y1 + (y2 - y1) / 2) * 60);
}

Room::Room(int _x1, int _y1, int _x2, int _y2, RoomType _type) {
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;

	visited = false;
	type = _type;

	if (type == Monsters) {
		specialRoom = false;
		battle = true;
	}
	else if (type == Boss) {
		specialRoom = true;
		battle = true;
	}
	else if (type == Treasure) {
		specialRoom = false;
		battle = false;
	}
	else if (type == Spawn) {
		specialRoom = false;
		battle = false;
	}
	else {
		specialRoom = true;
		battle = false;
	}
}


Room::~Room(){

}
