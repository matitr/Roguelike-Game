#pragma once


class Passive;

class Buff {
	Passive* parentPassive;

public:
	Passive* getParentPassive() { return parentPassive; }

	virtual bool update() = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual Buff* getCopy() = 0;

	Buff(Passive* parent = nullptr);
	virtual ~Buff();
};

