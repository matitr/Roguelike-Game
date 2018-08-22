#include "LevelGenerator.h"
#include "TextureManager.h"
#include "Room.h"
#include "Map.h"
#include "Chest.h"
#include "Player.h"
#include "Teleporter.h"
#include "Game.h"


FieldType& LevelGenerator::mapFieldType(int x, int y) {
	return mapFields[MAP_WIDTH * y + x];
}

void LevelGenerator::generateNewMap() {
	mapFields.resize(MAP_WIDTH * MAP_HEIGHT);

	int roomsNumber = 1 + 1 + 2 + 2 + rand() % 5 + 10;
	rooms.resize(roomsNumber);
	generateRooms(roomsNumber);
	levelTexture = TextureManager::textures[TextureFile::LEVEL_1];
	int x, y;
	int i;

	findPositionForRooms(roomsNumber);
	generateHallways(roomsNumber);

	for (i = 0; i < roomsNumber; i++)
		createRoom(rooms[i]);

	for (i = 0; i < roomsNumber; i++)
		addWallsDepth(rooms[i]);

	createAllFields();

	for (i = 0; i < roomsNumber; i++)
		createRoomObjects(rooms[i]);

	mapFields.clear();
}

void LevelGenerator::generateRooms(int &roomsNumber) {
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

	for (int i = 1; i < roomsNumber; i++) {
		if (!rooms[i]) {
			x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
			y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
			rooms[i] = new Room(x, y, x + rand() % 20 + 30, y + rand() % 20 + 20, Monsters); // mobs room
		}
	}
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

void LevelGenerator::generateHallways(int &roomsNumber) {
	int i, j, xji, xij, yji, yij;
	PointInt p1, p2;

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

							p2.y = p1.y;
							rooms[i]->addConnection(p1, p2, rooms[j]);
							p2.y++;
							createHallwayH(p1, p2);
							rooms[i]->addHallway(rooms[j], p1, p2);
							p1.y++;
							rooms[i]->addConnection(p1, p2, rooms[j]);
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

							p2.x = p1.x;
							createHallwayV(p1, p2);
							rooms[i]->addHallway(rooms[j], p1, p2);
							rooms[i]->addConnection(p1, p2, rooms[j]);
							p2.x++;
							createHallwayV(p1, p2);
							rooms[i]->addHallway(rooms[j], p1, p2);
							p1.x++;
							rooms[i]->addConnection(p1, p2, rooms[j]);
						}
						rooms[i]->addConnectedRoom(rooms[j]);
					}
				}
			}
		}
	}
}

void LevelGenerator::createHallwayH(PointInt& p1, PointInt& p2) { // Horizontal
	int x;

	for (x = p1.x + 1; x < p2.x; x++) {
		mapFieldType(x, p1.y) = FieldType::FloorHallway;
		mapFieldType(x, p1.y + 1) = FieldType::FloorHallway;
	}

	x = p1.x;
	for (int i = 0; i < 2; i++) {
		mapFieldType(x, p1.y) = FieldType::Door;
		mapFieldType(x, p1.y + 1) = FieldType::Door;
		x = p2.x;
	}
}

void LevelGenerator::createHallwayV(PointInt& p1, PointInt& p2) { // Vertical
	int y;

	for (y = p1.y + 1; y <= p2.y - 1; y++) {
		mapFieldType(p1.x, y) = FieldType::FloorHallway;
		mapFieldType(p2.x, y) = FieldType::FloorHallway;
	}

	y = p1.y;
	for (int i = 0; i < 2; i++) {
		mapFieldType(p1.x, y) = FieldType::Door;
		mapFieldType(p2.x, y) = FieldType::Door;
		y = p2.y;
	}
}

