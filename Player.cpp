#include "Player.h"
#include "Game.h"
#include "Map.h"


void Player::update(Map* map, SDL_Rect& fieldRect) {
	if (velocity.x < 0 && !map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h]->ground())
		return;
	else if (velocity.x > 0 && !map->map[(position.x + velocity.x * speed + srcrect.w) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h]->ground())
		return;
	else if (velocity.y < 0 && !map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h]->ground())
		return;
	else if (velocity.y > 0 && !map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h) / fieldRect.h]->ground())
		return;

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

Player::Player(SDL_Texture* txt) : Unit(txt, 60, 60){
	addAnimation("Stand", 0, 2, 15);
	addAnimation("Walk", 1, 2, 15);
};


Player::~Player(){

}
