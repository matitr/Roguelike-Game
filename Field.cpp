#include "Field.h"
#include "Room.h"


void Field::setPosition(int _x, int _y) {
	xPos = _x;
	yPos = _y;
}

Field::Field() {
	texture = nullptr;
}

Field::Field(SDL_Texture* txt) {
	texture = txt;
}

Field::Field(SDL_Texture* txt, FieldType _type) {
	texture = txt;
	fieldType = _type;
	if (_type == Floor)
		isGround = true;
}

Field::Field(SDL_Texture* txt, SDL_Rect* rectSize, int frames, int frameTime) {

}

Field::~Field() {

}