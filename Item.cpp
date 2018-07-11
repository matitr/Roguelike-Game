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

void Item::createDescriptionTxt() { 
	descriptionDstRect.w = 350;
	float descriptionHeight = 0;

	SDL_Rect r = { 10,5,0,0 };

	SDL_SetRenderDrawColor(Game::renderer, 50, 50, 50, 255);
	SDL_RenderClear(Game::renderer);

	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

	SDL_Texture* message = DataBase::getItemTypeText(type);
	SDL_QueryTexture(message, NULL, NULL, &r.w, &r.h);
	r.x = descriptionDstRect.w - r.w - 5;

	int numberOfPassives = 0;

	for (int i = 0; i < staticPassives.size(); i++)
		if (staticPassives[i])
			numberOfPassives++;

	descriptionDstRect.h = r.h * (3 + numberOfPassives); // Item description height
	itemDescription = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, descriptionDstRect.w, descriptionDstRect.h);
	SDL_SetTextureBlendMode(itemDescription, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(Game::renderer, itemDescription);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 200);
	SDL_RenderClear(Game::renderer);
	SDL_RenderCopy(Game::renderer, message, NULL, &r);
	SDL_DestroyTexture(message);

	r.x = 10;
	r.y = r.h * 2;
	int counter = 0;
	for (int i = 0; i < staticPassives.size(); i++) // Draw passives texts on item description texture
		if (staticPassives[i]) {
			SDL_Texture* messageTxt = nullptr;
			DataBase::getPassiveText(i, staticPassives[i], messageTxt);
			SDL_QueryTexture(messageTxt, NULL, NULL, &r.w, &r.h);

			SDL_RenderCopy(Game::renderer, messageTxt, NULL, &r);

			SDL_DestroyTexture(messageTxt);
			r.y += r.h;
		}

	SDL_SetRenderDrawColor(Game::renderer, 50, 200, 50, 255);
	SDL_RenderDrawRect(Game::renderer, &descriptionDstRect);
	SDL_SetRenderTarget(Game::renderer, NULL);
}

void Item::drawDescription(SDL_Rect& slotRect, SDL_Point& WindowResolution) {
	// Draw on right side of screen
	descriptionDstRect.x = slotRect.x - descriptionDstRect.w;

	descriptionDstRect.y = slotRect.y + slotRect.h / 2 - descriptionDstRect.h / 2;

	if (descriptionDstRect.y < 0)
		descriptionDstRect.y = 0;
	else if (descriptionDstRect.y + descriptionDstRect.h >= WindowResolution.y)
		descriptionDstRect.y = WindowResolution.y - descriptionDstRect.h;

	SDL_RenderCopy(Game::renderer, itemDescription, NULL, &descriptionDstRect);
}

Item::Item(ItemName::Name itemName, double posX, double posY)
	: InteractiveObject(TextureManager::itemTextureDetails[itemName], DataBase::inventoryDelails.slotSize, SDL_SCANCODE_E), type(DataBase::items[itemName].type)
	, staticPassives(DataBase::items[itemName].passives) {

	position.x = posX;
	position.y = posY;
	staticPassives[StaticPassiveName::unitSpeed] = 25.0;

	createDescriptionTxt();
}

Item::Item(double posX, double posY) : InteractiveObject(TextureManager::textureParameters[SingleTexture::Coin], Static, Circle, SDL_SCANCODE_E) {
	position.x = posX;
	position.y = posY;

	type = ItemType::Passive;

	staticPassives[StaticPassiveName::pierceShots] = 2;
	staticPassives[StaticPassiveName::homing] = 5;
	staticPassives[StaticPassiveName::unitSpeed] = 25.0;
	staticPassives[StaticPassiveName::numbOfProjectiles] = 1;
	staticPassives[StaticPassiveName::projectileSize] = 100;
	//	staticPassives[StaticPassiveName::chargeProjectiles] = 1;

	createDescriptionTxt();

}

Item::~Item() {
	if (itemDescription)
		SDL_DestroyTexture(itemDescription);

	if (passive)
		delete passive;
}
