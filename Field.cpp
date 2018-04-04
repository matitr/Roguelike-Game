#include "Field.h"
#include "Room.h"
#include "Game.h"


void Field::setPosition(int _x, int _y) {
	xPos = _x;
	yPos = _y;

	radius = dstRect.w / 2;
	position.x = (_x * dstRect.w) + radius;
	position.y = (_y * dstRect.h) + radius;
}

void Field::draw(int x, int y) {
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

Field::Field() : GameObject(Static, Square) {
	texture = nullptr;
}

Field::Field(SDL_Texture* txt) : GameObject(Static, Square) {
	texture = txt;
}

Field::Field(SDL_Texture* txt, SDL_Rect& _srcRect, FieldType _type) : GameObject(Static, Square) {
	texture = txt;
	fieldType = _type;
	if (_type == Floor)
		isGround = true;

	srcRect.x = _srcRect.x;
	srcRect.y = _srcRect.y;
	srcRect.w = _srcRect.w;
	srcRect.h = _srcRect.h;
	
	dstRect.w = _srcRect.w;
	dstRect.h = _srcRect.h;
}

Field::Field(SDL_Texture* txt, SDL_Rect* rectSize, int frames, int frameTime) : GameObject(Static, Square) {

}

Field::~Field() {

}