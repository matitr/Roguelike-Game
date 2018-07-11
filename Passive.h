#pragma once


enum class PassiveActivateOn { RoomClear, EnemyKill, Passive, size_of_enum };

class Buff;

class Passive {
	PassiveActivateOn passActivateOn;

	Buff* buffFromPassive;
public:
	PassiveActivateOn activateOn() { return passActivateOn; }
	Buff* buffOnActivate() { return buffFromPassive; }

	virtual bool activate() = 0;
	virtual void update() {};

	Passive(PassiveActivateOn activationOn);
	virtual ~Passive();
};

