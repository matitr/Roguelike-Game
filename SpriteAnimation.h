#pragma once
#include <SDL.h>

class SpriteAnimation {
private:

	int frames, frameTime, currFrame, frameCounter;
	int framesInRow;
	SDL_Rect &srcRectAnimation;
public:
	bool lastFrameEnded() { return frameCounter == frames * frameTime ? true : false; }
	void updateTexture();

	SpriteAnimation(int _frames, int _frameTime, int _framesInRow, SDL_Rect &_srcRect);
	~SpriteAnimation();
};

