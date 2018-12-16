#include "ButtonCheckBox.h"
#include "Game.h"
#include "Settings.h"
#include "TextureManager.h"


void ButtonCheckBox::draw() {
	SDL_Rect r = {
		getButtonRect().x + 10,
		getButtonRect().y + getButtonRect().h / 2 - getTextDstRect().h / 4,
		getTextDstRect().h / 2,
		getTextDstRect().h / 2
	};
	
	if (getValue() == "1")
		SDL_RenderCopy(Game::renderer, TextureManager::textures[TextureFile::MENU], &TextureManager::menuTextureSrcRect[MenuTextureName::BooleanTrue], &r);
	else
		SDL_RenderCopy(Game::renderer, TextureManager::textures[TextureFile::MENU], &TextureManager::menuTextureSrcRect[MenuTextureName::BooleanFalse], &r);

	Button::draw();
}

ButtonCheckBox::ButtonCheckBox(SDL_Rect dstR, const char* text, void(*onClickAction)(Screen* parentScreen, ScreensManager* screenManager, Game*))
	: Button(dstR, text, onClickAction) {
	
	setTextDstRectX(getButtonRect().x + 20 + getTextDstRect().h / 2);
	setTextDstRectY(getButtonRect().y + getButtonRect().h / 2 - getTextDstRect().h / 2);
}


ButtonCheckBox::~ButtonCheckBox() {

}
