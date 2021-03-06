#include "Button.h"
#include "Game.h"
#include "DataBase.h"
#include "SDL_TTF.h"
#include "Input.h"

#include "ScreensManager.h"
#include "Settings.h"
void Button::draw() {
	SDL_RenderCopy(Game::renderer, textTexture, NULL, &dstRect);
	SDL_SetRenderDrawColor(Game::renderer
		, DataBase::colors[TextColor::MenuButtonText].r
		, DataBase::colors[TextColor::MenuButtonText].g
		, DataBase::colors[TextColor::MenuButtonText].b
		, DataBase::colors[TextColor::MenuButtonText].a);
}

bool Button::mouseOverButton() {
	if (Input::mousePosX > buttonRect.x && Input::mousePosX < buttonRect.x + buttonRect.w
		&& Input::mousePosY > buttonRect.y && Input::mousePosY < buttonRect.y + buttonRect.h)
		return true;

	return false;
}

void Button::actionOnClick(Screen* parentScreen, ScreensManager* screenManager, Game* game) {
	onClickAction(parentScreen, screenManager, game);
}

Button::Button(SDL_Rect dstR, const char* text, void(*action)(Screen* parentScreen, ScreensManager* screenManager, Game*)) 
	: dstRect(dstR), buttonRect(dstR), onClickAction(action) {

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(DataBase::fonts[FontPurpose::MenuButtonsText], text, DataBase::colors[TextColor::MenuButtonText]);
	textTexture = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);

	SDL_QueryTexture(textTexture, NULL, NULL, &dstRect.w, &dstRect.h);

	dstRect.x -= dstRect.w / 2;
	dstRect.y -= dstRect.h / 2;

	buttonRect.x -= buttonRect.w / 2;
	buttonRect.y -= buttonRect.h / 2;
}


Button::~Button() {
	SDL_DestroyTexture(textTexture);
}
