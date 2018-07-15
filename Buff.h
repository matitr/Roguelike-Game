#pragma once
#include "Item.h"

class Passive;

class Buff {
	Passive* parentPassive;
	int duration = -1;
public:
	Passive* getParentPassive() { return parentPassive; }

	virtual bool update();
	virtual void activate(ItemPassives& unitStats) = 0;
	virtual void deactivate(ItemPassives& unitStats) = 0;

	virtual Buff* getCopy() = 0;

	Buff(Passive* parent = nullptr, int buffDuration = -1);
	virtual ~Buff();
};


class BuffHeal : public Buff {
	int healValue;
public:
	void activate(ItemPassives& unitStats) override;
	void deactivate(ItemPassives& unitStats) override;
	virtual Buff* getCopy() { return new BuffHeal(*this); };

	BuffHeal(Passive* parent, int buffDuration, int healV) : Buff(parent, buffDuration), healValue(healV) {}
	~BuffHeal() {}
};


class BuffMoveSpeed : public Buff {
	float moveSpeedValue;
public:
	void activate(ItemPassives& unitStats) override;
	void deactivate(ItemPassives& unitStats) override;
	virtual Buff* getCopy() { return new BuffMoveSpeed(*this); };

	BuffMoveSpeed(Passive* parent, int buffDuration, float moveValue) : Buff(parent, buffDuration), moveSpeedValue(moveValue) {}
	~BuffMoveSpeed() {}
};


