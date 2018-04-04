#include "UpdateCollision.h"
#include "Player.h"
#include "Field.h"
#include "Projectile.h"
#include "Player.h"
#include "Field.h"
#include "GameObject.h"
#include "SDL.h"


void UpdateCollision::updateAllUnits(Player* player, std::list <Unit*>& monsters, std::vector<std::vector<Field*>>& map, SDL_Rect& fieldRect) {
	std::list <Unit*>::iterator it_mon;
	std::list <Unit*>::iterator it_mon_second;

	player->collisionUnitFields(map, fieldRect);
	for (it_mon = monsters.begin(); it_mon != monsters.end(); it_mon++) {
		player->collisionUnit(*it_mon);

		(*it_mon)->collisionUnitFields(map, fieldRect);

		for (it_mon_second = monsters.begin(); it_mon_second != monsters.end(); it_mon_second++) {
			if (it_mon != it_mon_second)
				(*it_mon)->collisionUnit(*it_mon_second);

		}
	}
}

void UpdateCollision::updateAllProjectiles(std::list <Projectile*>& playerProjectiles, std::list <Projectile*>& monsterAttacks, Player* player, std::list <Unit*>& monsters) {
	std::list <Projectile*>::iterator it_projectile;
	std::list <Unit*>::iterator it_monster;
	
	for (it_projectile = monsterAttacks.begin(); it_projectile != monsterAttacks.end(); it_projectile++) {
		if ((*it_projectile)->detectCollision(player)) {
			(*it_projectile)->setEnemyHitted(true);
			player->takeDamage((*it_projectile)->getDamage());
		}
	}

	for (it_projectile = playerProjectiles.begin(); it_projectile != playerProjectiles.end(); it_projectile++) {
		for (it_monster = monsters.begin(); it_monster != monsters.end(); it_monster++) {
			if ((*it_projectile)->detectCollision(*it_monster)) {
				(*it_projectile)->setEnemyHitted(true);
				(*it_monster)->takeDamage((*it_projectile)->getDamage());
			}
		}
	}

}

UpdateCollision::UpdateCollision() {

}


UpdateCollision::~UpdateCollision() {

}
