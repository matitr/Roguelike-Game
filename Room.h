#pragma once
#include <unordered_map>
#include "Field.h"


#define WOOD_FLOOR 0
#define WATER 1
#define STONE 2

class SDL_Texture;
class FIELD;

class Room {

public:
	int x1, y1;
	int x2, y2;


	void changeValues(int _x1, int _y1, int _x2, int _y2);
	void changePosition(int _x1, int _y1);

	Room(int _x1, int _y1, int _x2, int _y2);
	~Room();
};

