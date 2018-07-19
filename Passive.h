#pragma once
#ifndef PASSIVE_H
#include <string>
#include <list>

enum class PassiveActivateOn { RoomClear, EnemyKill, Passive, TakeDamage, CreateAttack, HitEnemy, HitWall, HitWallOrEnemy, size_of_enum };
enum class PassiveName { None, OnRoomClearHeal, OnEnemyKillMoveSpeed, OnHitSlowMoveSpeed, size_of_enum };

struct SDL_Point;
class Buff;
class AttackType;

class Passive {
	PassiveActivateOn passActivateOn;

protected:
	Buff* buffFromPassive;
	std::string passiveDescription = "";
public:
	PassiveActivateOn activateOn() { return passActivateOn; }
	Buff* buffOnActivate() { return buffFromPassive; }
	std::string description() { return passiveDescription; }

	virtual bool activate(std::list <AttackType*>& attacks, SDL_Point* attackPoint) { return true; }
	virtual void update() {}

	Passive(PassiveActivateOn activationOn);
	virtual ~Passive();

	// Create passive object
	static Passive* createPassive(PassiveName name);
};


class PassiveOnRoomClearHeal : public Passive {

public:

	PassiveOnRoomClearHeal() : Passive(PassiveActivateOn::RoomClear) {}
	~PassiveOnRoomClearHeal() {}
};


class PassiveOnEnemyKillMoveSpeed : public Passive {

public:

	PassiveOnEnemyKillMoveSpeed();
	~PassiveOnEnemyKillMoveSpeed() {}
};


class PassiveOnHitSlowMoveSpeed : public Passive {

public:

	PassiveOnHitSlowMoveSpeed();
	~PassiveOnHitSlowMoveSpeed() {}
};







#endif // !PASSIVE_H