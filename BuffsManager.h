#pragma once
#include <vector>
#include "Item.h"

class Buff;
class Passive;
class Unit;

class BuffsManager {
	std::vector<Buff*> buffs;

	ItemPassives& unitStats;
public:
	void addBuffCopy(Buff* buff);
	void removeBuffs(Passive* parentPassive);
	void updateAllBuffs(Unit* unit);

	BuffsManager(ItemPassives& statsWithoutLimit);
	~BuffsManager();
};

