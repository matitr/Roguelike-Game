#include "Buff.h"
#include "Unit.h"


bool Buff::update(Unit* unit) {
	if (duration < 0) // Duration is infinity
		return true;

	if (!duration)
		return false;

	duration--;
	return true;
}

Buff::Buff(Passive* parent, int buffDuration) : parentPassive(parent), duration(buffDuration) {

}


Buff::~Buff() {

}


#pragma region BuffSingleHeal

bool BuffSingleHeal::update(Unit* unit) {
	unit->takeDamage(healValue, DamageType::Heal);

	return Buff::update(unit);
}

#pragma endregion


#pragma region BuffHealOvertime

bool BuffHealOvertime::update(Unit* unit) {
	if (!(duration % 30)) {
		unit->takeDamage(healValue, DamageType::Heal);
	}

	return Buff::update(unit);
}

#pragma endregion


#pragma region BuffMoveSpeed


void BuffMoveSpeed::activate(ItemPassives& unitStats) {
	unitStats[StaticPassiveName::unitSpeedMult] += moveSpeedValue;
}

void BuffMoveSpeed::deactivate(ItemPassives& unitStats) {
	unitStats[StaticPassiveName::unitSpeedMult] -= moveSpeedValue;
}

#pragma endregion


#pragma region BuffBurn

bool BuffBurn::update(Unit* unit) {
	if (!(duration % 30)) {
		unit->takeDamage(dmgPerTick, DamageType::Fire);
	}

	return Buff::update(unit);
}

#pragma endregion


#pragma region BuffDamageMult

void BuffDamageMult::activate(ItemPassives& unitStats) {
	unitStats[StaticPassiveName::damageMult] += damageMult;
}

void BuffDamageMult::deactivate(ItemPassives& unitStats) {
	unitStats[StaticPassiveName::damageMult] -= damageMult;
}

#pragma endregion


#pragma region BuffDamageTakenMult

void BuffDamageTakenMult::activate(ItemPassives& unitStats) {
	unitStats[StaticPassiveName::damageTakenMult] += damageTakenMult;
}

void BuffDamageTakenMult::deactivate(ItemPassives& unitStats) {
	unitStats[StaticPassiveName::damageTakenMult] -= damageTakenMult;
}

#pragma endregion






