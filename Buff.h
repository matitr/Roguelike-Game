#pragma once
#include "Item.h"

class Passive;
class Unit;

//All buffs
class BuffSingleHeal;
class BuffHealOvertime;
class BuffMoveSpeed;
class BuffBurn;
class BuffDamageMult;
class BuffDamageTakenMult;


class Buff {
	Passive* parentPassive;

protected:
	int duration = -1;
public:
	Passive* getParentPassive() { return parentPassive; }

	virtual bool update(Unit* unit);
	virtual void activate(ItemPassives& unitStats) {};
	virtual void deactivate(ItemPassives& unitStats) {};

	virtual Buff* getCopy() = 0;

	Buff(Passive* parent = nullptr, int buffDuration = -1);
	virtual ~Buff();
};


class BuffSingleHeal : public Buff {
	float healValue;
public:
	bool update(Unit* unit) override;
	Buff* getCopy() override { return new BuffSingleHeal(*this); };

	BuffSingleHeal(Passive* parent, int healV) : Buff(parent, 1), healValue(-healV) {}
	~BuffSingleHeal() {}
};


class BuffHealOvertime : public Buff {
	float healValue;
public:
	bool update(Unit* unit) override;
	Buff* getCopy() override { return new BuffHealOvertime(*this); };

	BuffHealOvertime(Passive* parent, int buffDuration, int healV) : Buff(parent, buffDuration), healValue(-healV) {}
	~BuffHealOvertime() {}
};


class BuffMoveSpeed : public Buff {
	float moveSpeedValue;
public:
	void activate(ItemPassives& unitStats) override;
	void deactivate(ItemPassives& unitStats) override;
	Buff* getCopy() override { return new BuffMoveSpeed(*this); };

	BuffMoveSpeed(Passive* parent, int buffDuration, float moveValue) : Buff(parent, buffDuration), moveSpeedValue(moveValue) {}
	~BuffMoveSpeed() {}
};


class BuffBurn : public Buff {
	float dmgPerTick;
public:
	void changeDmg(float dmg) { dmgPerTick = dmg; }

	bool update(Unit* unit) override;
	Buff* getCopy() override { return new BuffBurn(*this); };

	BuffBurn(Passive* parent, int buffDuration, float dmgPerTick) : Buff(parent, buffDuration), dmgPerTick(dmgPerTick) {}
	~BuffBurn() {}
};


class BuffDamageMult : public Buff {
	float damageMult;
public:
	void activate(ItemPassives& unitStats) override;
	void deactivate(ItemPassives& unitStats) override;
	Buff* getCopy() override { return new BuffDamageMult(*this); };

	BuffDamageMult(Passive* parent, int buffDuration, float damageMult) : Buff(parent, buffDuration), damageMult(damageMult) {}
	~BuffDamageMult() {}
};


class BuffDamageTakenMult : public Buff {
	float damageTakenMult;
public:
	void activate(ItemPassives& unitStats) override;
	void deactivate(ItemPassives& unitStats) override;
	Buff* getCopy() override { return new BuffDamageTakenMult(*this); };

	BuffDamageTakenMult(Passive* parent, int buffDuration, float damageTakenMult) : Buff(parent, buffDuration), damageTakenMult(damageTakenMult) {}
	~BuffDamageTakenMult() {}
};


