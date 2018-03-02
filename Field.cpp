#include "Field.h"


void Field::addTexture(SDL_Texture* txt) {
	background = txt;
}

Field::Field() {
	background = nullptr;
}

Field::Field(SDL_Texture* txt) {
	background = txt;
}

Field::Field(SDL_Texture* txt, Item* _item) {
	background = txt;
	itemOnField = _item;
}

Field::~Field() {
	if (itemOnField)
		delete background;
}