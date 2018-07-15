#include "Passive.h"
#include "Buff.h"
#include <iostream>

Passive::Passive(PassiveActivateOn activationOn) : passActivateOn(activationOn) {

}


Passive::~Passive() {
	if (buffFromPassive)
		delete buffFromPassive;
}


#pragma region BuffMoveSpeed

bool PassiveOnRoomClearHeal::activate() {
	return true;
}

#pragma endregion


#pragma region BuffMoveSpeed

bool PassiveOnEnemyKillMoveSpeed::activate() {
	return true;
}

PassiveOnEnemyKillMoveSpeed::PassiveOnEnemyKillMoveSpeed() : Passive(PassiveActivateOn::EnemyKill) {
	buffFromPassive = new BuffMoveSpeed(this, 120, 1);

	passiveDescription = "Increases movement speed by 100% after killing an enemy for 2 seconds.";
}

#pragma endregion

















Passive* Passive::createPassive(PassiveName name) {
	if (name == PassiveName::None)
		return nullptr;
	else if (name == PassiveName::OnRoomClearHeal)
		return new PassiveOnRoomClearHeal();
	else if (name == PassiveName::OnEnemyKillMoveSpeed)
		return new PassiveOnEnemyKillMoveSpeed();

	return nullptr;
}
