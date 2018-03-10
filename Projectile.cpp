#include "Projectile.h"
#include "Game.h"
#include "Map.h"
#include <math.h>

void Projectile::setDirection(float dir) {
	direction = dir * 3.14 / 180.0;
	angle = dir;
}

void Projectile::setVelocity(int x, int y) {
	velocity.x = x;
	velocity.y = y;
}

void Projectile::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

bool Projectile::update(Map* map, SDL_Rect& fieldRect) {
	if (!map->map[(position.x + velocity.x * projectileSpeed) / fieldRect.w][(position.y + velocity.y * projectileSpeed + srcRect.h / 2) / fieldRect.h]->ground())
		return false;
	else if (!map->map[(position.x + velocity.x * projectileSpeed + srcRect.w) / fieldRect.w][(position.y + velocity.y * projectileSpeed + srcRect.h / 2) / fieldRect.h]->ground())
		return false;
	else if (!map->map[(position.x + velocity.x * projectileSpeed) / fieldRect.w][(position.y + velocity.y * projectileSpeed + srcRect.h / 2) / fieldRect.h]->ground())
		return false;
	else if (!map->map[(position.x + velocity.x * projectileSpeed) / fieldRect.w][(position.y + velocity.y * projectileSpeed + srcRect.h) / fieldRect.h]->ground())
		return false;

//	direction = -90.0;
	position.x += projectileSpeed * cos(direction);
	position.y += projectileSpeed * sin(direction);

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
	dstRect.x = position.x - startRender->x;
	dstRect.y = position.y - startRender->y;

	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

Projectile::Projectile(SDL_Texture*txt, int width, int height, int _yIter, int _frames, int _frameTime) 
	: SpriteAnimation(txt,width,height,_yIter,_frames, _frameTime) {
	projectileSpeed = 5;
}


Projectile::~Projectile() {

}
