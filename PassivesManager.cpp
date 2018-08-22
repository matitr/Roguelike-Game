#include "PassivesManager.h"
#include "BuffsManager.h"
#include "Passive.h"
#include "DataBase.h"
#include "Unit.h"
#include <iostream>


#pragma region AttackPassivesManager
void AttackPassivesManager::activateHitEnemy(std::list <AttackType*>& attacks, BuffsManager* buffsManager, float hitDamage) {
	for (int i = 0; i < attackPassives.size(); i++) {
		if (attackPassives[i]->activateOn() == PassiveActivateOn::HitEnemy || attackPassives[i]->activateOn() == PassiveActivateOn::HitWallOrEnemy) {
			if (attackPassives[i]->activate(attacks, hitDamage) && attackPassives[i]->buffOnActivate()) {
				buffsManager->addBuffCopy(attackPassives[i]->buffOnActivate());
			}
		}
	}
}

void AttackPassivesManager::activateHitWall(std::list <AttackType*>& attacks) {
	for (int i = 0; i < attackPassives.size(); i++) {
		if (attackPassives[i]->activateOn() == PassiveActivateOn::HitWall || attackPassives[i]->activateOn() == PassiveActivateOn::HitWallOrEnemy) {
			if (attackPassives[i]->activate(attacks) && attackPassives[i]->buffOnActivate()) {
//				buffsManager->addBuffCopy(attackPassives[i]->buffOnActivate());
			}
		}
	}
}

void AttackPassivesManager::addAttackPassive(Passive* passive) {
	attackPassives.push_back(passive);
}

void AttackPassivesManager::removeAttackPassive(Passive* passive) {
	auto it_found = std::find(attackPassives.begin(), attackPassives.end(), passive);

	if (it_found != attackPassives.end())
		attackPassives.erase(it_found);
}

AttackPassivesManager::AttackPassivesManager(const AttackPassivesManager& attackPassivesM) {
	attackPassives.reserve(attackPassivesM.attackPassives.size());

	for (int i = 0; i < attackPassivesM.attackPassives.size(); i++)
		attackPassives.push_back(attackPassivesM.attackPassives[i]);
}
#pragma endregion


void PassivesManager::updateAllPassives(Unit* unitParent) {
	for (int i = 0; i < passives.size(); i++) {
		passives[i]->update();
	}
	buffsManager->updateAllBuffs(unitParent);
	limitStatistics();

//	static int o = 0;
//	o++;
//	if (!(o % 60)) {
//		for (int it_passive = 0; it_passive < unitStatsWithoutLimit.size(); it_passive++) {
//			std::cout << unitStatisticsRef[it_passive] <<",";
//		}
//		std::cout << std::endl;
//	}
}

void PassivesManager::equipItem(Item* item, Unit* unit) {
	// Add values
	for (int it_passive = 0; it_passive < item->getStaticPassives().size(); it_passive++) {
		unitStatsWithoutLimit[it_passive] += item->getStaticPassives()[it_passive];
	}
	if (item->getPassive()) {
		addPassive(item->getPassive());
		item->getPassive()->setParentUnit(unit);
	}
}

void PassivesManager::unequipItem(Item* item) {
	// Substract values
	for (int it_passive = 0; it_passive < item->getStaticPassives().size(); it_passive++) {
		unitStatsWithoutLimit[it_passive] -= item->getStaticPassives()[it_passive];
	}
	if (item->getPassive()) {
		removePassive(item->getPassive());
		item->getPassive()->removeParentUnit();
	}
}

void PassivesManager::limitStatistics() {
	for (int it_passive = 0; it_passive < unitStatsWithoutLimit.size(); it_passive++) {
		for (int i = 0; i < StaticPassiveName::enum_size; i++) {
			if (unitStatsWithoutLimit[i] < DataBase::passivesLimits[i].min)
				unitStatisticsRef[i] = DataBase::passivesLimits[i].min;
			else if (unitStatsWithoutLimit[i] > DataBase::passivesLimits[i].max)
				unitStatisticsRef[i] = DataBase::passivesLimits[i].max;
			else
				unitStatisticsRef[i] = unitStatsWithoutLimit[i];
		}
	}

	// Limit hp
	if (unitStatsWithoutLimit[StaticPassiveName::hp] > unitStatsWithoutLimit[StaticPassiveName::hpMax])
		unitStatsWithoutLimit[StaticPassiveName::hp] = unitStatsWithoutLimit[StaticPassiveName::hpMax];
}

void PassivesManager::activatePassives(PassiveActivateOn activationType, std::list <AttackType*>& attacks, float activationValue) {
	for (int i = 0; i < passives.size(); i++) {
		if (passives[i]->activateOn() == activationType) {
			if (passives[i]->activate(attacks) && passives[i]->buffOnActivate()) {
				buffsManager->addBuffCopy(passives[i]->buffOnActivate());
			}
		}
	}
}

void PassivesManager::addPassive(Passive* passive) {
	if (passive->activateOn() == PassiveActivateOn::HitEnemy || passive->activateOn() == PassiveActivateOn::HitWall || passive->activateOn() == PassiveActivateOn::HitWallOrEnemy)
		addAttackPassive(passive);
	else
		passives.push_back(passive);
}

void PassivesManager::removePassive(Passive* passive) {
	auto it_found = std::find(passives.begin(), passives.end(), passive);

	if (it_found != passives.end())
		passives.erase(it_found);

	buffsManager->removeBuffs(passive);

	removeAttackPassive(passive);
}

void PassivesManager::setStartingStat(StaticPassiveName::StaticPassiveName statName, float value) {
	unitStatsWithoutLimit[statName] = value;			
	
	if (unitStatsWithoutLimit[statName] < DataBase::passivesLimits[statName].min)
		unitStatisticsRef[statName] = DataBase::passivesLimits[statName].min;
	else if (unitStatsWithoutLimit[statName] > DataBase::passivesLimits[statName].max)
		unitStatisticsRef[statName] = DataBase::passivesLimits[statName].max;
	else
		unitStatisticsRef[statName] = unitStatsWithoutLimit[statName];
}

void PassivesManager::takeDamage(float& damage, DamageType damageType) {
	damage = damage * (1 + unitStatisticsRef[StaticPassiveName::damageTakenMult]);
	unitStatsWithoutLimit[StaticPassiveName::hp] -= damage;
}

PassivesManager::PassivesManager(ItemPassives& unitStatistics) : unitStatisticsRef(unitStatistics) {
	passives.reserve(4);
	buffsManager = new BuffsManager(unitStatsWithoutLimit);
}


PassivesManager::~PassivesManager() {
	delete buffsManager;
}
