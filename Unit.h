#pragma once
#include "Animation.h"
#include <unordered_map>

class Unit {
protected:
	std::unordered_map <const char*, Animation*> animations;

	int textureI = 0, textureFrame = 0, textureFrameTime = 100, textureFrames = 2;

	SDL_Rect srcrect, dstrect;
	SDL_Point position;
	SDL_Texture *texture;
	int speed;
public:
	SDL_Point movement;
	void draw();

	void addAnimation(const char* actionName, int _yPosTexture, int _frames, int _frameTime);
	void setAnimation(const char* actionName);
	void setPosition(int x, int y);

	Unit(SDL_Texture *txt, int width,int height);
	~Unit();
};

