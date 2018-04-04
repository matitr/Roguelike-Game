#pragma once
#include <SDL.h>

class SpriteAnimation {
protected:

	int frames, frameTime, currFrame, frameCounter;
//	int yIter;
public:
	SpriteAnimation(SDL_Texture*txt, int width, int height, int _yIter, int _frames, int _frameTime);
	~SpriteAnimation();
};

