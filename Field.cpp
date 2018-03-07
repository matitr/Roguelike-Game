#include "Field.h"
#include "Room.h"


Field::Field() {
	texture = nullptr;
}

Field::Field(SDL_Texture* txt) {
	texture = txt;
}

Field::Field(SDL_Texture* txt, bool _ground) {
	texture = txt;
	isGround = _ground;
}

Field::Field(SDL_Texture* txt, SDL_Rect* rectSize, int frames, int frameTime) {

}

Field::~Field() {

}