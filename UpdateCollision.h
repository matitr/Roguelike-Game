#pragma once
#include <list>
#include <vector>

class Player;
class Unit;
class Field;
class Projectile;
class SDL_Rect;


class UpdateCollision {
public:
	static void updateAllUnits(Player* player, std::list <Unit*>& monsters, std::vector<std::vector<Field*>>& map, SDL_Rect& fieldRect);
	static void updateAllProjectiles(std::list <Projectile*>& playerProjectiles, std::list <Projectile*>& monsterAttacks, Player* player, std::list <Unit*>& monsters);

	UpdateCollision();
	~UpdateCollision();
};

