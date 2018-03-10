#include "Map.h"
#include "TextureManager.h"
#include <time.h>


void Map::generateNewMap() {
	int roomsNumber = 1 + 1 + 2 + 2 + rand() % 5 + 10;
	rooms.resize(roomsNumber);
	generateSpecialRooms(roomsNumber);

	int x, y;
	int i, j;
	bool goodPosition = false;
	int closeRooms = 0;
	int specialRooms;

	for (i = 1; i < roomsNumber; i++) {
		if (!rooms[i]) {
			x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
			y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
			rooms[i] = new Room(x, y, x + rand() % 20 + 40, y + rand() % 20 + 40, 0, true); // mobs room
		}
	}

	for (i = 1; i < roomsNumber; i++) {
		goodPosition = false;

		while ((!goodPosition || (closeRooms - specialRooms) <= 0)) {
			specialRooms = 0;
			goodPosition = true;
			closeRooms = 0;
			x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 70) + BORDER_SIZE;
			y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 70) + BORDER_SIZE;
			rooms[i]->changePosition(x, y);
			for (j = 0; j < i; j++) {
				if (rooms[i]->x2 + ROOM_SEPARATION >= rooms[j]->x1 && rooms[j]->x2 + ROOM_SEPARATION >= rooms[i]->x1 &&
					rooms[i]->y2 + ROOM_SEPARATION >= rooms[j]->y1 && rooms[j]->y2 + ROOM_SEPARATION >= rooms[i]->y1)
					goodPosition = false;
				if (rooms[i]->x2 + MAX_ROOM_SEPARATION >= rooms[j]->x1 && rooms[j]->x2 + MAX_ROOM_SEPARATION >= rooms[i]->x1 
					&& rooms[i]->y2 + MAX_ROOM_SEPARATION >= rooms[j]->y1 && rooms[j]->y2 + MAX_ROOM_SEPARATION >= rooms[i]->y1)
					closeRooms++;
				if (rooms[j]->specialRoom)
					specialRooms++;
			}
		}
	}

	for (i = 0; i < roomsNumber; i++)
		createRoom(rooms[i]);
	//		createFieldWalls(rooms[i]);

	generateHallways(roomsNumber);

	for (i = 0; i < roomsNumber; i++)
		createRoomWalls(rooms[i]);
//	render();
	setSpawn(rooms[0], (rooms[0]->x2 - rooms[0]->x1) / 2 + rooms[0]->x1, (rooms[0]->y2 - rooms[0]->y1) / 2 + rooms[0]->y1);
}

void Map::generateSpecialRooms(int &roomsNumber) {
	int x, y;
	rooms[0] = new Room(MAP_WIDTH / 2 - 15, MAP_HEIGHT / 2 - 15, MAP_WIDTH / 2 - 15 + 30, MAP_HEIGHT / 2 - 15 + 30, 0); // start room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[rand() % (roomsNumber - 5) + 1] = new Room(x, y, x + 50, y + 50, 1, true); // boss room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 1] = new Room(x, y, x + 13, y + 13, 1); // secret room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 2] = new Room(x, y, x + 13, y + 13, 1); // secret room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 3] = new Room(x, y, x + 7, y + 7, 0); // treasure room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 4] = new Room(x, y, x + 7, y + 7, 0); // treasure room
}

void Map::createRoom(Room* room) {
	int xIter, yIter;
	for (xIter = room->x1 + 1; xIter < room->x2; xIter++)
		for (yIter = room->y1 + 1; yIter < room->y2; yIter++) {
			map[xIter][yIter] = new Field(textures[WOOD_FLOOR], Floor);
		}

}

