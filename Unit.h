#pragma once
#include "Animation.h"
#include <unordered_map>
#include "Map.h"
#include "Attacks.h"
#include "GameObject.h"

class Projectile;
class UnitAction;
class Attack;
class Movement;

enum ActionType {Stand, Walk, Roll, AttackProj};

class Unit : public GameObject {
protected:
	std::unordered_map <ActionType, UnitAction*> actions;
	std::list<ActionType> pattern;
	std::list<ActionType>::iterator currAction;

	int textureY = 0, textureFrame = 0, textureFrameTime = 100, textureFrames = 2, frameCounter = 0, textureFramesInRow;

	SDL_RendererFlip flip;

	float speed;
	float hp;
	float maxHp;

	// Hitbox
	int positionShiftX, positionShiftY;

public:
	PointFloat velocity;
	virtual bool update(std::list <Projectile*>& monsterAttacks, Map* map, SDL_Rect& fieldRect);
	virtual void draw(SDL_Point* startRender);
	void updateFrame();

	void addAction(ActionType action, Movement* move, Attack* attack, int yPosTexture, int frames, int frameTime, int attackFrame = -1);
	void addPattern(ActionType actionType);

	void setPosition(int x, int y);
	void setPositionShift(float positionShiftX, float positionShiftY, float hitboxRange);


	void setHp(int _hp) { hp = float(hp); }
	void takeDamage(float damage) { hp -= damage; }

	Unit(SDL_Texture *txt, int width,int height);
	~Unit();
	void renderCircle(int _x, int _y, int radius);
};

