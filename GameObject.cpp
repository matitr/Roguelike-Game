#include "GameObject.h"
#include <math.h>
#include "Player.h"
#include "Field.h"
#include "Projectile.h"
#include "InteractiveObject.h"
#include "Game.h"

template <class T>
void GameObject::collisionUnit(T *gameObj) {
	if (gameObj->hitboxType == Circle) {
		if (((position.x - gameObj->position.x)*(position.x - gameObj->position.x)
			+ (position.y - gameObj->position.y)*(position.y - gameObj->position.y)) <= (radius + gameObj->radius)*(radius + gameObj->radius)) {

			float dist = sqrtf((position.x - gameObj->position.x)*(position.x - gameObj->position.x) + (position.y - gameObj->position.y)*(position.y - gameObj->position.y));

			float overlap = 0.5f * (dist - radius - gameObj->radius);

			if (dist <= radius || dist <= gameObj->radius) {
				overlap = radius > gameObj->radius ? radius : gameObj->radius;
				overlap *= -0.5;

				if (!(int)(dist)) {
					float dir = atan2(rand() % 100 - 50, rand() % 100 - 50);

					position.x -= cos(dir) * overlap;
					position.y -= sin(dir) * overlap;

					gameObj->position.x += cos(dir) * overlap;
					gameObj->position.y += sin(dir) * overlap;

					return;
				}
			}
			position.x -= overlap * (position.x - gameObj->position.x) / dist;
			position.y -= overlap * (position.y - gameObj->position.y) / dist;

			gameObj->position.x += overlap * (position.x - gameObj->position.x) / dist;
			gameObj->position.y += overlap * (position.y - gameObj->position.y) / dist;
		}
	}
	else { // Rectangle

	}
}

template void GameObject::collisionUnit<Unit>(Unit *gameObj);
template void GameObject::collisionUnit<Field>(Field *gameObj);
template void GameObject::collisionUnit<Projectile>(Projectile *gameObj);


template <class T>
bool GameObject::detectCollision(T *gameObj) {
	if (hitboxType == Circle) {
		if (gameObj->hitboxType == Circle) {
			if (((position.x - gameObj->position.x)*(position.x - gameObj->position.x) + (position.y - gameObj->position.y)*(position.y - gameObj->position.y))
				<= (radius + gameObj->radius)*(radius + gameObj->radius))
				return true;
		}
		else { // Rectangle
			float minX = position.x < (gameObj->position.x + gameObj->radius) ? position.x : (gameObj->position.x + gameObj->radius);
			float deltaX = position.x - ((gameObj->position.x - gameObj->radius) > minX ? (gameObj->position.x - gameObj->radius) : minX);

			float minY = position.y < (gameObj->position.y + gameObj->radiusY) ? position.y : (gameObj->position.y + gameObj->radiusY);
			float deltaY = position.y - ((gameObj->position.y - gameObj->radiusY) > minY ? (gameObj->position.y - gameObj->radiusY) : minY);

			if ((deltaX * deltaX + deltaY * deltaY) < (radius * radius))
				return true;
		}
	}
	else { // this obj hitbox is Rectangle
		if (gameObj->hitboxType == Circle) {
			float minX = gameObj->position.x < (position.x + radius) ? gameObj->position.x : (position.x + radius);
			float deltaX = gameObj->position.x - ((position.x - radius) > minX ? (position.x - radius) : minX);

			float minY = gameObj->position.y < (position.y + radiusY) ? gameObj->position.y : (position.y + radiusY);
			float deltaY = gameObj->position.y - ((position.y - radiusY) > minY ? (position.y - radiusY) : minY);

			if ((deltaX * deltaX + deltaY * deltaY) < (gameObj->radius * gameObj->radius))
				return true;
		}
		else { // Collision Rectangle - Rectangle

		}
	}

	return false;
}

