#pragma once
#include <vector>

class CombatText;
class Unit;
struct SDL_Point;
enum class DamageType;

class CombatTextManager {
	std::vector<CombatText*> combatTexts;
public:
	static CombatTextManager& get() { static CombatTextManager cT; return cT; }

	void drawAndUpdate(SDL_Point* startRender);

	void addDamage(float value, DamageType damageType, Unit* unit);
	void addDebuff(float value, Unit* unit);

	CombatTextManager();
	~CombatTextManager();
};

