#include "AttackType.h"
#include "Game.h"
#include "Map.h"
#include <math.h>
#include <iostream>


void AttackType::draw(SDL_Point* startRender) {
	dstRect.x = int(position.x - startRender->x - dstRect.w / 2.0);
	dstRect.y = int((position.y - startRender->y) * HEIGHT_SCALE - dstRect.h / 2.0);

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

AttackType::AttackType(PassivesManager* passivesManager, double attackDamage)
	: GameObject(TextureManager::textureParameters[SingleTexture::ProjectileT], Dynamic, Circle), staticPassives(passivesManager->getUnitStatistics())
, attackPassivesManager(*passivesManager) {

	damage = attackDamage;
	enemyHitted = false;
	destroyObj = false;

	unitsHitted.reserve(10);
}


AttackType::~AttackType() {

}
