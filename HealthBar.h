#pragma once
#include "myMath.h"
#include "SDL.h"

enum class UnitType;

class HealthBar {
	const UnitType& unitType;

	const float& hp;
	const float& hpMax;

	const SDL_Rect& unitDstRect;
	SDL_Rect healthBarDstRect;
public:
	void draw();

	HealthBar(SDL_Rect& unitDstRect, float& hp, float& hpMax, UnitType& unitType);
	~HealthBar();
};

