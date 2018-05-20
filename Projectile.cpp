#include "Projectile.h"
#include "Game.h"
#include "Map.h"
#include <math.h>
#include <iostream>

void Projectile::setDirection(float dir) {
	direction = dir;
	angle = dir * 180.0 / 3.14159265;

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

bool Projectile::update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit) {
	if (enemyHitted) {
		enemyHitted = false;

		staticPassives[StaticPassiveName::pierceShots]--;
		if (staticPassives[StaticPassiveName::pierceShots] == -1)
			return false;
	}

	if (staticPassives[StaticPassiveName::homing] && closestUnit)
		homingShot(closestUnit);

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
	dstRect.y = (position.y - startRender->y) * HEIGHT_SCALE - dstRect.h / 2 - heightFromGround;

	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

void Projectile::homingShot(Unit* closestUnit) {
	double dist;
	if ((dist = distanceEdges(closestUnit)) > 150)
		return;

	float x = closestUnit->getPositionX() - position.x;
	float y = closestUnit->getPositionY() - position.y;
	double vectorMultiply = x * velocity.x + y * velocity.y;
	double distanceMultiply = sqrt(pow(x, 2) + pow(y, 2)) * sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	double direction2 = acos(vectorMultiply / distanceMultiply);
	double angle2 = direction2 * 180.0 / 3.14159265;

	double cross = velocity.x * y - velocity.y * x;

//	if (cross < 0)
//		direction2 *= -1;

	float change = int(angle2 * 0.09 + 1);
	if (dist < 40)
		change = rand() % 22;

	if (cross < 0) {
		angle -= change;

		if (angle < -180)
			angle = 180 - (angle + 180);
	}
	else {
		angle += change;
		
		if (angle > 180)
			angle = -180 + (angle - 180);
	}

	velocity.x = cos(angle * 3.14 / 180.0) * speed;
	velocity.y = sin(angle * 3.14 / 180.0) * speed;
}

Projectile::Projectile(AnimationDetails& animation, ItemPassives& passives)
	: frames(animation.frames), frameTime(animation.frameTime), GameObject(animation.txt, Dynamic, Circle, animation.width / 2), staticPassives(passives) {
	speed = 5;
	damage = 1;
	enemyHitted = false;

	srcRect.w = animation.width;
	srcRect.h = animation.height;
	srcRect.x = 0;
	srcRect.y = animation.yIter;

	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = animation.width;
	dstRect.h = animation.height;

	heightFromGround = 20;
}


Projectile::~Projectile() {

}
