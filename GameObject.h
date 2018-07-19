#pragma once
#include "SDL.h"
#include "myMath.h"
#include <vector>

#define NO_COLLISION 999999

class Unit;
class Field;
class Map;

enum GameObjectType {Static, Dynamic};
enum ObjectHitboxType { Rectangle, Circle };
struct TextureInfo;
struct ItemTextureInfo;

class GameObject {

protected:
	SDL_Texture* texture;
	PointDouble position;
	GameObjectType objectType;
	ObjectHitboxType hitboxType;
	int radius = 0;
	int radiusY = 0; // Only for Rectangle
	bool flatObjOnFloor = false;

	SDL_Rect srcRect, dstRect;

	// Hitbox
	int positionShiftX, positionShiftY;
public:
	PointDouble velocity;
	template <class T>
	void collisionUnit(T *gameObj);

	template <class T>
	bool detectCollision(T *gameObj);

	template <class T>
	float collisionDistance(T *gameObj);

	template <class T>
	float distanceEdges(T *gameObj);

	// Change position of unit when collision detected
	void collisionUnitFields(Map* map, SDL_Rect& fieldRect);

	void setRadius(int r) { radius = r; }
	void setRadiusY(int y) { radiusY = y; }
	void setFlatTextureOnFloor(bool f) { flatObjOnFloor = f; }

	void setPositionX(double x) { position.x = x; }
	void setPositionY(double y) { position.y = y; }
	void setPosition(double x, double y);
	void setPositionShift(float positionShiftX, float positionShiftY, float hitboxRange); // Percents
	void setPositionShiftY(float positionShiftY); // Pixels from top
	void setDstRectSize(int x, int y);

	const PointDouble& getPosition() const { return position; }
	inline double getPositionX() const { return position.x; }
	inline double getPositionY() const { return position.y; }
	int getRadius() { return radius; }
	int getRadiusY() { return radiusY; }
	int getPositionShiftY() const { return positionShiftY; }
	bool flatTextureOnFloor() const { return flatObjOnFloor; }

	virtual void draw(SDL_Point* startRender);
	void draw();

	GameObject(SDL_Texture* txt, GameObjectType objType, ObjectHitboxType hitbType, int radius);
	GameObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType, int radius);
	GameObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType);
	GameObject(ItemTextureInfo& txtInfo, SDL_Point& dstR);
	virtual ~GameObject();
};

