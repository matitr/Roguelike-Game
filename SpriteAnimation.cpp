#include "SpriteAnimation.h"



SpriteAnimation::SpriteAnimation(SDL_Texture*txt, int width, int height, int _yIter, int _frames, int _frameTime) {
//	yIter = _yIter;
	frames = _frames;
	frameTime = _frameTime;
	srcRect.w = width;
	srcRect.h = height;
	srcRect.x = 0;
	srcRect.y = _yIter;

	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = width;
	dstRect.h = height;

}


SpriteAnimation::~SpriteAnimation() {

}
