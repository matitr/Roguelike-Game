#include "Unit.h"
#include "Game.h"
#include "UnitAction.h"
#include "Attacks.h"
#include <math.h>

bool Unit::update(std::list <AttackType*>& monsterAttacks, Map* map) {
	if (hp <= 0)
		return false;

	actionsManager.onClosestObj(closestEnemy, closestEnemyDist);
	actionsManager.updateAction();

	SDL_Point p = { map->getPlayer()->getPositionX(), map->getPlayer()->getPositionY() };
	actionsManager.makeAttack(this, monsterAttacks, &p);
	actionsManager.makeMove(this);

	if (!(!velocity.y && !velocity.x)) {
		double dir = atan2(velocity.y, velocity.x);
		position.x += cos(dir) * speed;
		position.y += sin(dir) * speed;
	}
	return true;
}

void Unit::draw(SDL_Point* startRender) {
	dstRect.x = position.x - startRender->x - positionShiftX;
	dstRect.y = (position.y - startRender->y) * HEIGHT_SCALE - positionShiftY;

	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);	

	SDL_Rect r;
	r.h = 4;
	r.w = radius * 2;
	r.x = position.x - positionShiftX - startRender->x;
	r.y = position.y - startRender->y;
	SDL_SetRenderDrawColor(Game::renderer, rand() % 225, 0, 102, 255);
	renderCircle(position.x - startRender->x, (position.y - startRender->y) * HEIGHT_SCALE, radius);
	//	SDL_RenderFillRect(Game::renderer, &r);
}

void Unit::setClosestEnemy(Unit* u, double dist) {
	closestEnemy = u;
	closestEnemyDist = dist;
}

Unit::Unit(TextureInfo& txtInfo) : GameObject(txtInfo, Dynamic, Circle), actionsManager(srcRect, velocity, position) {
	speed = 3;
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