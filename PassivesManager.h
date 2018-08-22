#pragma once
#include <vector>
#include "Item.h"

enum class PassiveActivateOn;
class Passive;
class BuffsManager;
class AttackType;
class Unit;

enum class DamageType { Physical, Fire, Heal };

class AttackPassivesManager { // Object of this class is in attack
	std::vector<Passive*> attackPassives;

public:
	void activateHitEnemy(std::list <AttackType*>& attacks, BuffsManager* hittedBuffsManager, float hitDamage);
	void activateHitWall(std::list <AttackType*>& attacks);

	void addAttackPassive(Passive* passive);
	void removeAttackPassive(Passive* passive);

	AttackPassivesManager() = default;
	AttackPassivesManager(const AttackPassivesManager& attackPassivesM);
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

	void updateAllPassives(Unit* unitParent);

	void equipItem(Item* item, Unit* unit);
	void unequipItem(Item* item);

	void activatePassives(PassiveActivateOn activationType, std::list <AttackType*>& attacks, float activationValue = 0);

	void setStartingStat(StaticPassiveName::StaticPassiveName statName, float value);

	void takeDamage(float& damage, DamageType damageType = DamageType::Physical);

	PassivesManager(ItemPassives& unitStatistics);
	~PassivesManager();
};

