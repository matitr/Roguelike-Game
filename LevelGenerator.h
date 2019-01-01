#pragma once
#include <vector>
#include "SDL.h"
#include "myMath.h"
#include "WallsGenerator.h"

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
	WallsGenerator wallsGenerator;

	Map& map;
	Player* player;
	SDL_Rect fieldRect;

	inline FieldType& mapFieldType(int x, int y);

	void generateRooms(int &roomNumber);
	void findPositionForRooms(int roomsNumber);
	void generateHallways(int &roomsNumber);
	void createHallwayH(PointInt&, PointInt&); // Horizontal, (p1.y >= p2.y)
	void createHallwayV(PointInt&, PointInt&); // Vertical, (p1.y >= p2.y)

	void createRoom(Room* room);

	void setBaseWalls();
	void addWallsDepth(Room* room);
	void createAllFields();
	void createFieldsLeftIsWall(int x, int y);
	void createFieldsRighttIsWall(int x, int y);
	void createAbyss(int x, int y);
	void createRoomObjects(Room* room);
public:
	void setMapFieldType(int x, int y, FieldType type);
	const FieldType& getMapFieldType(int x, int y);
	void generateNewMap();

	LevelGenerator(Map *map);
	~LevelGenerator();
};