void LevelGenerator::createRoom(Room* room) {
	int xIter, yIter;
	for (yIter = room->y1 + 1; yIter < room->y2; yIter++) {
		for (xIter = room->x1 + 1; xIter < room->x2; xIter++)
			if (!map.getField(xIter, yIter))
				mapFieldType(xIter, yIter) = FieldType::Floor;
	}

	if (room->type == RoomType::Monsters)
		generateColumns(room);

//	if (room->type == RoomType::Spawn) {
//		xIter = room->x1 + (room->x2 - room->x1) / 2 + 2;
//		yIter = room->y1 + (room->y2 - room->y1) / 2 + 2;
//		mapFieldType(xIter, yIter) = FieldType::Wall;
//		mapFieldType(xIter + 1, yIter) = FieldType::Wall;
//		mapFieldType(xIter + 1, yIter + 1) = FieldType::Wall;
//		mapFieldType(xIter, yIter + 1) = FieldType::Wall;
//		mapFieldType(xIter + 1, yIter + 2) = FieldType::Wall;
//		mapFieldType(xIter, yIter + 2) = FieldType::Wall;
//
//		mapFieldType(xIter - 6, yIter) = FieldType::Wall;
//		mapFieldType(xIter - 5, yIter) = FieldType::Wall;
//		mapFieldType(xIter - 5, yIter + 1) = FieldType::Wall;
//		mapFieldType(xIter - 6, yIter + 1) = FieldType::Wall;
//
//		xIter - 4;
//		mapFieldType(xIter - 6, yIter) = FieldType::Wall;
//		mapFieldType(xIter - 6, yIter + 1) = FieldType::Wall;
//		mapFieldType(xIter - 5, yIter) = FieldType::Wall;
//		mapFieldType(xIter - 5, yIter + 1) = FieldType::Wall;
//		mapFieldType(xIter - 7, yIter) = FieldType::Wall;
//		mapFieldType(xIter - 7, yIter + 1) = FieldType::Wall;
//	}
}

void LevelGenerator::generateColumns(Room* room) {
	double maxCulumnsInColumn = (room->x2 - room->x1 + 1) / 7 - 1;
	double maxCulumnsInRow = (room->y2 - room->y1 + 1) / 5 - 1;
	
	std::vector<int> columnsNumber;

	
}

void LevelGenerator::addWallsDepth(Room* room) {

	for (int y = room->y1; y <= room->y2; y++) {
		for (int x = room->x1; x <= room->x2; x++) {
			if (mapFieldType(x, y) != FieldType::Wall && mapFieldType(x, y + 1) == FieldType::Wall && mapFieldType(x, y) != FieldType::Door && mapFieldType(x, y - 1) != FieldType::Door) {
				mapFieldType(x, y) = FieldType::Wall;
				mapFieldType(x, y - 1) = FieldType::Wall;
			}
		}
	}
}

void LevelGenerator::createAllFields() {

	for (int y = BORDER_SIZE; y < MAP_HEIGHT - BORDER_SIZE; y++) {
		for (int x = BORDER_SIZE; x < MAP_WIDTH - BORDER_SIZE; x++) {
			if (mapFieldType(x, y) == FieldType::FloorHallway) {
				map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WOOD_FLOOR], FieldType::Floor);
			}
			if (mapFieldType(x, y) == FieldType::Door) {
				map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::DOORS], FieldType::Door);
			}
			if (mapFieldType(x, y) == FieldType::Floor) {
				if (mapFieldType(x - 1, y) == FieldType::None || mapFieldType(x - 1, y) == FieldType::Wall) // Left is wall
					createFieldsLeftIsWall(x, y);

				if (mapFieldType(x + 1, y) == FieldType::None || mapFieldType(x + 1, y) == FieldType::Wall) // Right
					createFieldsRighttIsWall(x, y);

				if (mapFieldType(x - 1, y) == FieldType::Floor && mapFieldType(x , y - 1) == FieldType::Floor && mapFieldType(x - 1, y - 1) == FieldType::Wall)
					map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_COLUMN_NW], FieldType::Floor);
				else if (mapFieldType(x + 1, y) == FieldType::Floor && mapFieldType(x, y - 1) == FieldType::Floor && mapFieldType(x + 1, y - 1) == FieldType::Wall)
					map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_COLUMN_NE], FieldType::Floor);
				else if (mapFieldType(x, y - 1) == FieldType::Wall && (mapFieldType(x - 1, y) == FieldType::Floor && mapFieldType(x + 1, y) == FieldType::Floor))
					map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_N], FieldType::Floor);

				if (mapFieldType(x, y - 1) == FieldType::None || mapFieldType(x, y - 1) == FieldType::Wall) { // Up is wall
					map.getField(x, y - 1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_FRONT0], FieldType::Wall);
					map.getField(x, y - 2) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_FRONT1], FieldType::Wall);
					if (mapFieldType(x - 1, y - 3) != FieldType::Wall)
						map.getField(x, y - 3) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_COLUMN_SW], FieldType::Wall);
					else if (mapFieldType(x + 1, y - 3) != FieldType::Wall)
						map.getField(x, y - 3) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_COLUMN_SE], FieldType::Wall);
					else
						map.getField(x, y - 3) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_T], FieldType::Wall);
				}

				if (mapFieldType(x, y + 1) == FieldType::None || mapFieldType(x, y + 1) == FieldType::Wall) { // Down is wall
					if (mapFieldType(x - 1, y + 1) == FieldType::Wall && mapFieldType(x + 1, y + 1) == FieldType::Wall) {
						map.getField(x, y + 1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_B], FieldType::Wall);
						map.getField(x, y + 1)->setPositionShift(0, 0.4, 1);
						map.getField(x, y + 1)->setDrawLast();;
					}
				}

				if (!map.getField(x, y) && mapFieldType(x, y) == FieldType::Floor) {
					map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WOOD_FLOOR], FieldType::Floor);
				}
			}
		}
	}
}

