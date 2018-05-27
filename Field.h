#pragma once
#include "SDL.h"
#include "GameObject.h"
#include <typeinfo>
#include <iostream>

class Room;

enum FieldType {Floor, Door, Wall};

class Field : public GameObject {
	bool isGround = false;
	FieldType fieldType;
	int xPos, yPos;

	std::vector<GameObject*> collisionObjects;
public:
	double f, g, h; // A* search algorithm
	Field* prevField; // A* search algorithm

	void setPosition(int _x, int _y);

	SDL_Texture * getTexture() { return texture; }
	bool ground() { return isGround; }
	FieldType type() { return fieldType; }
	int x() { return xPos; }
	int y() { return yPos; }

	void drawField(int x, int y);
	void draw(SDL_Point* startRender) {}

	void addCollisionObj(GameObject* obj) { collisionObjects.push_back(obj); }
	std::vector<GameObject*>& getCollisionObj() { return collisionObjects; }

	Field(SDL_Texture* txt, SDL_Rect& _srcRect, FieldType);
	~Field();

};