template bool GameObject::detectCollision<Unit>(Unit *gameObj);
template bool GameObject::detectCollision<Player>(Player *gameObj);
template bool GameObject::detectCollision<Field>(Field *gameObj);
template bool GameObject::detectCollision<Projectile>(Projectile *gameObj);
template bool GameObject::detectCollision<InteractiveObject>(InteractiveObject *gameObj);
template bool GameObject::detectCollision<GameObject>(GameObject *gameObj);


template <class T>
float GameObject::collisionDistance(T *gameObj) {
	if (hitboxType == Circle) {
		if (gameObj->hitboxType == Circle) {
			if (((position.x - gameObj->position.x)*(position.x - gameObj->position.x) + (position.y - gameObj->position.y)*(position.y - gameObj->position.y))
				<= (radius + gameObj->radius)*(radius + gameObj->radius))
				return sqrt((position.x - gameObj->position.x)*(position.x - gameObj->position.x) + (position.y - gameObj->position.y)*(position.y - gameObj->position.y));
		}
		else { // Rectangle
			float minX = position.x < (gameObj->position.x + gameObj->radius) ? position.x : (gameObj->position.x + gameObj->radius);
			float deltaX = position.x - ((gameObj->position.x - gameObj->radius) > minX ? (gameObj->position.x - gameObj->radius) : minX);

			float minY = position.y < (gameObj->position.y + gameObj->radiusY) ? position.y : (gameObj->position.y + gameObj->radiusY);
			float deltaY = position.y - ((gameObj->position.y - gameObj->radiusY) > minY ? (gameObj->position.y - gameObj->radiusY) : minY);

			if ((deltaX * deltaX + deltaY * deltaY) < (radius * radius))
				return sqrt(deltaX * deltaX + deltaY * deltaY);
		}
	}
	else { // this obj hitbox is Rectangle
		if (gameObj->hitboxType == Circle) {
			float minX = gameObj->position.x < (position.x + radius) ? gameObj->position.x : (position.x + radius);
			float deltaX = gameObj->position.x - ((position.x - radius) > minX ? (position.x - radius) : minX);

			float minY = gameObj->position.y < (position.y + radiusY) ? gameObj->position.y : (position.y + radiusY);
			float deltaY = gameObj->position.y - ((position.y - radiusY) > minY ? (position.y - radiusY) : minY);

			if ((deltaX * deltaX + deltaY * deltaY) < (gameObj->radius * gameObj->radius))
				return sqrt(deltaX * deltaX + deltaY * deltaY);
		}
		else { // Collision Rectangle - Rectangle

		}
	}

	return NO_COLLISION;
}

template float GameObject::collisionDistance<InteractiveObject>(InteractiveObject *gameObj);
template float GameObject::collisionDistance<Unit>(Unit *gameObj);


template <class T>
float GameObject::distanceEdges(T *gameObj) {
	if (hitboxType == Circle) {
		if (gameObj->hitboxType == Circle) {
			return sqrt((position.x - gameObj->position.x)*(position.x - gameObj->position.x) + (position.y - gameObj->position.y)*(position.y - gameObj->position.y)) - radius - gameObj->radius;
		}
		else { // Rectangle
			float minX = position.x < (gameObj->position.x + gameObj->radius) ? position.x : (gameObj->position.x + gameObj->radius);
			float deltaX = position.x - ((gameObj->position.x - gameObj->radius) > minX ? (gameObj->position.x - gameObj->radius) : minX);

			float minY = position.y < (gameObj->position.y + gameObj->radiusY) ? position.y : (gameObj->position.y + gameObj->radiusY);
			float deltaY = position.y - ((gameObj->position.y - gameObj->radiusY) > minY ? (gameObj->position.y - gameObj->radiusY) : minY);

			return sqrt(deltaX * deltaX + deltaY * deltaY);
		}
	}
	else { // this obj hitbox is Rectangle
		if (gameObj->hitboxType == Circle) {
			float minX = gameObj->position.x < (position.x + radius) ? gameObj->position.x : (position.x + radius);
			float deltaX = gameObj->position.x - ((position.x - radius) > minX ? (position.x - radius) : minX);

			float minY = gameObj->position.y < (position.y + radiusY) ? gameObj->position.y : (position.y + radiusY);
			float deltaY = gameObj->position.y - ((position.y - radiusY) > minY ? (position.y - radiusY) : minY);

			return sqrt(deltaX * deltaX + deltaY * deltaY);
		}
		else { // Collision Rectangle - Rectangle

		}
	}

	return NO_COLLISION;
}

