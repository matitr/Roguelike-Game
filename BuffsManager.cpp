#include "BuffsManager.h"
#include "Buff.h"
#include "Passive.h"



void BuffsManager::addBuffCopy(Buff* buff) {
	std::vector<Buff*>::iterator it_found = buffs.begin();

	while (it_found != buffs.end()) {
		if ((*it_found)->getParentPassive() == buff->getParentPassive())
			break;

		it_found++;
	}

	if (it_found != buffs.end()) { // Found existing buff from the same passive
		// Reset cooldown / reset buff
		(*it_found)->deactivate(unitStats);
		*(*it_found) = *buff; // Copy buff
		(*it_found)->activate(unitStats);
		return;
	}
	else {
		buff = buff->getCopy();
		buffs.push_back(buff);
		buff->activate(unitStats);
	}
}

void BuffsManager::removeBuffs(Passive* parentPassive) {
	auto it = buffs.begin();
	while (it != buffs.end()) {
		if ((*it)->getParentPassive() == parentPassive) { // Remove buff
			(*it)->deactivate(unitStats);
			delete (*it);
			it = buffs.erase(it);
		}
		else
			it++;
	}
}

void BuffsManager::updateAllBuffs() {
	auto it = buffs.begin();
	auto it2 = buffs.begin();
	while (it != buffs.end()) {
		if (!(*it)->update()) { // Remove buff
			(*it)->deactivate(unitStats);
			delete (*it);
			it = buffs.erase(it);
		}
		else
			it++;
	}
}

BuffsManager::BuffsManager(ItemPassives& statsWithoutLimit) : unitStats(statsWithoutLimit) {
	buffs.reserve(4);
}


BuffsManager::~BuffsManager() {
	for (int i = 0; i < buffs.size(); i++)
		delete buffs[i];
}
