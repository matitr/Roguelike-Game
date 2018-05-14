#include "Item.h"
#include "TextureManager.h"
#include "Map.h"
#include "Player.h"


void Item::onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {
	player->pickUpItem(this);

	objects.erase(std::find(objects.begin(), objects.end(), this));
}

Item::Item(float posX, float posY) : InteractiveObject(TextureManager::textureParameters[Coin], Static, Circle, SDL_SCANCODE_E) {
	position.x = posX;
	position.y = posY;
}


Item::~Item() {

}
