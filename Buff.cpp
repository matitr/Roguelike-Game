#include "Buff.h"


bool Buff::update() {
	if (duration < 0)
		return true;

	if (!duration)
		return false;

	duration--;
}

Buff::Buff(Passive* parent, int buffDuration) : parentPassive(parent), duration(buffDuration) {

}


Buff::~Buff() {

}


#pragma region BuffHeal


void BuffHeal::activate(ItemPassives& unitStats) {

}

void BuffHeal::deactivate(ItemPassives& unitStats) {

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