void Map::generateHallways(int &roomsNumber) {
	int i, j, xji, xij, yji, yij;
	SDL_Point p1, p2;

	for (i = 0; i < roomsNumber; i++) {
		for (j = 0; j < roomsNumber; j++) { // 
			if (i != j) {
				if (rooms[i]->x2 + MAX_ROOM_SEPARATION >= rooms[j]->x1 && rooms[j]->x2 + MAX_ROOM_SEPARATION >= rooms[i]->x1
					&& rooms[i]->y2 + MAX_ROOM_SEPARATION >= rooms[j]->y1 && rooms[j]->y2 + MAX_ROOM_SEPARATION >= rooms[i]->y1 &&
					!rooms[i]->connectedRoom(rooms[j])) {
					// room is connectable and not connected yet

					xji = rooms[i]->x1 - rooms[j]->x2;
					xij = rooms[j]->x1 - rooms[i]->x2;
					yji = rooms[i]->y1 - rooms[j]->y2;
					yij = rooms[j]->y1 - rooms[i]->y2;

					int ko = 0;
					if (xij > 0) {
						if (yji > 0 || yij > 0 || xij < 5) { // Hallway with angle  _|

						// todo
						}
						else { // Hallway is straight line
							p1.x = rooms[i]->x2;
							p2.x = rooms[j]->x1;

							if (rooms[i]->y1 < rooms[j]->y1) // if i before j
								p1.y = rooms[j]->y1;
							else // yij < yji
								p1.y = rooms[i]->y1;

							if (rooms[i]->y2 < rooms[j]->y2)
								p1.y = rooms[i]->y2 - (rooms[i]->y2 - p1.y) / 2;
							else
								p1.y = rooms[j]->y2 - (rooms[j]->y2 - p1.y) / 2;

							p2.y = p1.y + 1;
							createHallwayH(p1, p2);	
							rooms[i]->addConnection(map[p1.x][p1.y], map[p2.x][p1.y], rooms[j]);
							rooms[i]->addConnection(map[p1.x][p1.y + 1], map[p2.x][p1.y + 1], rooms[j]);
						}
						rooms[i]->addConnectedRoom(rooms[j]);
					}
					else if (yij > 0) {
						if (xij > 0 || xji > 0 || yij < 5) { // Hallway with angle  _|

							// todo
						}
						else { // Hallway is straight line
							p1.y = rooms[i]->y2;
							p2.y = rooms[j]->y1;

							if (rooms[i]->x1 < rooms[j]->x1) // if i before j
								p1.x = rooms[j]->x1;
							else // xij < xji
								p1.x = rooms[i]->x1;

							if (rooms[i]->x2 < rooms[j]->x2)
								p1.x = rooms[i]->x2 - (rooms[i]->x2 - p1.x) / 2;
							else
								p1.x = rooms[j]->x2 - (rooms[j]->x2 - p1.x) / 2;
							
							p2.x = p1.x + 1;
							createHallwayV(p1, p2);	
							rooms[i]->addConnection(map[p1.x][p1.y], map[p1.x][p2.y], rooms[j]);
							rooms[i]->addConnection(map[p1.x + 1][p1.y], map[p1.x + 1][p2.y], rooms[j]);
						}
						rooms[i]->addConnectedRoom(rooms[j]);
					}
				}
			}
		}
	}
}

void Map::createHallwayH(SDL_Point& p1, SDL_Point& p2) { // Horizontal
	int x;
	Field *field;

	for (x = p1.x + 1; x < p2.x; x++) {
		map[x][p1.y] = new Field(textures[WOOD_FLOOR], Floor);
		map[x][p2.y] = new Field(textures[WOOD_FLOOR], Floor);

		map[x][p1.y - 3] = new Field(textures[WALL_TOP_T], Wall);
		map[x][p1.y - 2] = new Field(textures[WALL_SIDE], Wall);
		map[x][p1.y - 1] = new Field(textures[WALL_SIDE], Wall);
		map[x][p2.y + 1] = new Field(textures[WALL_TOP_B], Wall);
	}

	x = p1.x;
	for (int i = 0; i < 2; i++) {
		map[x][p1.y] = new Field(textures[DOORS], Door);
		map[x][p2.y] = new Field(textures[DOORS], Door);

		map[x][p1.y - 3] = new Field(textures[WALL_TOP_T], Wall);
		map[x][p1.y - 2] = new Field(textures[WALL_SIDE], Wall);
		map[x][p1.y - 1] = new Field(textures[WALL_SIDE], Wall);
		map[x][p2.y + 1] = new Field(textures[WALL_TOP_B], Wall);
		x = p2.x;
	}
}

void Map::createHallwayV(SDL_Point& p1, SDL_Point& p2) { // Vertical
	int y;
	Field *field;

	for (y = p1.y + 1; y <= p2.y; y++) {
		map[p1.x][y] = new Field(textures[WOOD_FLOOR], Floor);
		map[p2.x][y] = new Field(textures[WOOD_FLOOR], Floor);

		map[p1.x - 1][y] = new Field(textures[WALL_TOP_L], Wall);
		map[p2.x + 1][y] = new Field(textures[WALL_TOP_R], Wall);
	}

	y = p1.y;
	for (int i = 0; i < 2; i++) {
		map[p1.x][y] = new Field(textures[DOORS], Door);
		map[p2.x][y] = new Field(textures[DOORS], Door);

		map[p1.x - 1][y] = new Field(textures[WALL_TOP_L], Wall);
		map[p2.x + 1][y] = new Field(textures[WALL_TOP_R], Wall);
		y = p2.y;
	}
}

void Map::createHallwayAngle(SDL_Point& p1, SDL_Point& p2) { // todo
	
}

