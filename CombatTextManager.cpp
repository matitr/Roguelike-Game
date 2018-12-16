#include "CombatTextManager.h"
#include "CombatText.h"
#include "Unit.h"
#include "Settings.h"
#include "DataBase.h"
#include "PassivesManager.h"
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

void CombatTextManager::addDamage(float value, DamageType damageType, Unit* unit) {
	if (unit->getUnitType() == UnitType::Player) {
		if (!Settings::get()->getSettingDisplay(SettingsDisplay::ShowEnemyDamage))
			return;
	}
	else
		if (!Settings::get()->getSettingDisplay(SettingsDisplay::ShowDamage))
			return;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << (value);
	
	CombatText* combatT = new CombatText(unit);

	SDL_Color color;
	if (damageType == DamageType::Physical)
		color = DataBase::colors[TextColor::CombatTextDamage];
	else if (damageType == DamageType::Fire)
		color = DataBase::colors[TextColor::CombatTextFireDmg];
	else if (damageType == DamageType::Heal)
		color = DataBase::colors[TextColor::CombatTextHeal];

	combatT->setText(stream.str(), DataBase::fonts[FontPurpose::CombatTextDmg], color);

	combatTexts.push_back(combatT);
}

void CombatTextManager::addDebuff(float value, Unit* unit) {

}

CombatTextManager::CombatTextManager() {

}


CombatTextManager::~CombatTextManager() {

}
