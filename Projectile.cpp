#include "Projectile.h"
#include "Game.h"
#include "Map.h"
#include <math.h>

void Projectile::setDirection(float dir) {
	direction = dir;
	angle = dir * 180.0 / 3.14;

	velocity.x = cos(direction) * speed;
	velocity.y = sin(direction) * speed;
}

void Projectile::setAngle(float ang) {
	direction = ang * 3.14 / 180.0;
	angle = ang;

	velocity.x = cos(direction) * speed;
	velocity.y = sin(direction) * speed;
}

void Projectile::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

bool Projectile::update(Map* map, SDL_Rect& fieldRect) {
	if (enemyHitted)
		return false;

	position.x += velocity.x;
	position.y += velocity.y;

	if (!map->map[(position.x) / fieldRect.w][(position.y + radius) / fieldRect.h]->ground())
		return false;
	else if (!map->map[(position.x + radius) / fieldRect.w][(position.y) / fieldRect.h]->ground())
		return false;
	else if (!map->map[(position.x) / fieldRect.w][(position.y - radius) / fieldRect.h]->ground())
		return false;
	else if (!map->map[(position.x - radius) / fieldRect.w][(position.y) / fieldRect.h]->ground())
		return false;
	
	if (frameCounter == frameTime) {
		frameCounter = 0;
		if (currFrame == frames - 1)
			currFrame = 0;
		else
			currFrame++;
	}
	frameCounter++;

	return true;
}

void Projectile::draw(SDL_Point* startRender) {
	srcRect.x = srcRect.w * currFrame;
	dstRect.x = position.x - startRender->x - dstRect.w / 2;
	dstRect.y = position.y - startRender->y - dstRect.h / 2;

	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

Projectile::Projectile(SDL_Texture*txt, int width, int height, int _yIter, int _frames, int _frameTime) 
	: SpriteAnimation(txt,width,height,_yIter,_frames, _frameTime), GameObject(Dynamic, Circle) {
	texture = txt;
	speed = 5;
	damage = 1;
	enemyHitted = false;
	radius = width / 2;

	srcRect.w = width;
	srcRect.h = height;
	srcRect.x = 0;
	srcRect.y = _yIter;

	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = width;
	dstRect.h = height;
}


Projectile::~Projectile() {

}
