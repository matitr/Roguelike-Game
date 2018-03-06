#include "Player.h"
#include "Game.h"


void Player::movement(int x, int y) {
	velocity.x = x;
	velocity.y = y;
}

Player::Player(SDL_Texture* txt) : Unit(txt, 59, 118){
	addAnimation("Stand", 0, 4, 5);
	addAnimation("Walk", 1, 4, 5);
};


Player::~Player(){

}
