#include "Map.h"
#include "TextureManager.h"
#include <time.h>


void Map::generateNewMap() {
	int x1, y1, x2, y2;
	x1 = BORDER_SIZE;
	x2 = MAP_WIDTH - BORDER_SIZE;
	y1 = BORDER_SIZE;
	y2 = MAP_HEIGHT - BORDER_SIZE;
	MapDivideField container;
	container.x = 0;
	container.y = 0;
	container.w = MAP_SIZE;
	container.h = MAP_SIZE;
//	generateMapField(x1, y1, x2 - 1, y2 - 1, rand()%2, 0);
	generateNewMap(1);
}

void Map::generateNewMap(int gfgsd) {
	int roomsNumber = 1 + 1 + 2 + 2 + rand() % 5 + 25;
	rooms.resize(roomsNumber);
	int x, y;

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[0] = new Room(MAP_WIDTH / 2 - 10, MAP_HEIGHT / 2 - 10, x + 20, y + 20); // start room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[roomsNumber - 1] = new Room(x, y, x + 40, y + 40); // boss room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[1] = new Room(x, y, x + 13, y + 13); // secret room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[2] = new Room(x, y, x + 13, y + 13); // secret room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[3] = new Room(x, y, x + 7, y + 7); // treasure room

	x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
	rooms[4] = new Room(x, y, x + 7, y + 7); // treasure room

	int i, j;
	bool goodPosition = false;

	for (i = roomsNumber - 2; i > 4; i--) {
		x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
		y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 50) + BORDER_SIZE;
		rooms[i] = new Room(x, y, x + rand() % 15 + 40, y + rand() % 15 + 40); // treasure room
	}

	for (i = roomsNumber - 1; i > 0; i--) {
		goodPosition = false;

		while (!goodPosition && i != roomsNumber - 1) {
			x = rand() % (MAP_WIDTH - BORDER_SIZE - BORDER_SIZE - 70) + BORDER_SIZE;
			y = rand() % (MAP_HEIGHT - BORDER_SIZE - BORDER_SIZE - 70) + BORDER_SIZE;
			rooms[i]->changePosition(x, y);
			goodPosition = true;

			for (j = roomsNumber - 1; j > i; j--) {
				if (rooms[i]->x1 <= rooms[j]->x1) {
					if (rooms[i]->x2 >= rooms[j]->x1) {
						if (rooms[i]->y1 <= rooms[j]->y1) {
							if (rooms[i]->y2 >= rooms[j]->y1) {
								goodPosition = false;
							}
						}
						else { // rooms[i]->y1 >= rooms[j]->y1
							if (rooms[i]->y1 <= rooms[j]->y2) {
								goodPosition = false;
							}
						}
					}
				}
				else { // rooms[i]->x1 >= rooms[j]->x1
					if (rooms[i]->x1 <= rooms[j]->x2) {
						if (rooms[i]->y1 <= rooms[j]->y1) {
							if (rooms[i]->y2 >= rooms[j]->y1) {
								goodPosition = false;
							}
						}
						else { // rooms[i]->y1 >= rooms[j]->y1
							if (rooms[i]->y1 <= rooms[j]->y2) {
								goodPosition = false;
							}
						}
					}
				}
			}
		}
	}

	for (i = 0; i < roomsNumber; i++)
		createRoom(rooms[i]);


	setCamera((rooms[0]->x2 - rooms[0]->x1) / 2 + rooms[0]->x1, (rooms[0]->y2 - rooms[0]->y1) / 2 + rooms[0]->y1);
}

