#pragma once
#include <vector>
#include "SDL.h"
#include "myMath.h"

class Room;
class Player;
class Map;
class Field;

enum class FieldType;

class LevelGenerator {
	SDL_Texture* levelTexture;

	Map& mapClass;
	std::vector<Room*>& rooms;

	std::vector<FieldType> mapFields;

	Map& map;
	Player* player;
	SDL_Rect fieldRect;

	inline FieldType& mapFieldType(int x, int y);

	void generateRooms(int &roomNumber);
	void findPositionForRooms(int roomsNumber);
	void createRoom(Room* room);
	void generateHallways(int &roomsNumber);
	void createHallwayH(PointInt&, PointInt&); // Horizontal, (p1.y >= p2.y)
	void createHallwayV(PointInt&, PointInt&); // Vertical, (p1.y >= p2.y)

	void generateRoomFields(Room* room);
	void createAllFields();
	void createRoomObjects(Room* room);
public:
	void generateNewMap();

	LevelGenerator(Map *map);
	~LevelGenerator();
};

