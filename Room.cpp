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

void Room::spawnMonsters(Map* _map, Unit* _player) {
	if (type == Monsters) {
		for (int i = 0; i < 4; i++) {
			Unit *m;
			if (!i)
				m = new UnitEnemy2(_map, _player);
			else
				m = new UnitEnemy1(_map, _player);
			monsters.push_back(m);
			int enemyX, enemyY;

			do {
				enemyX = x1 + rand() % ((x2 - x1));
				enemyY = y1 + rand() % ((y2 - y1));
			} while (!_map->getField(enemyX, enemyY) || _map->getField(enemyX, enemyY)->type() != Floor);
			m->setPosition(enemyX * _map->fieldRect.w, enemyY * _map->fieldRect.h);
		}
	}
	else if (type == Boss) {
		Unit *m = new Boss1(_map, _player);
		monsters.push_back(m);
		m->setPosition((x1 + (x2 - x1) / 2) * _map->fieldRect.w, (y1 + (y2 - y1) / 2) * _map->fieldRect.h);

	}
}

void Room::getRoomObjects(std::list <Unit*>*& _monsters, std::vector <InteractiveObject*>*& _interactiveObjects) {
	_monsters = &monsters;
	_interactiveObjects = &interactiveObjects;
}

Room::Room(int _x1, int _y1, int _x2, int _y2, RoomType _type) : type(_type) {
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;

	visited = false;

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
	std::list <Unit*>::iterator it_unit = monsters.begin();

	for (it_unit; it_unit != monsters.end(); it_unit++)
		delete (*it_unit);

	std::vector <InteractiveObject*>::iterator it_obj = interactiveObjects.begin();

	for (it_obj; it_obj != interactiveObjects.end(); it_obj++)
		delete (*it_obj);

	for (std::list<Room*>::iterator it_hall = hallways.begin(); it_hall != hallways.end(); it_hall++) {
		std::list<Room*>::iterator it_conRoom = (*it_hall)->connectedRooms.begin();
		for (it_conRoom; it_conRoom != (*it_hall)->connectedRooms.end(); it_conRoom++) {
			if (*it_conRoom != this) {
				(*it_conRoom)->hallways.remove(*it_hall);
			}
		}

		delete (*it_hall);
	}
}
