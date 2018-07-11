#pragma once
#include <vector>

class Buff;
class Passive;

class BuffsManager {
	std::vector<Buff*> buffs;

public:
	void addBuffCopy(Buff* buff);
	void removeBuffs(Passive* parentPassive);
	void updateAllBuffs();

	BuffsManager();
	~BuffsManager();
};

