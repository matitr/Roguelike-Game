#pragma once
#include "Animation.h"
#include <unordered_map>
#include "Map.h"
#include "Projectile.h"
class Projectile;

enum ActionType {Stand, Walk, Roll};

class Unit {
protected:
	std::unordered_map <ActionType, Animation*> animations;

	int textureY = 0, textureFrame = 0, textureFrameTime = 100, textureFrames = 2, frameCounter = 0;

	SDL_Rect srcrect, dstrect;
	PointFloat position; // sdlpoint
	SDL_Texture *texture;

	int speed;
	float hp;
	float maxHp;

	ActionType unitActionName;
public:
	SDL_Point velocity;
	SDL_Point movement;
	virtual void draw(SDL_Point* startRender);
	virtual void update(Map* map, SDL_Rect& fieldRect) = 0;

	void addAnimation(ActionType actionName, int _yPosTexture, int _frames, int _frameTime);
	void setAnimation(ActionType actionName);
	void setPosition(int x, int y);

	Unit(SDL_Texture *txt, int width,int height);
	~Unit();
};

