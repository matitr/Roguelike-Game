#include "SpriteAnimation.h"


void SpriteAnimation::updateTexture() {
	if (!(frameCounter % frameTime) && frameCounter) { // Next texture frame
		if (currFrame + 1 == frames) { // The last texture frame has ended

			srcRectAnimation.x = srcRectAnimation.x - srcRectAnimation.w * (currFrame % framesInRow);
			srcRectAnimation.y = srcRectAnimation.y - srcRectAnimation.h * (currFrame / framesInRow);

			frameCounter = 0;
			currFrame = 0;
		}
		else { // Update frame
			if ((currFrame / framesInRow) && (currFrame % framesInRow) == 1) { // First frame at the next row
				srcRectAnimation.x = srcRectAnimation.x - srcRectAnimation.w * (currFrame % framesInRow);
				srcRectAnimation.y += srcRectAnimation.h;
			}
			else
				srcRectAnimation.x += srcRectAnimation.w;
			currFrame++;
		}
	}
	frameCounter++;
}

SpriteAnimation::SpriteAnimation(int _frames, int _frameTime, int _framesInRow, SDL_Rect &_srcRect)
	: frames(_frames), frameTime(_frameTime), framesInRow(_framesInRow), srcRectAnimation(_srcRect) {

	frameCounter = 0;
	currFrame = 0;
}


SpriteAnimation::~SpriteAnimation() {

}
