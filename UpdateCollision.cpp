#include "UpdateCollision.h"
#include "Player.h"
#include "Field.h"
#include "AttackType.h"
#include "Player.h"
#include "Field.h"
#include "GameObject.h"
#include "SDL.h"
#include "InteractiveObject.h"


void UpdateCollision::updateAllUnits(Player* player, std::list <Unit*>& monsters, Map* map, SDL_Rect& fieldRect) {
	std::list <Unit*>::iterator it_mon;
	std::list <Unit*>::iterator it_mon_second;

	if (player->collisionUnitFields(map, fieldRect))
		player->setHittedWall();

	for (it_mon = monsters.begin(); it_mon != monsters.end(); it_mon++) {
		if ((*it_mon)->alive()) {
			if (player->collisionUnit(*it_mon)) {
				player->setCollisionWithUnit();
				(*it_mon)->setCollisionWithUnit();
			}

			// Monster player dist. Closest unit to it_mon is player
			double dist = (*it_mon)->distanceEdges(player);
			(*it_mon)->setClosestEnemy(player, dist);

			if ((*it_mon)->collisionUnitFields(map, fieldRect))
				(*it_mon)->setHittedWall();

			for (it_mon_second = monsters.begin(); it_mon_second != monsters.end(); it_mon_second++) {
				if (it_mon != it_mon_second && (*it_mon_second)->alive() && (*it_mon)->collisionUnit(*it_mon_second)) {
					(*it_mon)->setCollisionWithUnit();
					(*it_mon_second)->setCollisionWithUnit();
				}
			}
		}

	}
}


bool UpdateCollision::detectCollisionWithField(Unit* unit, Map* map) {
	for (int y = (int)(unit->getPositionY() - unit->getRadius()) / map->fieldRect.h; y <= ((int)unit->getPositionY() - unit->getRadius()) / map->fieldRect.h; y++) {
		for (int x = ((int)unit->getPositionX() - unit->getRadius()) / map->fieldRect.w; x <= ((int)unit->getPositionX() - unit->getRadius()) / map->fieldRect.w; x++) {
			if (map->getField(x, y)->type() != FieldType::Floor && unit->detectCollision(map->getField(x, y)))
				return true;

			if (!map->getField(x, y)->getCollisionObj().empty())
				return true;
		}
	}

	return false;
}

void UpdateCollision::projectilesWithUnits(std::list <AttackType*>& playerProjectiles, std::list <AttackType*>& monsterAttacks, Player* player, std::list <Unit*>& monsters) {
	std::list <AttackType*>::iterator it_projectile;
	std::list <Unit*>::iterator it_monster;
	
	for (it_projectile = monsterAttacks.begin(); it_projectile != monsterAttacks.end(); it_projectile++) {
		if ((*it_projectile)->collision(player) && (*it_projectile)->canBeHitted(player)) { // Player hitted  

			(*it_projectile)->setEnemyHitted(player);
			float attackDamage = (*it_projectile)->getDamage();
			player->getPassivesManager()->activatePassives(PassiveActivateOn::TakeDamage, playerProjectiles, attackDamage);
			player->takeDamage(attackDamage);

			// Activate passives
			(*it_projectile)->getAttackPassivesManager().activateHitEnemy(monsterAttacks, player->getPassivesManager()->getBuffsManager(), attackDamage);
		}
	}

	for (it_projectile = playerProjectiles.begin(); it_projectile != playerProjectiles.end(); it_projectile++) {
		for (it_monster = monsters.begin(); it_monster != monsters.end(); it_monster++) {
			if ((*it_monster)->alive() && (*it_projectile)->collision(*it_monster) && (*it_projectile)->canBeHitted(*it_monster)) { // Monster hitted

				(*it_projectile)->setEnemyHitted(*it_monster);
				float attackDamage = (*it_projectile)->getDamage();
				(*it_monster)->getPassivesManager()->activatePassives(PassiveActivateOn::TakeDamage, playerProjectiles, attackDamage);
				(*it_monster)->takeDamage(attackDamage);

				// Activate passives
				(*it_projectile)->getAttackPassivesManager().activateHitEnemy(playerProjectiles, (*it_monster)->getPassivesManager()->getBuffsManager(), attackDamage);
			}
		}
	}

}

void UpdateCollision::projectilesWithWalls(std::list <AttackType*>& projectiles, Map* map) {
	std::list <AttackType*>::iterator it_proj = projectiles.begin();

	while (it_proj != projectiles.end()) {
		int y = ((int)(*it_proj)->getPositionY() - (*it_proj)->getRadiusY()) / map->fieldRect.h;
		for (y; y <= ((*it_proj)->getPositionY() + (*it_proj)->getRadiusY()) / map->fieldRect.h; y++) {
			int x = ((int)(*it_proj)->getPositionX() - (*it_proj)->getRadius()) / map->fieldRect.w;
			for (x; x <= ((*it_proj)->getPositionX() + (*it_proj)->getRadius()) / map->fieldRect.w; x++) {

				if (!map->getField(x, y)->ground() && (*it_proj)->detectCollision(map->getField(x, y))) {
					(*it_proj)->onWallHit();
					(*it_proj)->getAttackPassivesManager().activateHitWall(projectiles);
				}
				else {
					std::vector<GameObject*>::iterator it_collisionObj = map->getField(x, y)->getCollisionObj().begin();
					for (it_collisionObj; it_collisionObj < map->getField(x, y)->getCollisionObj().end(); it_collisionObj++) {
						if ((*it_proj)->detectCollision(*it_collisionObj)) {
							(*it_proj)->onWallHit();
							(*it_proj)->getAttackPassivesManager().activateHitWall(projectiles);
						}
					}
				}
			}
		}
		it_proj++;
	}
}

void UpdateCollision::updateInteractiveObjects(std::vector <InteractiveObject*>& objects, std::unordered_map <SDL_Scancode, InteractiveObject*>& objectSelected, Player* player) {
	std::unordered_map <SDL_Scancode, InteractiveObject*>::iterator it_objSelected;
	float dist;

	for (it_objSelected = objectSelected.begin(); it_objSelected != objectSelected.end(); it_objSelected++) {
		interactiveObjDist[(*it_objSelected).first] = NO_COLLISION;
		objectSelected[(*it_objSelected).first] = nullptr;
	}

	for (int i = 0; i < objects.size(); i++) {
		dist = player->distanceEdges(objects[i]);
		if (dist < 20) {
			objects[i]->onPlayerTouch();

			if (objects[i]->canInteract() && objects[i]->interactOnKey() && interactiveObjDist[objects[i]->interactKey()] > dist) {
				interactiveObjDist[objects[i]->interactKey()] = dist;
				objectSelected[objects[i]->interactKey()] = objects[i];
			}
		}
	}
}

UpdateCollision::UpdateCollision() {

}


UpdateCollision::~UpdateCollision() {

}
