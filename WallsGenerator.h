#pragma once
#include "myMath.h"

#define MIN_COLUMN_SPACE 5
#define MIN_COLUMN_SIZE 2
#define COLUMN_MAX_WIDTH_TO_HEIGHT 2.6
#define COLUMN_MAX_HEIGHT_TO_WIDTH 2

#define MIN_WALL_RECT_SPACE 5

class LevelGenerator;
class Room;
enum class FieldType;


class WallsGenerator {

	bool canPlaceWall(LevelGenerator* mapGen, RectInt wallRect);
	void placeWall(LevelGenerator* mapGen, RectInt wallRect, FieldType fieldType);
public:
	void generateSymetrical(LevelGenerator* levelGen, Room* room, FieldType fieldType);
	void generateConnectedToWall(LevelGenerator* levelGen, Room* room, FieldType fieldType);


	WallsGenerator();
	~WallsGenerator();
};

