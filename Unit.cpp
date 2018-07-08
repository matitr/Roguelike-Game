#include "Unit.h"
#include "Game.h"
#include "UnitAction.h"
#include "Attacks.h"
#include "Player.h"
#include <math.h>

bool Unit::update(std::list <AttackType*>& monsterAttacks, Map* map) {
	if (hp <= 0)
		return false;

	actionsManager.onClosestObj(closestEnemy, closestEnemyDist);
	actionsManager.updateAction();

	SDL_Point p = { (int)map->getPlayer()->getPositionX(), (int)map->getPlayer()->getPositionY() };
	actionsManager.makeAttack(this, monsterAttacks, &p);
	actionsManager.makeMove(this);

	if (!(!velocity.y && !velocity.x)) {
		double dir = atan2(velocity.y, velocity.x);
		double speedMultiplier = staticPassives[StaticPassiveName::unitSpeed] ? 1 + staticPassives[StaticPassiveName::unitSpeed] / 100 : 1;
		if (maxSpeed == -1 || (speed * speedMultiplier) <= maxSpeed) {
			position.x += cos(dir) * speed * speedMultiplier;
			position.y += sin(dir) * speed * speedMultiplier;
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

Unit::Unit(TextureInfo& txtInfo) : GameObject(txtInfo, Dynamic, Circle), actionsManager(srcRect, velocity, position) {
	speed = 3;
	baseSpeed = 3;
	hp = 100;

	velocity.x = 0;
	velocity.y = 0;
}


Unit::~Unit() {

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