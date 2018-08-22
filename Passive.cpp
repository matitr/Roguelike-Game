#include "Passive.h"
#include "Buff.h"
#include "AttackType.h"
#include "Unit.h"
#include <iostream>

Passive::Passive(PassiveActivateOn activationOn) : passActivateOn(activationOn) {

}


Passive::~Passive() {
	if (buffFromPassive)
		delete buffFromPassive;
}

#pragma region PassiveActivateOn::Passive



#pragma endregion

#pragma region PassiveActivateOn::CreateAttack



#pragma endregion

#pragma region PassiveActivateOn::TakeDamage



#pragma endregion

#pragma region PassiveActivateOn::EnemyKill

PassiveOnEnemyKillMoveSpeed::PassiveOnEnemyKillMoveSpeed() : Passive(PassiveActivateOn::EnemyKill) {
	buffFromPassive = new BuffMoveSpeed(this, 120, 1);

	passiveDescription = "Increases movement speed by 100% after killing an enemy for 2 seconds.";
}

#pragma endregion

#pragma region PassiveActivateOn::Death



#pragma endregion

#pragma region PassiveActivateOn::RoomClear



#pragma endregion

#pragma region PassiveActivateOn::HitEnemy

PassiveOnHitSlowMoveSpeed::PassiveOnHitSlowMoveSpeed() : Passive(PassiveActivateOn::HitEnemy) {
	buffFromPassive = new BuffMoveSpeed(this, 30, -0.5);

	passiveDescription = "On hit slow enemy for 50% for 0.5 seconds.";
}

bool PassiveOnHitBurn::activate(std::list <AttackType*>& attacks, float activationValue) {
	buffBurn->changeDmg(activationValue / 4);
	return true;
}

PassiveOnHitBurn::PassiveOnHitBurn() : Passive(PassiveActivateOn::HitEnemy) {
	buffBurn = new BuffBurn(this, 120, 2);
	buffFromPassive = buffBurn;

	passiveDescription = "Burn!";
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
	else if (name == PassiveName::OnHitBurn)
		return new PassiveOnHitBurn();
	else
		_DEBUG_ERROR("Add passive to createPassive");

	return nullptr;
}
