#include "Passive.h"
#include "Buff.h"
#include "AttackType.h"
#include <iostream>

Passive::Passive(PassiveActivateOn activationOn) : passActivateOn(activationOn) {

}


Passive::~Passive() {
	if (buffFromPassive)
		delete buffFromPassive;
}


#pragma region PassiveOnRoomClearHeal

#pragma endregion


#pragma region PassiveOnEnemyKillMoveSpeed
PassiveOnEnemyKillMoveSpeed::PassiveOnEnemyKillMoveSpeed() : Passive(PassiveActivateOn::EnemyKill) {
	buffFromPassive = new BuffMoveSpeed(this, 120, 1);

	passiveDescription = "Increases movement speed by 100% after killing an enemy for 2 seconds.";
}

#pragma endregion


#pragma region PassiveOnHitSlowMoveSpeed
PassiveOnHitSlowMoveSpeed::PassiveOnHitSlowMoveSpeed() : Passive(PassiveActivateOn::HitEnemy) {
	buffFromPassive = new BuffMoveSpeed(this, 30, -0.5);

	passiveDescription = "On hit slow enemy for 50% for 0.5 seconds.";
}

#pragma endregion

















Passive* Passive::createPassive(PassiveName name) {
	if (name == PassiveName::None)
		return nullptr;
	else if (name == PassiveName::OnRoomClearHeal)
		return new PassiveOnRoomClearHeal();
	else if (name == PassiveName::OnEnemyKillMoveSpeed)
		return new PassiveOnEnemyKillMoveSpeed();
	else if (name == PassiveName::OnHitSlowMoveSpeed)
		return new PassiveOnHitSlowMoveSpeed();

	return nullptr;
}
