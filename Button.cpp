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
//	SDL_RenderDrawRect(Game::renderer, &buttonRect);

	if (buttonType == ButtonType::Boolean) {
		SDL_Rect r = {
			buttonRect.x + 10,
			buttonRect.y + buttonRect.h / 2 - dstRect.h / 4,
			dstRect.h / 2,
			dstRect.h / 2
		};
		Settings* s = Settings::get();
		if (value == "1")
			SDL_RenderCopy(Game::renderer, TextureManager::textures[TextureFile::MENU], &TextureManager::menuTextureSrcRect[MenuTextureName::BooleanTrue], &r);
		else
			SDL_RenderCopy(Game::renderer, TextureManager::textures[TextureFile::MENU], &TextureManager::menuTextureSrcRect[MenuTextureName::BooleanFalse], &r);
	}
}

void Button::setButtonType(ButtonType::ButtonType type) { 
	buttonType = type; 

	if (buttonType == ButtonType::Boolean) {
		dstRect.x = buttonRect.x + 20 + dstRect.h / 2;
	}
	else if (buttonType == ButtonType::Text) {
		dstRect.x = buttonRect.x + buttonRect.w / 2 - dstRect.w / 2;
		dstRect.y = buttonRect.y + buttonRect.h / 2 - dstRect.h / 2;
	}
}

bool Button::mouseOverButton() {
	if (Input::mousePosX > buttonRect.x && Input::mousePosX < buttonRect.x + buttonRect.w
		&& Input::mousePosY > buttonRect.y && Input::mousePosY < buttonRect.y + buttonRect.h)
		return true;

	return false;
}

void Button::actionOnClick(Screen* parentScreen, ScreensManager* screenManager, Game* game) {
//	(screenManager->*onClickAction)(game);
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
