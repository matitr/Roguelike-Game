#pragma once
#include "SpriteAnimation.h"

class Map;

class Projectile : public SpriteAnimation {
	int projectileSpeed;
	SDL_Point velocity;
	SDL_Point position;
public:
	void setVelocity(int x, int y);
	void setPosition(int x, int y);

	bool update(Map* map, SDL_Rect& fieldRect);
	void draw(SDL_Point* startRender);

	Projectile(SDL_Texture*txt, int width, int height, int _yIter, int _frames, int _frameTime);
	~Projectile();
};

