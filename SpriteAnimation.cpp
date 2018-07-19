#include "SpriteAnimation.h"
#include "DataBase.h"


void SpriteAnimation::updateTexture() {
	if (frameCounter == frameTime) { // Next texture frame
		if (currFrame + 1 == frames) { // The last texture frame has ended

			srcRectAnimation.x = firstFrame.x;
			srcRectAnimation.y = firstFrame.y;

			currFrame = 0;
		}
		else { // Update frame
			if ((currFrame / framesInRow) && (currFrame % framesInRow) == 1) { // First frame at the next row
				srcRectAnimation.x = firstFrame.x;
				srcRectAnimation.y = firstFrame.y;
			}
			else
				srcRectAnimation.x += srcRectAnimation.w;
			currFrame++;
		}
		frameCounter = 0;
	}
	frameCounter++;
}

void SpriteAnimation::setFirstFrame() {
	srcRectAnimation.x = firstFrame.x;
	srcRectAnimation.y = firstFrame.y;

	frameCounter = 1;
	currFrame = 0;
}

void SpriteAnimation::setLastFrame() {
	while (currFrame != frames - 1)
		updateTexture();
}

void SpriteAnimation::setFrameCounter(SpriteAnimation& animationOther) {
	setFirstFrame();

	while (frameCounter != animationOther.frameCounter)
		updateTexture();

}

bool SpriteAnimation::firstTimuUnitOfFrame(int frame) {
	return (currFrame == frame && frameCounter == 1); 
}

SpriteAnimation::SpriteAnimation(AnimationDetails& animationD, SDL_Rect &_srcRect)
	: firstFrame(animationD.firstFrame), frames(animationD.frames), frameTime(animationD.frameTime), framesInRow(animationD.framesInRow), srcRectAnimation(_srcRect) {

	srcRectAnimation.x = animationD.firstFrame.x;
	srcRectAnimation.y = animationD.firstFrame.y;
	frameCounter = 1;
	currFrame = 0;
}


SpriteAnimation::~SpriteAnimation() {

}
