#pragma once
#include "Animation.h"
#include <unordered_map>
#include "Map.h"
#include "Attacks.h"

class Projectile;
class UnitAction;
class Attack;
class Movement;

enum ActionType {Stand, Walk, Roll, AttackProj};

class Unit {
protected:
	std::unordered_map <ActionType, UnitAction*> actions;
	std::list<ActionType> pattern;
	std::list<ActionType>::iterator currAction;

	int textureY = 0, textureFrame = 0, textureFrameTime = 100, textureFrames = 2, frameCounter = 0;

	SDL_Rect srcrect, dstrect;
	PointFloat position; // sdlpoint
	SDL_Texture *texture;
	SDL_RendererFlip flip;

	int speed;
	float hp;
	float maxHp;

public:
	SDL_Point velocity;
	SDL_Point movement;
	virtual void update(std::list <Projectile*>& monsterAttacks, Map* map, SDL_Rect& fieldRect);
	virtual void draw(SDL_Point* startRender);
	void updateFrame();

	void addAction(ActionType action, Movement* move, Attack* attack, int yPosTexture, int frames, int frameTime, int attackFrame = -1, int loops = 1);
	void addPattern(ActionType actionType);

	void setPosition(int x, int y);

	inline int getPositionX() { return position.x; }
	inline int getPositionY() { return position.y; }
	inline int getPosMiddleX() { return position.x + dstrect.w / 2; }
	inline int getPosMiddleY() { return position.y + dstrect.h / 4 * 3.3; }

	Unit(SDL_Texture *txt, int width,int height);
	~Unit();
};

