#include "Sprite.h"
#include "Game.h"



void Sprite::draw(SDL_Rect& dstRect) {
	SDL_RenderCopy(Game::renderer, texture, NULL, &dstRect);
}

Sprite::Sprite(SDL_Texture* txt) {
	texture = txt;
}

Sprite::~Sprite() {

}