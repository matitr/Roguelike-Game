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
	bool lastFrameEnded() { return frameCounter == frames * frameTime ? true : false; }
	void setOnEndOfFrame() { frameCounter = frameTime; }

	void updateTexture();

	void setFirstFrame();
	void setLastFrame();
	void setFrameCounter(SpriteAnimation& animationOther);
	bool firstTimuUnitOfFrame(int frame);

	SpriteAnimation(AnimationDetails& animationD, SDL_Rect &_srcRect);
	~SpriteAnimation();
};