template float GameObject::distanceEdges<Unit>(Unit *gameObj);
template float GameObject::distanceEdges<Player>(Player *gameObj);


void GameObject::collisionUnitFields(std::vector<std::vector<Field*>>& map, SDL_Rect& fieldRect) {
	int fieldX, fieldY;
	Field* field;
	float minX, deltaX, minY, deltaY;

	for (fieldX = (position.x - radius) / fieldRect.w; fieldX <= (position.x + radius) / fieldRect.w; fieldX++) {
		for (fieldY = (position.y - radius) / fieldRect.h; fieldY <= (position.y + radius) / fieldRect.h; fieldY++) {
			field = map[fieldX][fieldY];
			if (field->type() != Floor) {
				minX = position.x < (field->getPositionX() + field->getRadius()) ? position.x : (field->getPositionX() + field->getRadius());
				deltaX = position.x - ((field->getPositionX() - field->getRadius()) > minX ? (field->getPositionX() - field->getRadius()) : minX);

				minY = position.y < (field->getPositionY() + field->getRadius()) ? position.y : (field->getPositionY() + field->getRadius());
				deltaY = position.y - ((field->getPositionY() - field->getRadius()) > minY ? (field->getPositionY() - field->getRadius()) : minY);

				if ((deltaX * deltaX + deltaY * deltaY) < (radius * radius)) {
					if (abs(deltaX) > abs(deltaY) && deltaX) {
						if (deltaX > 0)
							position.x += radius - deltaX;
						else
							position.x -= radius + deltaX;
					}
					if (abs(deltaY) > abs(deltaX) && deltaY)
						if (deltaY > 0)
							position.y += radius - deltaY;
						else
							position.y -= radius + deltaY;
				}
			}
		}
	}

}

void GameObject::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void GameObject::setPositionShift(float _positionShiftX, float _positionShiftY, float _hitboxRange) {
	positionShiftX = _positionShiftX * dstRect.w;
	positionShiftY = _positionShiftY * dstRect.h;
	radius = (_hitboxRange * dstRect.w) / 2;
}

void  GameObject::draw(SDL_Point* startRender) {
	dstRect.x = position.x - startRender->x - dstRect.w / 2;
	dstRect.y = (position.y - startRender->y) - dstRect.h / 2;


	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

void GameObject::draw() {
	dstRect.x = position.x - dstRect.w / 2;
	dstRect.y = position.y - dstRect.h / 2;


	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

GameObject::GameObject(SDL_Texture* txt, GameObjectType objType, ObjectHitboxType hitbType, int _radius)
	: objectType(objType), hitboxType(hitbType), radius(_radius), radiusY(_radius), texture(txt) {

}

GameObject::GameObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType, int _radius)
	: objectType(objType), hitboxType(hitbType), radius(_radius), radiusY(_radius) {

	texture = txtInfo.texture;
	srcRect = txtInfo.srcRect;
	dstRect.w = txtInfo.dstRect.w;
	dstRect.h = txtInfo.dstRect.h;
}

GameObject::GameObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType)
	: objectType(objType), hitboxType(hitbType), radius(txtInfo.dstRect.w / 2), radiusY(radius) {

	texture = txtInfo.texture;
	srcRect = txtInfo.srcRect;
	dstRect.w = txtInfo.dstRect.w;
	dstRect.h = txtInfo.dstRect.h;

	positionShiftX = dstRect.w / 2;
	positionShiftY = dstRect.h / 2;
}

GameObject::~GameObject() {

}
