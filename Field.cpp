#include "Field.h"
#include "Room.h"
#include "Game.h"
#include "Map.h"


void Field::setPosition(int _x, int _y) {
	fieldPos.x = _x;
	fieldPos.y = _y;

	position.x = (_x * dstRect.w) + radius;
	position.y = (_y * dstRect.h) + radius;
}

void Field::drawField(int x, int y) {
	dstRect.x = x - positionShiftX;
	dstRect.y = y - positionShiftY;

	int h = dstRect.h;
	dstRect.h *= HEIGHT_SCALE;
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
	dstRect.h = h;
}

double Field::distanceEdgesX(Field* otherField) {
	float xDist = abs(otherField->position.x - position.x);
	if (xDist)
		xDist -= otherField->radius + radius;

	return xDist;
}

double Field::distanceEdgesY(Field* otherField) {
	float yDist = abs(otherField->position.y - position.y);
	if (yDist)
		yDist -= otherField->radiusY + radiusY;

	return yDist;
}

Field::Field(SDL_Texture* txt, SDL_Rect& _srcRect, FieldType _type) : GameObject(txt, Static, Rectangle, _srcRect.w / 2) {
	fieldType = _type;
	if (_type == FieldType::Floor)
		isGround = true;

	srcRect.x = _srcRect.x;
	srcRect.y = _srcRect.y;
	srcRect.w = _srcRect.w;
	srcRect.h = _srcRect.h;
	
	dstRect.w = _srcRect.w;
	dstRect.h = _srcRect.h;

	collisionObjects.reserve(4);
}

Field::~Field() {
	collisionObjects.clear();
}