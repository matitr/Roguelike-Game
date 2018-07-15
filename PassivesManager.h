#pragma once
#include <vector>
#include "Item.h"

enum class PassiveActivateOn;
class Passive;
class BuffsManager;

class PassivesManager {
	std::vector<Passive*> passives;

	BuffsManager* buffsManager;

	ItemPassives& unitStatisticsRef;
	ItemPassives unitStatsWithoutLimit;

	void limitStatistics();
public:
	void updateAllPassives();

	void equipItem(Item* item);
	void unequipItem(Item* item);

	void activatePassives(PassiveActivateOn activationType);
	void addPassive(Passive* passive);
	void removePassive(Passive* passive);

	void addStartingStat(StaticPassiveName::StaticPassiveName statName, float value);
	void setStartingStat(StaticPassiveName::StaticPassiveName statName, float value);

	PassivesManager(ItemPassives& unitStatistics);
	~PassivesManager();
};

