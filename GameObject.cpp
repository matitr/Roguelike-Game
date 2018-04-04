#include "GameObject.h"
#include <math.h>
#include "Player.h"
#include "Field.h"
#include "Projectile.h"

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
				if (!dist) {
					dist = 1;

					position.x -= overlap;
					position.y -= overlap;

					gameObj->position.x += overlap;
					gameObj->position.y += overlap;
					overlap = 0;
				}
			}
			position.x -= overlap * (position.x - gameObj->position.x) / dist;
			position.y -= overlap * (position.y - gameObj->position.y) / dist;

			gameObj->position.x += overlap * (position.x - gameObj->position.x) / dist;
			gameObj->position.y += overlap * (position.y - gameObj->position.y) / dist;
		}
	}
	else { // Square

	}
}

template void GameObject::collisionUnit<Unit>(Unit *gameObj);
template void GameObject::collisionUnit<Field>(Field *gameObj);
template void GameObject::collisionUnit<Projectile>(Projectile *gameObj);

template <class T>
bool GameObject::detectCollision(T *gameObj) {
	if (gameObj->hitboxType == Circle) {
		if (((position.x - gameObj->position.x)*(position.x - gameObj->position.x) + (position.y - gameObj->position.y)*(position.y - gameObj->position.y)) 
			<= (radius + gameObj->radius)*(radius + gameObj->radius))
			return true;
	}
	else { // Square

	}

	return false;
}

template bool GameObject::detectCollision<Unit>(Unit *gameObj);
template bool GameObject::detectCollision<Player>(Player *gameObj);
template bool GameObject::detectCollision<Field>(Field *gameObj);
template bool GameObject::detectCollision<Projectile>(Projectile *gameObj);

GameObject::GameObject(GameObjectType objType, ObjectHitboxType hitbType)
	: objectType(objType), hitboxType(hitbType) {

}


GameObject::~GameObject() {

}
