#include "Map.h"
#include "TextureManager.h"
#include <time.h>
#include "Game.h"


void Map::generateNewMap() {
	int roomsNumber = 1 + 1 + 2 + 2 + rand() % 5 + 10;
	rooms.resize(roomsNumber);
	generateSpecialRooms(roomsNumber);
	levelTexture = TextureManager::textures[LEVEL_1];
	int x, y;
	int i, j;

	for (i = 1; i < roomsNumber; i++) {
		if (!rooms[i]) {
			x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
			y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
			rooms[i] = new Room(x, y, x + rand() % 20 + 40, y + rand() % 20 + 40, Monsters); // mobs room
		}
	}

	findPositionForRooms(roomsNumber);

	for (i = 0; i < roomsNumber; i++)
		createRoom(rooms[i]);

	generateHallways(roomsNumber);

	for (i = 0; i < roomsNumber; i++)
		createRoomWalls(rooms[i]);

	setSpawn(rooms[0], (rooms[0]->x2 - rooms[0]->x1) / 2 + rooms[0]->x1, (rooms[0]->y2 - rooms[0]->y1) / 2 + rooms[0]->y1);
	rooms[0]->setVisited(true);
	createMinimap();
}

void Map::generateSpecialRooms(int &roomsNumber) {
	int x, y;
	rooms[0] = new Room(MAP_WIDTH / 2 - 15, MAP_HEIGHT / 2 - 15, MAP_WIDTH / 2 - 15 + 30, MAP_HEIGHT / 2 - 15 + 30, Spawn); // start room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[rand() % (roomsNumber - 5) + 1] = new Room(x, y, x + 50, y + 50, Boss); // boss room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 1] = new Room(x, y, x + 13, y + 13, Secret); // secret room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 2] = new Room(x, y, x + 13, y + 13, Secret); // secret room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 3] = new Room(x, y, x + 7, y + 7, Treasure); // treasure room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 4] = new Room(x, y, x + 7, y + 7, Treasure); // treasure room
}

void Map::findPositionForRooms(int roomsNumber) {
	bool goodPosition = false;
	int closeRooms = 0, specialRooms, x, y, j;

	for (int i = 1; i < roomsNumber; i++) {
		goodPosition = false;

		while ((!goodPosition || (closeRooms - specialRooms) <= 0)) {
			specialRooms = 0;
			goodPosition = true;
			closeRooms = 0;
			x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 70) + BORDER_SIZE;
			y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 70) + BORDER_SIZE;
			rooms[i]->changePosition(x, y);

			for (j = 0; j < i; j++) {
				if (MIN_ROOM_SEPARATION >= rooms[j]->x1 - rooms[i]->x2 && MIN_ROOM_SEPARATION >= rooms[i]->x1 - rooms[j]->x2 &&
					MIN_ROOM_SEPARATION >= rooms[j]->y1 - rooms[i]->y2 && MIN_ROOM_SEPARATION >= rooms[i]->y1 - rooms[j]->y2)
					goodPosition = false;

				if (MAX_ROOM_SEPARATION >= rooms[j]->x1 - rooms[i]->x2 && MAX_ROOM_SEPARATION >= rooms[i]->x1 - rooms[j]->x2 &&
					MAX_ROOM_SEPARATION >= rooms[j]->y1 - rooms[i]->y2 && MAX_ROOM_SEPARATION >= rooms[i]->y1 - rooms[j]->y2) {
					if ((rooms[i]->x1 - rooms[j]->x2 >= MIN_ROOM_SEPARATION || rooms[j]->x1 - rooms[i]->x2 >= MIN_ROOM_SEPARATION) &&
						(!(rooms[i]->y1 - rooms[j]->y2 > -6 || rooms[j]->y1 - rooms[i]->y2 > -6))) // do not allow diagonal rooms
						closeRooms++;
					else if ((rooms[i]->y1 - rooms[j]->y2 >= MIN_ROOM_SEPARATION || rooms[j]->y1 - rooms[i]->y2 >= MIN_ROOM_SEPARATION) &&
						(!(rooms[i]->x1 - rooms[j]->x2 > -6 || rooms[j]->x1 - rooms[i]->x2 > -6))) // do not allow diagonal rooms
						closeRooms++;
				}
				if (rooms[j]->specialRoom)
					specialRooms++;
			}

		}
	}
}

