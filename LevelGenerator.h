#pragma once
#include <vector>
#include "SDL.h"

class Room;
class Player;
class Map;
class Field;

class LevelGenerator {
	SDL_Texture* levelTexture;

	Map& mapClass;
	std::vector<Room*>& rooms;

	std::vector<std::vector<Field*>>& map;
	Player* player;
	SDL_Rect fieldRect;

	void generateSpecialRooms(int &roomNumber);
	void findPositionForRooms(int roomsNumber);
	void createRoom(Room* room);
	void generateHallways(int &roomsNumber);
	void createHallwayH(SDL_Point&, SDL_Point&); // Horizontal, (p1.y >= p2.y)
	void createHallwayV(SDL_Point&, SDL_Point&); // Vertical, (p1.y >= p2.y)
	void createRoomWalls(Room* room);
public:
	void generateNewMap();

	LevelGenerator(Map *map);
	~LevelGenerator();
};

