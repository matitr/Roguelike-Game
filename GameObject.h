#pragma once
#include "SDL.h"
#include <vector>

#define NO_COLLISION 999999

class Unit;
class Field;
struct Field;

class PointFloat {
public:
	float x, y;

	PointFloat() {
		x = 0;
		y = 0;
	}
};

enum GameObjectType {Static, Dynamic};
enum ObjectHitboxType { Rectangle, Circle };
struct TextureInfo;

class GameObject {

protected:
	SDL_Texture* texture;
	PointFloat position;
	PointFloat velocity;
	GameObjectType objectType;
	ObjectHitboxType hitboxType;
	int radius = 0;
	int radiusY = 0; // Only for Rectangle

	SDL_Rect srcRect, dstRect;
public:
	template <class T>
	void collisionUnit(T *gameObj);

	template <class T>
	bool detectCollision(T *gameObj);

	template <class T>
	float collisionDistance(T *gameObj);

	void collisionUnitFields(std::vector<std::vector<Field*>>& map, SDL_Rect& fieldRect);

	void setRadiusY(int y) { radiusY = y; }

	inline int getPositionX() const { return position.x; }
	inline int getPositionY() const { return position.y; }
	int getRadius() { return radius; }

	virtual void draw(SDL_Point* startRender) {}

	GameObject(SDL_Texture* txt, GameObjectType objType, ObjectHitboxType hitbType, int radius);
	GameObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType, int radius);
	GameObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType);
	~GameObject();
};

