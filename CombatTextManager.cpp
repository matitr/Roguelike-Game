#include "CombatTextManager.h"
#include "CombatText.h"
#include "Unit.h"
#include "Settings.h"
#include "DataBase.h"
#include <sstream>
#include <iomanip>


void CombatTextManager::drawAndUpdate(SDL_Point* startRender) {
	std::vector<CombatText*>::iterator it_combatText = combatTexts.begin();

	while (it_combatText != combatTexts.end()) {
		(*it_combatText)->draw(startRender);
		it_combatText++;
	}

	// Update
	it_combatText = combatTexts.begin();
	while (it_combatText != combatTexts.end()) {
		if (!(*it_combatText)->update()) {
			delete (*it_combatText);
			it_combatText = combatTexts.erase(it_combatText);
		}
		else
			it_combatText++;
	}
}

void CombatTextManager::addDamage(float value, Unit* unit) {
	if (unit->getUnitType() == UnitType::Player) {
		if (!Settings::get()->showEnemyDamage)
			return;
	}
	else
		if (!Settings::get()->showDamage)
			return;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << roundf(value);
	
	CombatText* combatT = new CombatText(unit);
	combatT->setText(stream.str(), DataBase::fonts[FontPurpose::CombatText], DataBase::colors[TextColor::CombatTextDamage]);

	combatTexts.push_back(combatT);
}

void CombatTextManager::addHeal(float value, Unit* unit) {

}

void CombatTextManager::addDebuff(float value, Unit* unit) {

}

CombatTextManager::CombatTextManager() {

}


CombatTextManager::~CombatTextManager() {

}
