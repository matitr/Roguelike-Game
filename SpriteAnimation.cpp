#include "SpriteAnimation.h"
#include "DataBase.h"

void SpriteAnimation::setFirstFrame() {
	srcRectAnimation.x = firstFrame.x;
	srcRectAnimation.y = firstFrame.y;

	frameCounter = 0;
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

void SpriteAnimation::updateTexture() {
	if (!(frameCounter % frameTime) && frameCounter) { // Next texture frame
		if (currFrame + 1 == frames) { // The last texture frame has ended

			srcRectAnimation.x = firstFrame.x;
			srcRectAnimation.y = firstFrame.y;

			frameCounter = 0;
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
	}
	frameCounter++;
}

SpriteAnimation::SpriteAnimation(AnimationDetails& animationD, SDL_Rect &_srcRect)
	: firstFrame(animationD.firstFrame), frames(animationD.frames), frameTime(animationD.frameTime), framesInRow(animationD.framesInRow), srcRectAnimation(_srcRect) {

	frameCounter = 0;
	currFrame = 0;
}


SpriteAnimation::~SpriteAnimation() {

}
