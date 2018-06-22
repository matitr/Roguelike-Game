#include "LevelGenerator.h"
#include "TextureManager.h"
#include "Room.h"
#include "Map.h"
#include "Chest.h"
#include "Player.h"
#include "Teleporter.h"



void LevelGenerator::generateNewMap() {
	int roomsNumber = 1 + 1 + 2 + 2 + rand() % 5 + 10;
	rooms.resize(roomsNumber);
	generateSpecialRooms(roomsNumber);
	levelTexture = TextureManager::textures[TextureFile::LEVEL_1];
	int x, y;
	int i;

	for (i = 1; i < roomsNumber; i++) {
		if (!rooms[i]) {
			x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
			y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
			rooms[i] = new Room(x, y, x + rand() % 20 + 30, y + rand() % 20 + 20, Monsters); // mobs room
		}
	}

	findPositionForRooms(roomsNumber);

	generateHallways(roomsNumber);

	for (i = 0; i < roomsNumber; i++)
		createRoomWalls(rooms[i]);

	for (i = 0; i < roomsNumber; i++)
		createRoom(rooms[i]);
}

void LevelGenerator::generateSpecialRooms(int &roomsNumber) {
	int x, y;
	rooms[0] = new Room(MAP_WIDTH / 2 - 15, MAP_HEIGHT / 2 - 15, MAP_WIDTH / 2 - 15 + 30, MAP_HEIGHT / 2 - 15 + 15, Spawn); // start room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[rand() % (roomsNumber - 5) + 1] = new Room(x, y, x + 50, y + 50, Boss); // boss room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 1] = new Room(x, y, x + 30, y + 15, Secret); // secret room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 2] = new Room(x, y, x + 30, y + 15, Secret); // secret room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 3] = new Room(x, y, x + 30, y + 17, Treasure); // treasure room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 4] = new Room(x, y, x + 30, y + 17, Treasure); // treasure room
}

void LevelGenerator::findPositionForRooms(int roomsNumber) {
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

void LevelGenerator::createRoom(Room* room) {
	int xIter, yIter;
	for (yIter = room->y1 + 1; yIter < room->y2; yIter++) {
		for (xIter = room->x1 + 1; xIter < room->x2; xIter++)
			if (!map.getField(xIter, yIter))
				map.getField(xIter, yIter) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WOOD_FLOOR], Floor);
		}

	if (room->type == Monsters || room->type == Spawn) {
		room->telporter = new Teleporter(((room->x2 - room->x1 + 1) / 2.0 + room->x1) * fieldRect.w, (room->y1 + (room->y2 - room->y1 + 1) / 2.0) * fieldRect.w);
		room->interactiveObjects.push_back(room->telporter);
	}

	if (room->type == Monsters || room->type == Boss) {
		room->spawnMonsters(&mapClass, player);
	}

	if (room->type == Treasure) {
		ChestObj* chestO = new ChestObj(room->roomCenterX(fieldRect.w), room->roomCenterY(fieldRect.h));
		room->interactiveObjects.push_back(chestO);

		int y = ((int)chestO->getPositionY() - chestO->getRadiusY()) / fieldRect.h;
		for (y; y <= (chestO->getPositionY() + chestO->getRadiusY()) / fieldRect.h; y++) {
			int x = ((int)chestO->getPositionX() - chestO->getRadius()) / fieldRect.w;
			for (x; x <= (chestO->getPositionX() + chestO->getRadius()) / fieldRect.w; x++) {
				map.getField(x, y)->addCollisionObj(chestO);
			}
		}
	}
}

void LevelGenerator::generateHallways(int &roomsNumber) {
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
						if (yij > -6 || yji > -6) { // Hallway with angle  -|

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
							rooms[i]->addConnection(map.getField(p1.x, p1.y), map.getField(p2.x, p1.y), rooms[j]);
							rooms[i]->addConnection(map.getField(p1.x, p1.y + 1), map.getField(p2.x, p1.y + 1), rooms[j]);
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
							rooms[i]->addConnection(map.getField(p1.x, p1.y), map.getField(p1.x, p2.y), rooms[j]);
							rooms[i]->addConnection(map.getField(p1.x + 1, p1.y), map.getField(p1.x + 1, p2.y), rooms[j]);
						}
						rooms[i]->addConnectedRoom(rooms[j]);
					}
				}
			}
		}
	}
}

void LevelGenerator::createHallwayH(SDL_Point& p1, SDL_Point& p2) { // Horizontal
	int x;

	for (x = p1.x + 1; x < p2.x; x++) {
		map.getField(x, p1.y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WOOD_FLOOR], Floor);
		map.getField(x,p1.y + 1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WOOD_FLOOR], Floor);
	}

	x = p1.x;
	for (int i = 0; i < 2; i++) {
		map.getField(x, p1.y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::DOORS], Door);
		map.getField(x, p1.y + 1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::DOORS], Door);
		x = p2.x;
	}
}

void LevelGenerator::createHallwayV(SDL_Point& p1, SDL_Point& p2) { // Vertical
	int y;

	for (y = p1.y + 1; y <= p2.y - 1; y++) {
		map.getField(p1.x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WOOD_FLOOR], Floor);
		map.getField(p2.x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WOOD_FLOOR], Floor);
	}

	y = p1.y;
	for (int i = 0; i < 2; i++) {
		map.getField(p1.x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::DOORS], Door);
		map.getField(p2.x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::DOORS], Door);
		y = p2.y;
	}
}

void LevelGenerator::createRoomWalls(Room* room) {
	for (int i = room->x1 + 1; i <= room->x2 - 1; i++) { // x walls
		if (!map.getField(i, room->y1)) { // TOP
			map.getField(i, room->y1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_SIDE0], Wall);
			map.getField(i, room->y1 - 1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_SIDE1], Wall);
			map.getField(i, room->y1 - 2) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_T], Wall);
		}

		if (!map.getField(i, room->y2)) { // BOTTOM
			map.getField(i, room->y2) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_B], Wall);
		}
	}

	for (int i = room->y1 - 1; i <= room->y2 - 1; i++) { // y walls
		if (!map.getField(room->x1, i)) { // LEFT
			map.getField(room->x1, i) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_L], Wall);
		}

		if (!map.getField(room->x2, i)) { // RIGHT
			map.getField(room->x2, i) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_R], Wall);
		}
	}

	map.getField(room->x1, room->y1 - 2) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_CORSEN_LT], Wall);
	map.getField(room->x2, room->y1 - 2) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_CORSEN_RT], Wall);
	map.getField(room->x1, room->y2) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_CORSEN_LB], Wall);
	map.getField(room->x2, room->y2) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_CORSEN_RB], Wall);

}

LevelGenerator::LevelGenerator(Map* _map) : mapClass(*_map), map(*_map), rooms(_map->rooms), player(_map->getPlayer()), fieldRect(_map->fieldRect) {

}


LevelGenerator::~LevelGenerator(){

}
