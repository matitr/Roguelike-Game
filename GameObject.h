#pragma once
#include "SDL.h"

class Unit;

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

public:
	template <class T>
	void collisionUnit(T *gameObj);

	template <class T>
	bool detectCollision(T *gameObj);


	void test(Unit * u);
	GameObject(GameObjectType objType, ObjectHitboxType hitbType);
	~GameObject();
};