void Map::createRoom(Room* room) {
	int xIter, yIter;
	for (xIter = room->x1 + 1; xIter < room->x2; xIter++)
		for (yIter = room->y1 + 1; yIter < room->y2; yIter++) {
			map[xIter][yIter] = new Field(levelTexture, TextureManager::textureSrcRect[WOOD_FLOOR], Floor);
		}

}

void Map::generateHallways(int &roomsNumber) {
	int i, j, xji, xij, yji, yij;
	SDL_Point p1, p2, pointBetween;

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
						if (yij > -6) { // Hallway with angle  -|

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
							rooms[i]->addHallway(rooms[j], p1, p2);
							rooms[i]->addConnection(map[p1.x][p1.y], map[p2.x][p1.y], rooms[j]);
							rooms[i]->addConnection(map[p1.x][p1.y + 1], map[p2.x][p1.y + 1], rooms[j]);
						}
						rooms[i]->addConnectedRoom(rooms[j]);
					}
					else if (yij > 0) {
						if (xij > -6 || xji > -6) { // Hallway with angle  _|
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
							rooms[i]->addHallway(rooms[j], p1, p2);
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
		map[x][p1.y] = new Field(levelTexture, TextureManager::textureSrcRect[WOOD_FLOOR], Floor);
		map[x][p1.y + 1] = new Field(levelTexture, TextureManager::textureSrcRect[WOOD_FLOOR], Floor);
	}

	x = p1.x;
	for (int i = 0; i < 2; i++) {
		map[x][p1.y] = new Field(levelTexture, TextureManager::textureSrcRect[DOORS], Door);
		map[x][p1.y + 1] = new Field(levelTexture, TextureManager::textureSrcRect[DOORS], Door);
		x = p2.x;
	}
}

void Map::createHallwayV(SDL_Point& p1, SDL_Point& p2) { // Vertical
	int y;
	Field *field;

	for (y = p1.y + 1; y <= p2.y; y++) {
		map[p1.x][y] = new Field(levelTexture, TextureManager::textureSrcRect[WOOD_FLOOR], Floor);
		map[p2.x][y] = new Field(levelTexture, TextureManager::textureSrcRect[WOOD_FLOOR], Floor);
	}

	y = p1.y;
	for (int i = 0; i < 2; i++) {
		map[p1.x][y] = new Field(levelTexture, TextureManager::textureSrcRect[DOORS], Door);
		map[p2.x][y] = new Field(levelTexture, TextureManager::textureSrcRect[DOORS], Door);
		y = p2.y;
	}
}

void Map::createRoomWalls(Room* room) {
	for (int i = room->x1; i <= room->x2; i++) { // x walls
		if (!map[i][room->y1]) { // TOP
			map[i][room->y1] = new Field(levelTexture, TextureManager::textureSrcRect[WALL_SIDE], Wall);
			map[i][room->y1 - 1] = new Field(levelTexture, TextureManager::textureSrcRect[WALL_SIDE], Wall);
			map[i][room->y1 - 2] = new Field(levelTexture, TextureManager::textureSrcRect[WALL_TOP_T], Wall);
		}

		if (!map[i][room->y2]) { // BOTTOM
			map[i][room->y2] = new Field(levelTexture, TextureManager::textureSrcRect[WALL_TOP_B], Wall);
		}
	}

	for (int i = room->y1 - 1; i <= room->y2 - 1; i++) { // y walls
		if (!map[room->x1][i]) { // LEFT
			map[room->x1][i] = new Field(levelTexture, TextureManager::textureSrcRect[WALL_TOP_L], Wall);
		}

		if (!map[room->x2][i]) { // RIGHT
			map[room->x2][i] = new Field(levelTexture, TextureManager::textureSrcRect[WALL_TOP_R], Wall);
		}
	}
}

