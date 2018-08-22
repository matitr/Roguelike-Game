#pragma once
#ifndef PASSIVE_H
#include <string>
#include <list>

enum class PassiveActivateOn { Passive, CreateAttack, TakeDamage, EnemyKill, Death, RoomClear, HitEnemy, HitWall, HitWallOrEnemy, size_of_enum };
enum class PassiveName { None, OnRoomClearHeal, OnEnemyKillMoveSpeed, OnHitSlowMoveSpeed, OnHitBurn, size_of_enum };

struct SDL_Point;
class Buff;
class AttackType;
class Unit;
class BuffBurn;

// All passives
#pragma region AllPassives

#pragma region PassiveActivateOn::Passive
#pragma endregion

#pragma region PassiveActivateOn::CreateAttack
#pragma endregion

#pragma region PassiveActivateOn::TakeDamage
#pragma endregion

#pragma region PassiveActivateOn::EnemyKill
class PassiveOnEnemyKillMoveSpeed;
#pragma endregion

#pragma region PassiveActivateOn::Death
#pragma endregion

#pragma region PassiveActivateOn::RoomClear
class PassiveOnRoomClearHeal;
#pragma endregion

#pragma region PassiveActivateOn::HitEnemy
class PassiveOnHitSlowMoveSpeed;
class PassiveOnHitBurn;
#pragma endregion

#pragma region PassiveActivateOn::HitWall
#pragma endregion

#pragma region PassiveActivateOn::HitWallOrEnemy
#pragma endregion

#pragma endregion


class Passive {
	PassiveActivateOn passActivateOn;

protected:
	Buff* buffFromPassive;
	std::string passiveDescription = "";
	Unit* unitParent = nullptr;

public:
	PassiveActivateOn activateOn() { return passActivateOn; }
	Buff* buffOnActivate() { return buffFromPassive; }
	std::string description() { return passiveDescription; }
	void setParentUnit(Unit* unit) { unitParent = unit; }
	void removeParentUnit() { unitParent = nullptr; }

	virtual bool activate(std::list <AttackType*>& attacks, float activationValue = 0) { return true; }
	virtual void update() {}

	Passive(PassiveActivateOn activationOn);
	virtual ~Passive();

	// Create passive object
	static Passive* createPassive(PassiveName name);
};

#pragma region PassiveActivateOn::Passive



#pragma endregion

#pragma region PassiveActivateOn::CreateAttack



#pragma endregion

#pragma region PassiveActivateOn::TakeDamage



#pragma endregion

#pragma region PassiveActivateOn::EnemyKill

class PassiveOnEnemyKillMoveSpeed : public Passive {

public:
	PassiveOnEnemyKillMoveSpeed();
	~PassiveOnEnemyKillMoveSpeed() {}
};

#pragma endregion

#pragma region PassiveActivateOn::Death



#pragma endregion

#pragma region PassiveActivateOn::RoomClear

class PassiveOnRoomClearHeal : public Passive {

public:
	PassiveOnRoomClearHeal() : Passive(PassiveActivateOn::RoomClear) {}
	~PassiveOnRoomClearHeal() {}
};

#pragma endregion

#pragma region PassiveActivateOn::HitEnemy

class PassiveOnHitSlowMoveSpeed : public Passive {

public:
	PassiveOnHitSlowMoveSpeed();
	~PassiveOnHitSlowMoveSpeed() {}
};

class PassiveOnHitBurn : public Passive {
	BuffBurn* buffBurn;
public:
	bool activate(std::list <AttackType*>& attack, float activationValue = 0) override;

	PassiveOnHitBurn();
	~PassiveOnHitBurn() {}
};

#pragma endregion

#pragma region PassiveActivateOn::HitWall



#pragma endregion

#pragma region PassiveActivateOn::HitWallOrEnemy



#pragma endregion













#endif // !PASSIVE_H