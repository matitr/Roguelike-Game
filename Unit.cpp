#include "Unit.h"
#include "Game.h"

void Unit::draw() {
	srcrect.x = srcrect.w * static_cast<int>((SDL_GetTicks() / textureFrameTime) % textureFrames);

	SDL_RenderCopy(Game::renderer, texture, &srcrect, &dstrect);
}

void Unit::addAnimation(const char* actionName, int _yPosTexture, int _frames, int _frameTime) {
	animations[actionName] = new Animation(_yPosTexture, _frames, _frameTime);
}

void Unit::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

Unit::Unit(SDL_Texture *txt, int width, int height) {
	texture = txt;

	srcrect.w = width;
	dstrect.w = width;
	srcrect.h = height;
	dstrect.h = height;
}


Unit::~Unit() {

}
