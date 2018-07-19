#include "CombatText.h"
#include "TextureManager.h"
#include "Unit.h"
#include "Game.h"


bool CombatText::update() {
	if (duration <= 0)
		return false;

	duration--;
	xIt += xItChange;
	if (velocityToLeft) {
		positionShift.x += xIt;
		positionShift.y += yIt;
	}
	else {
		positionShift.x -= xIt;
		positionShift.y += yIt;
	}

	if (duration < COMBAT_TEXT_DURATION * 0.6)
		SDL_SetTextureAlphaMod(textTexture, 255 * duration / 40);

	return true;
}

void CombatText::draw(SDL_Point* startRender) {
	dstRect.x = int(unitPos.x - startRender->x - positionShift.x);
	dstRect.y = int((unitPos.y - startRender->y) * HEIGHT_SCALE - positionShift.y);

	SDL_RenderCopy(Game::renderer, textTexture, NULL, &dstRect);
}

void CombatText::setText(std::string text, TTF_Font* font, SDL_Color& color) {
	textTexture = TextureManager::textureFromText(text, font, color, 9999);
	SDL_QueryTexture(textTexture, NULL, NULL, &dstRect.w, &dstRect.h);

	if (velocityToLeft)
		positionShift.x += dstRect.w;
}

CombatText::CombatText(Unit* unit) : duration(COMBAT_TEXT_DURATION), unitPos(unit->getPosition()) {
	positionShift.x = rand() % int(unit->getRadius() * 0.4 + 1);
	positionShift.y = unit->getPositionShiftY() * 0.7 + rand() % int(unit->getPositionShiftY() * 0.3 + 1);

	xItChange = (rand() % 12 + 1) * 0.001f;

	velocityToLeft = rand() % 2;
	if (!velocityToLeft)
		positionShift.x *= -1;
}


CombatText::~CombatText() {
	SDL_DestroyTexture(textTexture);
}
