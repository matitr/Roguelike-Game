#include "Unit.h"
#include "Game.h"
#include "UnitAction.h"
#include "Attacks.h"
#include "Player.h"
#include "PassivesManager.h"
#include "BuffsManager.h"
#include "Passive.h"
#include "HealthBar.h"
#include "CombatTextManager.h"
#include <math.h>

bool Unit::update(std::list <AttackType*>& monsterAttacks, Map* map) {
	attackPos.x = (int)closestEnemy->getPositionX();
	attackPos.y = (int)closestEnemy->getPositionY();

	if (staticPassives[StaticPassiveName::hp] <= 0) {
		passivesManager->activatePassives(PassiveActivateOn::Death, monsterAttacks);
	}

	if (staticPassives[StaticPassiveName::hp] <= 0) {
		isAlive = false;
		return actionsManager.updateDeathAction(this, monsterAttacks, &attackPos);
	}

	actionsManager.updateMove();
	actionsManager.onClosestObj(map, closestEnemy, closestEnemyDist, position);
	actionsManager.updateAction(velocity);
	passivesManager->activatePassives(PassiveActivateOn::Passive, monsterAttacks);
	passivesManager->updateAllPassives(this);

	speed = staticPassives[StaticPassiveName::unitSpeed];

	actionsManager.makeAttack(this, monsterAttacks, &attackPos);
	actionsManager.makeMove(this);

	unitDetectedCollisionUnit = false;
	unitDetectedCollisionWall = false;

	if (!(!velocity.y && !velocity.x)) {
		double dir = atan2(velocity.y, velocity.x);
		if (maxSpeed == -1 || (speed * (1 + staticPassives[StaticPassiveName::unitSpeedMult])) <= maxSpeed) {
			position.x += cos(dir) * speed * (1 + staticPassives[StaticPassiveName::unitSpeedMult]);
			position.y += sin(dir) * speed * (1 + staticPassives[StaticPassiveName::unitSpeedMult]);
		}
		else {
			position.x += cos(dir) * maxSpeed;
			position.y += sin(dir) * maxSpeed;
		}
	}
	maxSpeed = -1;

	return true;
}

void Unit::draw(SDL_Point* startRender) {
	dstRect.x = int(position.x - startRender->x) - positionShiftX;
	dstRect.y = int((position.y - startRender->y) * HEIGHT_SCALE) - positionShiftY;

	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);	
	healthBar->draw();

	// Draw hitbox
//	SDL_Rect r;
//	r.h = 4;
//	r.w = radius * 2;
//	r.x = (int)position.x - positionShiftX - startRender->x;
//	r.y = (int)position.y - startRender->y;
//	SDL_SetRenderDrawColor(Game::renderer, rand() % 225, 0, 102, 255);
//	renderCircle((int)position.x - startRender->x, ((int)position.y - startRender->y) * HEIGHT_SCALE, radius);
}

void Unit::setClosestEnemy(Unit* u, double dist) {
	closestEnemy = u;
	closestEnemyDist = dist;
}

void Unit::takeDamage(float& damage, DamageType damageType) {
	passivesManager->takeDamage(damage, damageType);

	if (damage < 0)
		damageType = DamageType::Heal;

	CombatTextManager::get().addDamage(damage, damageType, this);
}

Unit::Unit(TextureInfo& txtInfo, UnitType uType) 
	: GameObject(txtInfo, Dynamic, Circle), actionsManager(srcRect, staticPassives[StaticPassiveName::unitSpeedMult], staticPassives[StaticPassiveName::attackSpeedMult], this), unitType(uType) {
	passivesManager = new PassivesManager(staticPassives);
	healthBar = new HealthBar(dstRect, staticPassives[StaticPassiveName::hp], staticPassives[StaticPassiveName::hpMax], unitType);
	healthBar->draw();
	passivesManager->setStartingStat(StaticPassiveName::damage, 1);
	passivesManager->setStartingStat(StaticPassiveName::hp, 100);
	passivesManager->setStartingStat(StaticPassiveName::hpMax, 100);
	passivesManager->setStartingStat(StaticPassiveName::unitSpeed, 3);

	velocity.x = 0;
	velocity.y = 0;
}


Unit::~Unit() {
	delete passivesManager;
	delete healthBar;
}


void Unit::renderCircle(int _x, int _y, int radius) {
	int x = radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int err = tx - (radius << 1);
								 
	while (x >= y) {
		SDL_RenderDrawPoint(Game::renderer, _x + x, _y - y);
		SDL_RenderDrawPoint(Game::renderer, _x + x, _y + y);
		SDL_RenderDrawPoint(Game::renderer, _x - x, _y - y);
		SDL_RenderDrawPoint(Game::renderer, _x - x, _y + y);
		SDL_RenderDrawPoint(Game::renderer, _x + y, _y - x);
		SDL_RenderDrawPoint(Game::renderer, _x + y, _y + x);
		SDL_RenderDrawPoint(Game::renderer, _x - y, _y - x);
		SDL_RenderDrawPoint(Game::renderer, _x - y, _y + x);

		if (err <= 0){
			y++;
			err += ty;
			ty += 2;
		}
		else if (err > 0) {
			x--;
			tx += 2;
			err += tx - (radius << 1);
		}
	}
}