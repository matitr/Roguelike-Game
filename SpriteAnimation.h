#pragma once
#include <SDL.h>

struct AnimationDetails;

class SpriteAnimation {
private:
	SDL_Point firstFrame;
	int frames, frameTime, currFrame, frameCounter;
	int framesInRow;
	SDL_Rect &srcRectAnimation;
public:
	int getFrameCounter() { return frameCounter; }
	bool lastFrameEnded() { return frameCounter == frames * frameTime ? true : false; }
	void setOnEndOfFrame() { frameCounter = frameTime; }

	void setFirstFrame();
	void setLastFrame();
	void setFrameCounter(SpriteAnimation& animationOther);
	void updateTexture();

	SpriteAnimation(AnimationDetails& animationD, SDL_Rect &_srcRect);
	~SpriteAnimation();
};

