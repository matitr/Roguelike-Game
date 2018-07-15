#include "PassivesManager.h"
#include "BuffsManager.h"
#include "Passive.h"
#include "DataBase.h"
#include <iostream>


void PassivesManager::updateAllPassives() {
	for (int i = 0; i < passives.size(); i++) {
		passives[i]->update();
	}
	buffsManager->updateAllBuffs();
	limitStatistics();

	static int o = 0;
	o++;
	if (!(o % 60)) {
		for (int it_passive = 0; it_passive < unitStatsWithoutLimit.size(); it_passive++) {
			std::cout << unitStatisticsRef[it_passive] <<",";
		}
		std::cout << std::endl;
	}
}

void PassivesManager::equipItem(Item* item) {
	// Add values
	for (int it_passive = 0; it_passive < item->getStaticPassives().size(); it_passive++) {
		unitStatsWithoutLimit[it_passive] += item->getStaticPassives()[it_passive];
	}
	if (item->getPassive())
		addPassive(item->getPassive());
}

void PassivesManager::unequipItem(Item* item) {
	// Substract values
	for (int it_passive = 0; it_passive < item->getStaticPassives().size(); it_passive++) {
		unitStatsWithoutLimit[it_passive] -= item->getStaticPassives()[it_passive];
	}
	if (item->getPassive())
		removePassive(item->getPassive());
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
}

void PassivesManager::activatePassives(PassiveActivateOn activationType) {
	for (int i = 0; i < passives.size(); i++) {
		if (passives[i]->activateOn() == activationType) {
			if (passives[i]->activate() && passives[i]->buffOnActivate()) {
				buffsManager->addBuffCopy(passives[i]->buffOnActivate());
			}
		}
	}
}

void PassivesManager::addPassive(Passive* passive) {
	passives.push_back(passive);
}

void PassivesManager::removePassive(Passive* passive) {
	auto it_found = std::find(passives.begin(), passives.end(), passive);

	if (it_found != passives.end())
		passives.erase(it_found);

	buffsManager->removeBuffs(passive);
}

void PassivesManager::addStartingStat(StaticPassiveName::StaticPassiveName statName, float value) {
	unitStatsWithoutLimit[statName] += value;
}

void PassivesManager::setStartingStat(StaticPassiveName::StaticPassiveName statName, float value) {
	unitStatsWithoutLimit[statName] = value;
}

PassivesManager::PassivesManager(ItemPassives& unitStatistics) : unitStatisticsRef(unitStatistics) {
	passives.reserve(4);
	buffsManager = new BuffsManager(unitStatsWithoutLimit);
}


PassivesManager::~PassivesManager() {
	delete buffsManager;
}
