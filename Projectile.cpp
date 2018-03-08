#include "Projectile.h"
#include "Game.h"
#include "Map.h"

void Projectile::setVelocity(int x, int y) {
	velocity.x = x;
	velocity.y = y;
}

void Projectile::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

bool Projectile::update(Map* map, SDL_Rect& fieldRect) {
	if (velocity.x < 0 && !map->map[(position.x + velocity.x * projectileSpeed) / fieldRect.w][(position.y + velocity.y * projectileSpeed + srcRect.h / 2) / fieldRect.h]->ground())
		return false;
	else if (velocity.x > 0 && !map->map[(position.x + velocity.x * projectileSpeed + srcRect.w) / fieldRect.w][(position.y + velocity.y * projectileSpeed + srcRect.h / 2) / fieldRect.h]->ground())
		return false;
	else if (velocity.y < 0 && !map->map[(position.x + velocity.x * projectileSpeed) / fieldRect.w][(position.y + velocity.y * projectileSpeed + srcRect.h / 2) / fieldRect.h]->ground())
		return false;
	else if (velocity.y > 0 && !map->map[(position.x + velocity.x * projectileSpeed) / fieldRect.w][(position.y + velocity.y * projectileSpeed + srcRect.h) / fieldRect.h]->ground())
		return false;


	position.x += velocity.x * projectileSpeed;
	position.y += velocity.y * projectileSpeed;

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
