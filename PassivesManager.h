#pragma once
#include <vector>
#include "Item.h"

enum class PassiveActivateOn;
class Passive;
class BuffsManager;
class AttackType;


class AttackPassivesManager {
	std::vector<Passive*> attackPassives;

public:
	void activateHitEnemy(std::list <AttackType*>& attacks, BuffsManager* hittedBuffsManager);
	void activateHitWall(std::list <AttackType*>& attacks, BuffsManager* buffsManager);

	void addAttackPassive(Passive* passive);
	void removeAttackPassive(Passive* passive);

	AttackPassivesManager() = default;
	~AttackPassivesManager() = default;
};


class PassivesManager : public AttackPassivesManager {
	std::vector<Passive*> passives;

	BuffsManager* buffsManager;

	ItemPassives& unitStatisticsRef;
	ItemPassives unitStatsWithoutLimit;

	void limitStatistics();
	void addPassive(Passive* passive);
	void removePassive(Passive* passive);
public:
	ItemPassives& getUnitStatistics() { return unitStatisticsRef; }
	BuffsManager* getBuffsManager() { return buffsManager; }

	void updateAllPassives();

	void equipItem(Item* item);
	void unequipItem(Item* item);

	void activatePassives(PassiveActivateOn activationType, std::list <AttackType*>& attacks, SDL_Point* attackPoint);

	void addStartingStat(StaticPassiveName::StaticPassiveName statName, float value);
	void setStartingStat(StaticPassiveName::StaticPassiveName statName, float value);

	PassivesManager(ItemPassives& unitStatistics);
	~PassivesManager();
};

