#pragma once
#include <string>
#include "SDL_ttf.h"
#include "myMath.h"

class Unit;

#define COMBAT_TEXT_DURATION 60

class CombatText {
	SDL_Texture* textTexture = nullptr;
	SDL_Rect dstRect;

	PointDouble unitPos;
	PointDouble positionShift;

	bool velocityToLeft;

	float xItChange;
	float xIt = 0;
	float yIt = 0.6;

	int duration;
public:
	bool update();
	void draw(SDL_Point* startRender);

	void setText(std::string text, TTF_Font* font, SDL_Color& color);

	CombatText(Unit* unit);
	~CombatText();
};

