#include "SpriteAnimation.h"



SpriteAnimation::SpriteAnimation(SDL_Texture*txt, int width, int height, int _yIter, int _frames, int _frameTime) {
//	yIter = _yIter;
	frames = _frames;
	frameTime = _frameTime;
}


SpriteAnimation::~SpriteAnimation() {

}
