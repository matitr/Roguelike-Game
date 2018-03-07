#pragma once
#include "Animation.h"
#include <unordered_map>
#include "Map.h"

class Unit {
protected:
	std::unordered_map <const char*, Animation*> animations;

	int textureY = 0, textureFrame = 0, textureFrameTime = 100, textureFrames = 2, frameCounter = 0;

	SDL_Rect srcrect, dstrect;
	SDL_Point position;
	SDL_Texture *texture;
	int speed;

	const char* unitActionName;
public:
	SDL_Point velocity;
	SDL_Point movement;
	void draw(SDL_Point* startRender);
	virtual void update(Map* map, SDL_Rect& fieldRect) = 0;

	void addAnimation(const char* actionName, int _yPosTexture, int _frames, int _frameTime);
	void setAnimation(const char* actionName);
	void setPosition(int x, int y);

	Unit(SDL_Texture *txt, int width,int height);
	~Unit();
};

