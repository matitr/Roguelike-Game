#include "Player.h"
#include "Game.h"



Player::Player(SDL_Texture* txt) : Unit(txt, 32, 64){
	addAnimation("Stand", 0, 3, 100);
	addAnimation("Walk", 1, 8, 100);
};


Player::~Player(){

}
