#include "Unit.h"
#include "Game.h"

void Unit::draw() {
	srcrect.x = srcrect.w * textureFrame;
	SDL_RenderCopy(Game::renderer, texture, &srcrect, &dstrect);

}

void Unit::update() {
	dstrect.x += velocity.x;
	dstrect.y += velocity.y;

	if (frameCounter == textureFrameTime) {
		frameCounter = 0;
		if (textureFrame == textureFrames - 1)
			textureFrame = 0;
		else
			textureFrame++;
	}
	frameCounter++;
}

void Unit::addAnimation(const char* actionName, int _yPosTexture, int _frames, int _frameTime) {
	animations[actionName] = new Animation(_yPosTexture, _frames, _frameTime);
}

void Unit::setAnimation(const char* actionName) {
	if (unitActionName == actionName)
		return;

	unitActionName = actionName;
	frameCounter = 0;
	textureY = animations[actionName]->yPosTexture;
	textureFrame = 0;
	textureFrameTime = animations[actionName]->frameTime;
	textureFrames = animations[actionName]->frames;

	srcrect.y = dstrect.h * textureY;
}

void Unit::setPosition(int x, int y) {
	position.x = x;
	position.y = y;


}

Unit::Unit(SDL_Texture *txt, int width, int height) {
	texture = txt;

	dstrect.x = 100;
	dstrect.y = 100;
	srcrect.w = width;
	dstrect.w = width;
	srcrect.h = height;
	dstrect.h = height;
}


Unit::~Unit() {

}
