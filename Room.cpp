#include "Room.h"
#include "SDL.h"


void Room::changeValues(int _x1, int _y1, int _x2, int _y2) {
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;
}

void Room::changePosition(int _x1, int _y1) {
	x2 = _x1 + (x2 - x1);
	y2 = _y1 + (y2 - y1);

	x1 = _x1;
	y1 = _y1;
}

Room::Room(int _x1, int _y1, int _x2, int _y2){
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;
}


Room::~Room(){

}
