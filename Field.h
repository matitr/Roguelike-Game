#pragma once
#include "Item.h"
#include "SDL.h"
#include <typeinfo>
#include <iostream>

class Room;

enum FieldType {Floor, Door, Wall};

class Field{
	SDL_Texture* texture;
	bool isGround = false;
	FieldType fieldType;
	int xPos, yPos;
public:
	void setPosition(int _x, int _y);

	SDL_Texture * getTexture() { return texture; }
	bool ground() { return isGround; }
	FieldType type() { return fieldType; }
	int x() { return xPos; }
	int y() { return yPos; }

	Field();
	Field(SDL_Texture* txt);
	Field(SDL_Texture* txt, FieldType);
	Field(SDL_Texture* txt, SDL_Rect* rectSize, int frames, int frameTime);
	~Field();

};

