#pragma once

class Animation {
public:
	int frames;
	int frameTime;
	int yPosTexture;
public:

	Animation(int y, int f, int frameT);
	~Animation();
};

