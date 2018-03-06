#include "Animation.h"
#include "Game.h"


Animation::Animation(int y, int f, int frameT) {
	frames = f;
	frameTime = frameT;
	yPosTexture = y;
}

Animation::~Animation() {

}
	
