#include "AttackType.h"
#include "Game.h"
#include "Map.h"
#include <math.h>
#include <iostream>

void AttackType::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void AttackType::draw(SDL_Point* startRender) {
	dstRect.x = position.x - startRender->x - dstRect.w / 2;
	dstRect.y = (position.y - startRender->y) * HEIGHT_SCALE - dstRect.h / 2;

	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

void AttackType::setEnemyHitted(Unit* u) {
	enemyHitted = true;

	staticPassives[StaticPassiveName::pierceShots]--;
	unitsHitted.push_back(u);
}

bool AttackType::canBeHitted(Unit* u) {
	return std::find(unitsHitted.begin(), unitsHitted.end(), u) == unitsHitted.end();
}

void AttackType::delHittedUnitPointer(Unit* u) {
	std::vector<Unit*>::iterator findPos = std::find(unitsHitted.begin(), unitsHitted.end(), u);

	if (findPos != unitsHitted.end())
		unitsHitted.erase(findPos);
}

void AttackType::onWallHit() {

}

AttackType::AttackType(ItemPassives& passives)
	: GameObject(TextureManager::textureParameters[ProjectileT], Dynamic, Circle), staticPassives(passives) {

	damage = 1;
	enemyHitted = false;
	destroyObj = false;

	unitsHitted.reserve(50);
}


AttackType::~AttackType() {

}
