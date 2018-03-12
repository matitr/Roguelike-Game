#include "Room.h"
#include "SDL.h"


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
	Room* hallway = new Room(p1.x, p1.y, p2.x, p2.y, 1);

	hallways.push_back(hallway);
	otherRoom->hallways.push_back(hallway);

	hallway->connectedRooms.push_back(this);
	hallway->connectedRooms.push_back(otherRoom);
}

Room::Room(int _x1, int _y1, int _x2, int _y2, bool specialR) {
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;

	specialRoom = specialR;
	battle = false;
	visited = false;
}

Room::Room(int _x1, int _y1, int _x2, int _y2, bool specialR, bool _battle){
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;

	specialRoom = specialR;
	battle = _battle;
	visited = false;
}


Room::~Room(){

}
