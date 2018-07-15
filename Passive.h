#pragma once
#ifndef PASSIVE_H
#include <string>

enum class PassiveActivateOn { RoomClear, EnemyKill, Passive, size_of_enum };
enum class PassiveName { None, OnRoomClearHeal, OnEnemyKillMoveSpeed, size_of_enum };

class Buff;

class Passive {
	PassiveActivateOn passActivateOn;

protected:
	Buff* buffFromPassive;
	std::string passiveDescription = "";
public:
	PassiveActivateOn activateOn() { return passActivateOn; }
	Buff* buffOnActivate() { return buffFromPassive; }
	std::string description() { return passiveDescription; }

	virtual bool activate() { return true; }
	virtual void update() {}

	Passive(PassiveActivateOn activationOn);
	virtual ~Passive();

	// Create passive object
	static Passive* createPassive(PassiveName name);
};


class PassiveOnRoomClearHeal : public Passive {

public:
	bool activate() override;

	PassiveOnRoomClearHeal() : Passive(PassiveActivateOn::RoomClear) {}
	~PassiveOnRoomClearHeal() {}
};


class PassiveOnEnemyKillMoveSpeed : public Passive {

public:
	bool activate() override;

	PassiveOnEnemyKillMoveSpeed();
	~PassiveOnEnemyKillMoveSpeed() {}
};







#endif // !PASSIVE_H