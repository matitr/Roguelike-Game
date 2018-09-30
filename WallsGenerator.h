#pragma once

#define MIN_COLUMN_SPACE 5
#define MIN_COLUMN_SIZE 2
#define COLUMN_MAX_WIDTH_TO_HEIGHT 2.6
#define COLUMN_MAX_HEIGHT_TO_WIDTH 2

class LevelGenerator;
class Room;


class WallsGenerator {


public:
	void generateSymetrical(LevelGenerator* levelGen, Room* room);

	WallsGenerator();
	~WallsGenerator();
};

