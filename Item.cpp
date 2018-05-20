#include "Item.h"
#include "TextureManager.h"
#include "Map.h"
#include "Player.h"
#include "SDL_ttf.h"
#include "Game.h"
#include "DataBase.h"
#include <string>


void Item::onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {
	player->inventory().pickUpItem(this);

	objects.erase(std::find(objects.begin(), objects.end(), this));
}

void Item::createDescriptionTxt() { // todo
	descriptionDstRect.w = 300;
	float descriptionHeight = 0;
	float letterSize = 18;

	SDL_Color white = { 255,255,255,255 };
	SDL_Color gold = { 255, 204, 0,255 };
	SDL_Color blue = { 0, 51, 204,255 };
	SDL_Rect r = { 10,5,0,0 };

	SDL_SetRenderDrawColor(Game::renderer, 50, 50, 50, 255);
	SDL_RenderClear(Game::renderer);

	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Font/font.ttf", letterSize * 0.9);

	std::string itemTypeStr = DataBase::getItemTypeText(type);
	char itemType[100];
	strcpy_s(itemType, itemTypeStr.c_str());
	SDL_Surface* surface = TTF_RenderText_Blended(font, itemType, gold);
	SDL_Texture* message = SDL_CreateTextureFromSurface(Game::renderer, surface);

	int w, h;
	SDL_QueryTexture(message, NULL, NULL, &r.w, &r.h);
	r.x = descriptionDstRect.w - r.w - 5;



	int numberOfPassives = 0;

	for (int i = 0; i < staticPassives.size(); i++)
		if (staticPassives[i])
			numberOfPassives++;


	descriptionDstRect.h = r.h * (3 + numberOfPassives);
	itemDescription = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 300, descriptionDstRect.h);
	SDL_SetTextureBlendMode(itemDescription, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(Game::renderer, itemDescription);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 200);
	SDL_RenderClear(Game::renderer);
	SDL_RenderCopy(Game::renderer, message, NULL, &r);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(message);

	r.x = 10;
	r.y = r.h * 2;
	int counter = 0;
	for (int i = 0; i < staticPassives.size(); i++)
		if (staticPassives[i]) {
			std::string passiveText = DataBase::getPassiveText(i, staticPassives[i]);
			char text[100];
			strcpy_s(text, passiveText.c_str());
			SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, blue);
			SDL_Texture* messageTxt = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
			SDL_QueryTexture(messageTxt, NULL, NULL, &r.w, &r.h);

			SDL_RenderCopy(Game::renderer, messageTxt, NULL, &r);

			SDL_FreeSurface(surfaceMessage);
			SDL_DestroyTexture(messageTxt);
			r.y += r.h;
		}

	SDL_RenderDrawRect(Game::renderer, &descriptionDstRect);

	SDL_SetRenderTarget(Game::renderer, NULL);

	SDL_RenderCopy(Game::renderer, itemDescription, NULL, &descriptionDstRect);
	SDL_RenderPresent(Game::renderer);

	TTF_Quit();
}

Item::Item(float posX, float posY) : InteractiveObject(TextureManager::textureParameters[Coin], Static, Circle, SDL_SCANCODE_E) {
	position.x = posX;
	position.y = posY;

	type = MainWeapon;
	
	staticPassives[StaticPassiveName::pierceShots] = 999999999;
	staticPassives[StaticPassiveName::homing] = 99;

	createDescriptionTxt();
}


Item::~Item() {

}
