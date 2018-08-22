#pragma once
#include <SDL.h>

#define FRAME_ENDED -1

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
	bool lastFrameEnded() { return (currFrame + 1 == frames && frameCounter == FRAME_ENDED) ? true : false; }
	void setOnEndOfFrame() { frameCounter = frameTime; frameCounter = FRAME_ENDED; }
	void setFrameTime(int fTime) { frameTime = fTime; }

	void updateTexture(float frameTimeMultReciprocal = 0);

	void setFirstFrame();
	void setLastFrame();
	void setFrameCounter(SpriteAnimation& animationOther);
	bool firstTimuUnitOfFrame(int frame, float attackSpeedMult);

	SpriteAnimation(AnimationDetails& animationD, SDL_Rect &_srcRect);
	~SpriteAnimation();
};

