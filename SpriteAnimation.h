#pragma once
#include <SDL.h>

struct AnimationDetails;


// frameCounter begin from 1
// currFrame	begin from 0
class SpriteAnimation {
private:
	SDL_Point firstFrame;
	int frames, frameTime, currFrame, frameCounter;
	int framesInRow;
	SDL_Rect &srcRectAnimation;
public:
	bool lastFrameEnded() { return (frameCounter == frameTime && currFrame + 1 == frames) ? true : false; }
	void setOnEndOfFrame() { frameCounter = frameTime; }
	void setFrameTime(int fTime) { frameTime = fTime; }

	void updateTexture();

	void setFirstFrame();
	void setLastFrame();
	void setFrameCounter(SpriteAnimation& animationOther);
	bool firstTimuUnitOfFrame(int frame);

	SpriteAnimation(AnimationDetails& animationD, SDL_Rect &_srcRect);
	~SpriteAnimation();
};

