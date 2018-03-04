#include "Field.h"
#include "Room.h"


void Field::addTexture(SDL_Texture* txt) {
	background = txt;
}

Field::Field() {
	background = nullptr;
	roomParent = nullptr;
	itemOnField = nullptr;
}

Field::Field(SDL_Texture* txt) {
	background = txt;
	roomParent = nullptr;
	itemOnField = nullptr;
}

Field::Field(SDL_Texture* txt, Room* parent) {
	background = txt;
	roomParent = parent;
	itemOnField = nullptr;
}

Field::Field(SDL_Texture* txt, Item* _item) {
	background = txt;
	roomParent = nullptr;
	itemOnField = _item;
}

Field::~Field() {
	if (itemOnField)
		delete background;
}