void Map::generateMapField(int x1, int y1, int x2, int y2, bool divideWidth, int depth) {
	Room* room = new Room(x1, y1, x2, y2);
	createFieldWalls(room);
//	render();
//	createRoom(room);
	if ((x2 - x1) < 25 || (y2 - y1) < 15) {
		return;
	}
//	else if (((x2 - x1) < 45 || (y2 - y1) < 45)) {
	else if (depth == MAX_MAP_GEN_DEPTH) {
		if (rand() % 100 < 1)
			return;
		Room* room = new Room(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
		createRoom(room);
//		render();
		//		createRoom(room);
		return;
	}

	if (divideWidth) {// [      |        ]
		min = (int)(0.4 * (x2 - x1));
		max = (int)(0.6   * (x2 - x1));
		int separationX = x1 + ((rand() % (max - min + 1)) + min);
//		separationX = x1 + (x2 - x1) / 2;
//		createRoomConectionsX(room, separationX);
		generateMapField(x1, y1, separationX, y2, !divideWidth, depth+1);
		generateMapField(separationX, y1, x2, y2, !divideWidth,depth + 1);

	}
	else {
		min = (int)(0.4 * (y2 - y1));
		max = (int)(0.6 * (y2 - y1));
		int separationY = y1 + ((rand() % (max - min + 1)) + min);
//		separationY = y1 + (y2 - y1) / 2;
//		createRoomConectionsY(room, separationY);
		generateMapField(x1, y1, x2, separationY, !divideWidth, depth+1);
		generateMapField(x1, separationY, x2, y2, !divideWidth, depth+1);

	}
}

void Map::createRoom(Room* room) {
	/*
	min = (int)(0.6 * (room->x2 - room->x1));
	max = (int)(0.8 * (room->x2 - room->x1));

	int temp = room->x1 + (rand() % (max - min + 1) + min);
	room->x1 = room->x1 + rand() % int((room->x2 - room->x1) * 0.2);
	room->x2 = temp;

	min = (int)(0.6 * (room->y2 - room->y1));
	max = (int)(0.8 * (room->y2 - room->y1));

	temp = room->y1 + (rand() % (max - min + 1) + min);
	room->y1 = room->y1 + rand() % int((room->y2 - room->y1) * 0.2);
	room->y2 = temp;

	int xIter, yIter;
		for (xIter = room->x1 + 1; xIter < room->x2; xIter++)
			for (yIter = room->y1 + 1; yIter < room->y2; yIter++) {
				map[xIter][yIter] = new Field(textures[WOOD_FLOOR]);
			}

//	for (xIter = room->x1; xIter <= xRoomMax; xIter++) { // x walls
//		map[xIter][room->y1] = new Field(textures[STONE]);
//		map[xIter][yRoomMax] = new Field(textures[STONE]);
//	}
//
//	for (yIter = room->y1; yIter <= yRoomMax; yIter++) { // y walls
//		map[room->x1][yIter] = new Field(textures[STONE]);
//		map[xRoomMax][yIter] = new Field(textures[STONE]);
//	}*/

	int xIter, yIter;
	for (xIter = room->x1 + 1; xIter < room->x2; xIter++)
		for (yIter = room->y1 + 1; yIter < room->y2; yIter++) {
			map[xIter][yIter] = new Field(textures[WOOD_FLOOR]);
		}

}

void Map::createFieldWalls(Room* room) {
	for (int i = room->x1; i <= room->x2; i++) { // x walls
		map[i][room->y1] = new Field(textures[STONE]);
		map[i][room->y2] = new Field(textures[STONE]);
	}

	for (int i = room->y1; i <= room->y2; i++) { // y walls
		map[room->x1][i] = new Field(textures[STONE]);
		map[room->x2][i] = new Field(textures[STONE]);
	}
}

void Map::createRoomConectionsX(Room* room, int xSeparation) {
	int y = room->y1 + (room->y2 - room->y1) / 2; int x;
	for (x = (xSeparation - room->x1) / 2; x < xSeparation + (room->x2 - xSeparation) / 2; x++)
		map[x][y] = new Field(textures[WOOD_FLOOR]);
}

void Map::createRoomConectionsY(Room* room, int ySeparation) {
	int x = room->x1 + (room->x2 - room->x1) / 2;
	for (int y = (ySeparation - room->y1) / 2; y < ySeparation + (room->y2 - ySeparation) / 2; y++)
		map[x][y] = new Field(textures[WOOD_FLOOR]);
}

Map::Map(int _hCenter, int _wCenter) : RenderMap(_hCenter, _wCenter) {
	hCenter = _hCenter;
	wCenter = _wCenter;

	textures[WOOD_FLOOR] = TextureManager::LoadTexture("Textures/woodFloor.png");
	textures[WATER] = TextureManager::LoadTexture("Textures/water.png");
	textures[STONE] = TextureManager::LoadTexture("Textures/stone.png");
}

Map::~Map() {
	for (int i = 0; i < map.size(); i++)
		map[i].clear();

	map.clear();
}   