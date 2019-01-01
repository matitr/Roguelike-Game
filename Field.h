#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "myMath.h"
#include <typeinfo>
#include <iostream>

class Room;

enum class FieldType { BasicWall, Wall, Floor, FloorHallway, Door, Abyss, None };

class Field : public GameObject {
	bool isGround = false;
	FieldType fieldType;
	PointInt fieldPos;
	bool drawFieldLast = false;

	std::vector<GameObject*> collisionObjects;
public:
	double f, g, h; // A* search algorithm
	Field* prevField; // A* search algorithm

	void setPosition(int _x, int _y);

	SDL_Texture * getTexture() { return texture; }
	bool ground() { return isGround; }
	FieldType type() { return fieldType; }
	int x() { return fieldPos.x; }
	int y() { return fieldPos.y; }
	PointInt& getFieldPos() { return fieldPos; }
	void setDrawLast() { drawFieldLast = true; }
	bool drawLast() { return drawFieldLast; }

	void drawField(int x, int y);
	void draw(SDL_Point* startRender) {}

	double distanceEdgesX(Field* otherField);
	double distanceEdgesY(Field* otherField);

	void addCollisionObj(GameObject* obj) { collisionObjects.push_back(obj); }
	std::vector<GameObject*>& getCollisionObj() { return collisionObjects; }

	Field(SDL_Texture* txt, SDL_Rect& _srcRect, FieldType);
	~Field();

};