void Map::createMinimap() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 184, 77, 200);
	SDL_SetRenderTarget(Game::renderer, minimap);
	SDL_Rect r;

	r.h = MAP_HEIGHT;
	r.w = MAP_WIDTH;
	r.x = 0;
	r.y = 0;
	SDL_SetRenderDrawColor(Game::renderer, 0, 51, 51, 100);
	SDL_RenderFillRect(Game::renderer, &r);

	SDL_SetRenderDrawColor(Game::renderer, 255, 184, 77, 200);

	r.w = 1;
	r.h = 1;
	int x, y;
	for (int i = 0; i < rooms.size(); i++) { // for every room
		if (rooms[i]->visited && std::find(roomsOnMiniman.begin(), roomsOnMiniman.end(), rooms[i]) == roomsOnMiniman.end()) {
			for (x = rooms[i]->x1; x < rooms[i]->x2; x++) {
				for (y = rooms[i]->y1; y < rooms[i]->y2; y++) {
					if (map[x][y] && (map[x][y]->type() == Floor)) {
						r.x = x;
						r.y = y;
						SDL_RenderFillRect(Game::renderer, &r);
					}
				}
			}
			addToMinimap(rooms[i]);
		}
	}

	SDL_SetRenderTarget(Game::renderer, NULL);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void Map::addToMinimap(Room* room) {
	SDL_SetRenderDrawColor(Game::renderer, 255, 184, 77, 200);
	SDL_SetRenderTarget(Game::renderer, minimap);
	SDL_Rect r;
	r.w = 1;
	r.h = 1;
	int x, y;

	for (std::list<Room*>::iterator it = room->hallways.begin(); it != room->hallways.end(); it++) { // for every hallway in room
		if (std::find(roomsOnMiniman.begin(), roomsOnMiniman.end(), (*it)) == roomsOnMiniman.end()) {
			for (x = (*it)->x1; x <= (*it)->x2; x++) {
				for (y = (*it)->y1; y <= (*it)->y2; y++) {
					if (map[x][y] && (map[x][y]->type() == Floor || map[x][y]->type() == Door)) {
						r.x = x;
						r.y = y;
						SDL_RenderFillRect(Game::renderer, &r);
					}
				}
			}
			for (std::list<Room*>::iterator it_room = (*it)->connectedRooms.begin(); it_room != (*it)->connectedRooms.end(); it_room++) { // for other room in hallway
				if ((*it_room) != room) {
					for (x = (*it_room)->x1; x < (*it_room)->x2; x++) {
						for (y = (*it_room)->y1; y < (*it_room)->y2; y++) {
							if (map[x][y] && (map[x][y]->type() == Floor)) {
								r.x = x;
								r.y = y;
								SDL_RenderFillRect(Game::renderer, &r);
							}
						}
					}
					roomsOnMiniman.push_back(*it_room);
				}
			}
			roomsOnMiniman.push_back(*it);
		}
	}

	SDL_SetRenderTarget(Game::renderer, NULL);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
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
			newY = (y + 2) * fieldRect.h;
		else
			newY = (y - 2) * fieldRect.h;
	}
	else if (map[x - 1][y]->type() == Door) { // Doors are horizontally
		newX = x * fieldRect.w - fieldRect.w / 2;
		if (y + 1 <= room->y2) // Top
			newY = (y + 2) * fieldRect.h;
		else
			newY = (y - 2) * fieldRect.h;
	}
	else if (map[x][y + 1]->type() == Door) { // Doors are vertically
		newY = y * fieldRect.w + fieldRect.w / 2;
		if (x + 1 <= room->x2) // Left
			newX = (x + 2) * fieldRect.w;
		else
			newX = (x - 2) * fieldRect.w;

	}
	else { // Doors are vertically
		newY = y * fieldRect.w - fieldRect.w / 2;
		if (x + 1 <= room->x2)
			newX = (x + 2) * fieldRect.w;
		else
			newX = (x - 2) * fieldRect.w;
	}

	currRoom = room;
	setCamera(newX, newY);
	addToMinimap(room);

}

Map::Map(int _hCenter, int _wCenter) : RenderMap(_hCenter, _wCenter) {
	hCenter = _hCenter;
	wCenter = _wCenter;
}

Map::~Map() {
	for (int i = 0; i < map.size(); i++)
		map[i].clear();

	map.clear();
}   