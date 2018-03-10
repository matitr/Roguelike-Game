#include "Player.h"
#include "Game.h"
#include "Map.h"
#include <math.h>


void Player::update(Map* map, SDL_Rect& fieldRect) {
	Field *field = map->map[(position.x + velocity.x * speed + srcrect.w) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h];
	/*
	if (velocity.x < 0 && !map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h]->ground())
		return;
	else if (velocity.x > 0 && !map->map[(position.x + velocity.x * speed + srcrect.w) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h]->ground())
		return;
	else if (velocity.y < 0 && !map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h]->ground())
		return;
	else if (velocity.y > 0 && !map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h) / fieldRect.h]->ground())
		return;
		*/

	if (velocity.x < 0)
		field = map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h];
	else if (velocity.x > 0)
		field = map->map[(position.x + velocity.x * speed + srcrect.w) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h];

	if (velocity.x != 0 && field->type() == Door && !map->currentRoom()->battle) {
		Field * f = map->currentRoom()->doorsConnection[field];
		map->changeRoom(map->currentRoom()->roomConnection[field], map->currentRoom()->doorsConnection[field]);
		setPosition(map->getCameraX(), map->getCameraY());
		velocity.x = 0;
		velocity.y = 0;
		setAnimation(Stand);
		return;
	}
	else if (!field->ground())
		velocity.x = 0;

	if (velocity.y < 0)
		field = map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h];
	else if (velocity.y > 0)
		field = map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h) / fieldRect.h];

	if (velocity.y != 0 && field->type() == Door && !map->currentRoom()->battle) {

	}
	else if (!field->ground())
		velocity.y = 0;

	map->moveCamera(velocity.x * speed, velocity.y * speed);
	
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;

	if (frameCounter == textureFrameTime) {
		frameCounter = 0;
		if (textureFrame == textureFrames - 1)
			textureFrame = 0;
		else
			textureFrame++;
	}
	frameCounter++;
}

void Player::movement(int x, int y) {
	velocity.x = x;
	velocity.y = y;
}

Projectile* Player::attack(SDL_Texture* txt, int x, int y) {
	Projectile* p = new Projectile(txt, 25, 25, 0, 3, 10);

	float dir = atan2(y - 17 - position.y, x - 17 - position.x);

	if (x - position.x > 0)
		p->setDirection(dir * (180.0 / 3.1415));
//		p->setVelocity(1,0);
	else
//		p->setVelocity(-1, 0);
		p->setDirection(dir * (180.0 / 3.1415));

	p->setPosition(position.x, position.y);
	return p;
}

Player::Player(SDL_Texture* txt) : Unit(txt, 60, 60){
	addAnimation(Stand, 0, 2, 15);
	addAnimation(Walk, 1, 2, 15);
};


Player::~Player(){

}
