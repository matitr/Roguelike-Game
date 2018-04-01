#pragma once
#include "SpriteAnimation.h"
#include "GameObject.h"

class Map;

class Projectile : public SpriteAnimation, public GameObject {
	int speed;
	float direction;
	float angle; // starting in middle right 
	float damage;
	bool enemyHitted;
public:
	void setDirection(float dir);
	void setAngle(float ang);
	void setPosition(int x, int y);

	bool update(Map* map, SDL_Rect& fieldRect);
	void draw(SDL_Point* startRender);

	float getDamage() { return damage; }
	void setEnemyHitted(bool hitted) { enemyHitted = hitted; }

	Projectile(SDL_Texture*txt, int width, int height, int _yIter, int _frames, int _frameTime);
	~Projectile();
};

