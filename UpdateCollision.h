#pragma once
#include "SDL.h"
#include <list>
#include <vector>
#include <unordered_map>

class Player;
class Unit;
class Field;
class AttackType;
struct SDL_Rect;
class InteractiveObject;
class Map;


class UpdateCollision {
	std::unordered_map <SDL_Scancode, float> interactiveObjDist;

public:
	void updateAllUnits(Player* player, std::list <Unit*>& monsters, std::vector<std::vector<Field*>>& map, SDL_Rect& fieldRect);
	static bool detectCollisionWithField(Unit* unit, Map* map);

	void projectilesWithUnits(std::list <AttackType*>& playerProjectiles, std::list <AttackType*>& monsterAttacks, Player* player, std::list <Unit*>& monsters);
	void projectilesWithWalls(std::list <AttackType*>& playerProjectiles, Map* map);

	void updateInteractiveObjects(std::vector <InteractiveObject*>& objects, std::unordered_map <SDL_Scancode, InteractiveObject*>& objectSelected, Player* player);

	UpdateCollision();
	~UpdateCollision();
};

