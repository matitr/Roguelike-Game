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

public:
	double f, g, h; // A* search algorithm
	Field* prevField; // A* search algorithm

	void setPosition(int _x, int _y);

	SDL_Texture * getTexture() { return texture; }
	bool ground() { return isGround; }
	FieldType type() { return fieldType; }
	int x() { return xPos; }
	int y() { return yPos; }

	void draw(int x, int y);

	Field();
	Field(SDL_Texture* txt);
	Field(SDL_Texture* txt, SDL_Rect& _srcRect, FieldType);
	Field(SDL_Texture* txt, SDL_Rect* rectSize, int frames, int frameTime);
	~Field();

};

