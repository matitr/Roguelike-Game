#pragma once
#include "SDL.h"
#include <list>
#include <vector>
#include <unordered_map>

class Player;
class Unit;
class Field;
class Projectile;
class SDL_Rect;
class InteractiveObject;
class Map;


class UpdateCollision {
	std::unordered_map <SDL_Scancode, float> interactiveObjDist;

public:
	void updateAllUnits(Player* player, std::list <Unit*>& monsters, std::vector<std::vector<Field*>>& map, SDL_Rect& fieldRect);
	void projectilesWithUnits(std::list <Projectile*>& playerProjectiles, std::list <Projectile*>& monsterAttacks, Player* player, std::list <Unit*>& monsters);
	void projectilesWithWalls(std::list <Projectile*>& playerProjectiles, Map* map);

	void updateInteractiveObjects(std::vector <InteractiveObject*>& objects, std::unordered_map <SDL_Scancode, InteractiveObject*>& objectSelected, Player* player);

	UpdateCollision();
	~UpdateCollision();
};

