#pragma once
#include "SDL.h"
#include <vector>

class Unit;
class Field;

class PointFloat {
public:
	float x, y;

	PointFloat() {
		x = 0;
		y = 0;
	}
};

enum GameObjectType {Static, Dynamic};
enum ObjectHitboxType { Square, Circle };

class GameObject {

protected:
	SDL_Texture* texture;
	PointFloat position;
	PointFloat velocity;
	GameObjectType objectType;
	ObjectHitboxType hitboxType;
	int radius;

	SDL_Rect srcRect, dstRect;
public:
	template <class T>
	void collisionUnit(T *gameObj);

	template <class T>
	bool detectCollision(T *gameObj);

	inline int getPositionX() { return position.x; }
	inline int getPositionY() { return position.y; }
	int getRadius() { return radius; }

	GameObject(GameObjectType objType, ObjectHitboxType hitbType);
	~GameObject();
};

