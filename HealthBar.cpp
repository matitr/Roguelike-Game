#include "HealthBar.h"
#include "Game.h"
#include "Unit.h"
#include "Settings.h"


void HealthBar::draw() {
	if (unitType == UnitType::Player) {
		if (!Settings::get()->showPlayerHp)
			return;
	}
	else
		if (!Settings::get()->showEnemyHp)
			return;

	healthBarDstRect.x = unitDstRect.x + unitDstRect.w / 2 - healthBarDstRect.w / 2;
	healthBarDstRect.y = unitDstRect.y - healthBarDstRect.h - 4;

	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(Game::renderer, &healthBarDstRect); // Frame
	SDL_SetRenderDrawColor(Game::renderer, 179, 0, 0, 255);

	healthBarDstRect.x++;
	healthBarDstRect.y++;
	healthBarDstRect.w -= 2;
	healthBarDstRect.h -= 2;

	int barWidth = healthBarDstRect.w;

	healthBarDstRect.w = int(healthBarDstRect.w * (hp / hpMax));
	SDL_RenderFillRect(Game::renderer, &healthBarDstRect); // Health bar

	healthBarDstRect.w = barWidth;
	healthBarDstRect.x--;
	healthBarDstRect.y--;
	healthBarDstRect.w += 2;
	healthBarDstRect.h += 2;
}

HealthBar::HealthBar(SDL_Rect& _unitDstRect, float& _hp, float& _hpMax, UnitType& uType) : unitDstRect(_unitDstRect), hp(_hp), hpMax(_hpMax), unitType(uType) {
	healthBarDstRect.w = 60;
	healthBarDstRect.h = 5;

}


HealthBar::~HealthBar() {

}
