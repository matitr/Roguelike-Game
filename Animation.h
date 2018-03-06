#pragma once
#include "Sprite.h"
class Animation {
protected:
	int frames;
	int frameTime;
	int yPosTexture;
	int currFrame;
public:

	Animation(int y, int f, int frameT);
	~Animation();
};