void Map::createRoomWalls(Room* room) {
	for (int i = room->x1 + 1; i <= room->x2 - 1; i++) { // x walls
		if (!map[i][room->y1]) { // TOP
			map[i][room->y1] = new Field(textures[WALL_SIDE], Wall);
			map[i][room->y1 - 1] = new Field(textures[WALL_SIDE], Wall);
			map[i][room->y1 - 2] = new Field(textures[WALL_TOP_T], Wall);
		}

		if (!map[i][room->y2]) { // BOTTOM
			map[i][room->y2] = new Field(textures[WALL_TOP_B], Wall);
		}
	}

	for (int i = room->y1 - 1; i <= room->y2 - 1; i++) { // y walls
		if (!map[room->x1][i]) { // LEFT
			map[room->x1][i] = new Field(textures[WALL_TOP_L], Wall);
		}

		if (!map[room->x2][i]) { // RIGHT
			map[room->x2][i] = new Field(textures[WALL_TOP_R], Wall);
		}
	}
}

void Map::createFieldWalls(Room* room) {
	for (int i = room->x1; i <= room->x2; i++) { // x walls
		if (!map[i][room->y1])
			map[i][room->y1] = new Field(textures[STONE]);

		if (!map[i][room->y2])
			map[i][room->y2] = new Field(textures[STONE]);
	}

	for (int i = room->y1; i <= room->y2; i++) { // y walls
		if (!map[room->x1][i])
			map[room->x1][i] = new Field(textures[STONE]);

		if (!map[room->x2][i])
			map[room->x2][i] = new Field(textures[STONE]);
	}
}

void Map::setFieldsPositions() {
	int x, y;
	for (x = 0; x < map.size(); x++)
		for (y = 0; y < map[x].size(); y++)
			if (map[x][y])
				map[x][y]->setPosition(x, y);
}

void Map::changeRoom(Room* room, Field* fieldToMove) {
	int x = fieldToMove->x(), y = fieldToMove->y();
	int newX, newY;
	
	if (map[x + 1][y]->type() == Door) { // Doors are horizontally
		newX = x * fieldRect.w + fieldRect.w / 2;
		if (y + 1 <= room->y2) // Top
			newY = (y + 1) * fieldRect.h;
		else
			newY = (y - 1) * fieldRect.h;
	}
	else if (map[x - 1][y]->type() == Door) { // Doors are horizontally
		newX = x * fieldRect.w - fieldRect.w / 2;
		if (y + 1 <= room->y2) // Top
			newY = (y + 1) * fieldRect.h;
		else
			newY = (y - 1) * fieldRect.h;
	}
	else if (map[x][y + 1]->type() == Door) { // Doors are vertically
		newY = y * fieldRect.w + fieldRect.w / 2;
		if (x + 1 <= room->x2) // Left
			newX = (x + 1) * fieldRect.w;
		else
			newX = (x - 1) * fieldRect.w;

	}
	else if (map[x][y - 1]->type() == Door) { // Doors are vertically
		newY = y * fieldRect.w - fieldRect.w / 2;
		if (x + 1 <= room->x2)
			newX = (x + 1) * fieldRect.w;
		else
			newX = (x - 1) * fieldRect.w;
	}

	currRoom = room;
	setCamera(newX, newY);
}

Map::Map(int _hCenter, int _wCenter) : RenderMap(_hCenter, _wCenter) {
	hCenter = _hCenter;
	wCenter = _wCenter;

	textures[PLAYER] = TextureManager::LoadTexture("Textures/player.png");
	textures[WOOD_FLOOR] = TextureManager::LoadTexture("Textures/woodFloor.png");
	textures[WATER] = TextureManager::LoadTexture("Textures/water.png");
	textures[STONE] = TextureManager::LoadTexture("Textures/stone.png");
	textures[PLAYER] = TextureManager::LoadTexture("Textures/player.png");
	textures[WALL_SIDE] = TextureManager::LoadTexture("Textures/wallSide.png");
	textures[WALL_TOP_T] = TextureManager::LoadTexture("Textures/wallTopT.png");
	textures[WALL_TOP_R] = TextureManager::LoadTexture("Textures/wallTopR.png");
	textures[WALL_TOP_B] = TextureManager::LoadTexture("Textures/wallTopB.png");
	textures[WALL_TOP_L] = TextureManager::LoadTexture("Textures/wallTopL.png");

	textures[PROJECTILES] = TextureManager::LoadTexture("Textures/projectiles.png");
	textures[DOORS] = TextureManager::LoadTexture("Textures/doors.png");
}

Map::~Map() {
	for (int i = 0; i < map.size(); i++)
		map[i].clear();

	map.clear();
}   