void LevelGenerator::createFieldsLeftIsWall(int x, int y) {
	if (mapFieldType(x - 1, y - 1) != FieldType::Wall) {
		map.getField(x - 1, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_COLUMN_NE], FieldType::Wall);
		map.getField(x - 1, y)->setPositionShift(0, 0.4, 1);
		map.getField(x - 1, y)->setDrawLast();
	}
	else if (!(mapFieldType(x - 1, y + 3) != FieldType::Wall || mapFieldType(x - 1, y + 2) != FieldType::Wall || mapFieldType(x - 1, y + 1) != FieldType::Wall) ||
		(mapFieldType(x - 1, y + 3) == FieldType::Door || mapFieldType(x - 1, y + 2) == FieldType::Door || mapFieldType(x - 1, y + 1) == FieldType::Door)) {
		map.getField(x - 1, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_L], FieldType::Wall);
	}

	if (mapFieldType(x, y - 1) == FieldType::None || mapFieldType(x, y - 1) == FieldType::Wall) { // Left & Up is wall
		map.getField(x - 1, y - 3) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_CORNER_LT], FieldType::Wall);
		map.getField(x - 1, y - 1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_L], FieldType::Wall);
		map.getField(x - 1, y - 2) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_L], FieldType::Wall);
		map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_NW], FieldType::Floor);
	}

	if (mapFieldType(x, y + 1) == FieldType::None || mapFieldType(x, y + 1) == FieldType::Wall) { // Left & Down is wall
		map.getField(x - 1, y + 1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_CORNER_LB], FieldType::Wall);
	}

	if (mapFieldType(x - 1, y - 1) == FieldType::Wall) {
		if (mapFieldType(x - 1, y - 1) == FieldType::Wall && mapFieldType(x - 1, y - 2) == FieldType::Floor)
			map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_COLUMN_SW], FieldType::Floor);
		else if (mapFieldType(x, y - 1) == FieldType::Floor)
			map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_W], FieldType::Floor);
	}
}

void LevelGenerator::createFieldsRighttIsWall(int x, int y) {
	if (mapFieldType(x + 1, y - 1) != FieldType::Wall) {
		map.getField(x + 1, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_COLUMN_NW], FieldType::Wall);
		map.getField(x + 1, y)->setPositionShift(0, 0.4, 1);
		map.getField(x + 1, y)->setDrawLast();
	}
	else if (!(mapFieldType(x + 1, y + 3) != FieldType::Wall || mapFieldType(x + 1, y + 2) != FieldType::Wall || mapFieldType(x + 1, y + 1) != FieldType::Wall) ||
		(mapFieldType(x + 1, y + 3) == FieldType::Door || mapFieldType(x + 1, y + 2) == FieldType::Door || mapFieldType(x + 1, y + 1) == FieldType::Door)) {
		map.getField(x + 1, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_R], FieldType::Wall);
	}

	if (mapFieldType(x, y - 1) == FieldType::None || mapFieldType(x, y - 1) == FieldType::Wall) { // Right & Up is wall
		map.getField(x + 1, y - 3) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_CORNER_RT], FieldType::Wall);
		map.getField(x + 1, y - 1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_R], FieldType::Wall);
		map.getField(x + 1, y - 2) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_R], FieldType::Wall);
		map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_NE], FieldType::Floor);
	}
	if (mapFieldType(x, y + 1) == FieldType::None || mapFieldType(x, y + 1) == FieldType::Wall) { // Right & Down is wall
		map.getField(x + 1, y + 1) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::WALL_CORNER_RB], FieldType::Wall);
	}

	if (mapFieldType(x + 1, y - 1) == FieldType::Wall) {
		if (mapFieldType(x + 1, y - 2) == FieldType::Floor || mapFieldType(x + 1, y - 2) == FieldType::Door)
			map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_COLUMN_SE], FieldType::Floor);
		else if (mapFieldType(x, y - 1) == FieldType::Floor)
			map.getField(x, y) = new Field(levelTexture, TextureManager::fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_E], FieldType::Floor);
	}
}

void LevelGenerator::createRoomObjects(Room* room) {
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

LevelGenerator::LevelGenerator(Map* _map) : mapClass(*_map), map(*_map), rooms(_map->rooms), player(_map->getPlayer()), fieldRect(_map->fieldRect) {

}


LevelGenerator::~LevelGenerator(){

}
