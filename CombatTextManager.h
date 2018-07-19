#pragma once
#include <vector>

class CombatText;
class Unit;
struct SDL_Point;

class CombatTextManager {
	std::vector<CombatText*> combatTexts;
public:
	static CombatTextManager& get() { static CombatTextManager cT; return cT; }

	void drawAndUpdate(SDL_Point* startRender);

	void addDamage(float value, Unit* unit);
	void addHeal(float value, Unit* unit);
	void addDebuff(float value, Unit* unit);

	CombatTextManager();
	~CombatTextManager();
};

