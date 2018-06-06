#include "UpdateCollision.h"
#include "Player.h"
#include "Field.h"
#include "AttackType.h"
#include "Player.h"
#include "Field.h"
#include "GameObject.h"
#include "SDL.h"
#include "InteractiveObject.h"


void UpdateCollision::updateAllUnits(Player* player, std::list <Unit*>& monsters, std::vector<std::vector<Field*>>& map, SDL_Rect& fieldRect) {
	std::list <Unit*>::iterator it_mon;
	std::list <Unit*>::iterator it_mon_second;

	player->collisionUnitFields(map, fieldRect);
	for (it_mon = monsters.begin(); it_mon != monsters.end(); it_mon++) {
		player->collisionUnit(*it_mon);

		// Monster player dist
		double dist = (*it_mon)->distanceEdges(player);
		(*it_mon)->setClosestEnemy(player, dist);

		(*it_mon)->collisionUnitFields(map, fieldRect);

		for (it_mon_second = monsters.begin(); it_mon_second != monsters.end(); it_mon_second++) {
			if (it_mon != it_mon_second)
				(*it_mon)->collisionUnit(*it_mon_second);

		}
	}
}

bool UpdateCollision::detectCollisionWithField(Unit* unit, Map* map) {
	for (int x = (unit->getPositionX() - unit->getRadius()) / map->fieldRect.w; x <= (unit->getPositionX() - unit->getRadius()) / map->fieldRect.w; x++) {
		for (int y = (unit->getPositionY() - unit->getRadius()) / map->fieldRect.h; y <= (unit->getPositionY() - unit->getRadius()) / map->fieldRect.h; y++) {
			if (map->map[x][y]->type() != Floor && unit->detectCollision(map->map[x][y]))
				return true;

			//for (auto it_collisionObj = map->map[x][y]->getCollisionObj().begin(); it_collisionObj != map->map[x][y]->getCollisionObj().end(); it_collisionObj++)
			//	if (unit->detectCollision(*it_collisionObj))
			//		return true;
			if (!map->map[x][y]->getCollisionObj().empty())
				return true;
		}
	}

	return false;
}

void UpdateCollision::projectilesWithUnits(std::list <AttackType*>& playerProjectiles, std::list <AttackType*>& monsterAttacks, Player* player, std::list <Unit*>& monsters) {
	std::list <AttackType*>::iterator it_projectile;
	std::list <Unit*>::iterator it_monster;
	
	for (it_projectile = monsterAttacks.begin(); it_projectile != monsterAttacks.end(); it_projectile++) {
		if ((*it_projectile)->collision(player) && (*it_projectile)->canBeHitted(player)) {
			(*it_projectile)->setEnemyHitted(player);
			player->takeDamage((*it_projectile)->getDamage());
		}
	}

	for (it_projectile = playerProjectiles.begin(); it_projectile != playerProjectiles.end(); it_projectile++) {
		for (it_monster = monsters.begin(); it_monster != monsters.end(); it_monster++) {
			if ((*it_projectile)->collision(*it_monster) && (*it_projectile)->canBeHitted(*it_monster)) {
				(*it_projectile)->setEnemyHitted(*it_monster);
				(*it_monster)->takeDamage((*it_projectile)->getDamage());
			}
		}
	}

}

void UpdateCollision::projectilesWithWalls(std::list <AttackType*>& playerProjectiles, Map* map) {
	std::list <AttackType*>::iterator it_proj = playerProjectiles.begin();

	while (it_proj != playerProjectiles.end()) {
		int x = ((*it_proj)->getPositionX() - (*it_proj)->getRadius()) / map->fieldRect.w;
		for (x; x <= ((*it_proj)->getPositionX() + (*it_proj)->getRadius()) / map->fieldRect.w; x++) {
			int y = ((*it_proj)->getPositionY() - (*it_proj)->getRadiusY()) / map->fieldRect.h;
			for (y; y <= ((*it_proj)->getPositionY() + (*it_proj)->getRadiusY()) / map->fieldRect.h; y++) {

				if (!map->map[x][y]->ground())
					(*it_proj)->onWallHit();
				else {
					std::vector<GameObject*>::iterator it_collisionObj = map->map[x][y]->getCollisionObj().begin();
					for (it_collisionObj; it_collisionObj < map->map[x][y]->getCollisionObj().end(); it_collisionObj++) {
						if ((*it_proj)->detectCollision(*it_collisionObj))
							(*it_proj)->onWallHit();
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
