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

class PointDouble {
public:
	double x, y;

	PointDouble() {
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
	PointDouble velocity;
	GameObjectType objectType;
	ObjectHitboxType hitboxType;
	int radius = 0;
	int radiusY = 0; // Only for Rectangle
	bool flatObjOnFloor = false;

	SDL_Rect srcRect, dstRect;

	// Hitbox
	int positionShiftX, positionShiftY;
public:
	template <class T>
	void collisionUnit(T *gameObj);

	template <class T>
	bool detectCollision(T *gameObj);

	template <class T>
	float collisionDistance(T *gameObj);

	template <class T>
	float distanceEdges(T *gameObj);

	void collisionUnitFields(std::vector<std::vector<Field*>>& map, SDL_Rect& fieldRect);

	void setRadiusY(int y) { radiusY = y; }
	void setFlatTextureOnFloor(bool f) { flatObjOnFloor = f; }

	void setPositionX(float x) { position.x = x; }
	void setPositionY(float y) { position.y = y; }
	void setPosition(int x, int y);
	void setPositionShift(float positionShiftX, float positionShiftY, float hitboxRange);

	inline int getPositionX() const { return position.x; }
	inline int getPositionY() const { return position.y; }
	int getRadius() { return radius; }
	int getRadiusY() { return radiusY; }
	bool flatTextureOnFloor() const { return flatObjOnFloor; }

	virtual void draw(SDL_Point* startRender);
	void draw();

	GameObject(SDL_Texture* txt, GameObjectType objType, ObjectHitboxType hitbType, int radius);
	GameObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType, int radius);
	GameObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType);
	~GameObject();
};

