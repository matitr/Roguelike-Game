#pragma once
#include "SpriteAnimation.h"

class Map;

class PointFloat {
public:
	float x, y;

	PointFloat() {
		x = 0;
		y = 0;
	}
};

class Projectile : public SpriteAnimation {
	int projectileSpeed;
	PointFloat velocity;
	PointFloat position;
	float direction;
	float angle; // starting in bottom right
public:
	void setDirection(float dir);
	void setAngle(float ang);
	void setPosition(int x, int y);

	bool update(Map* map, SDL_Rect& fieldRect);
	void draw(SDL_Point* startRender);

	Projectile(SDL_Texture*txt, int width, int height, int _yIter, int _frames, int _frameTime);
	~Projectile();
};

