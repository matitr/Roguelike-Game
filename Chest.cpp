#include "Chest.h"
#include "InteractiveObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Player.h"


void ChestObj::onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {
	open = true;
	objCanInteract = false;
}

bool ChestObj::update(Player *player) {
	if (open && !lastFrameEnded()) {
		updateTexture();
	}

	return true;
}

ChestObj::ChestObj(float posX, float posY) 
	: InteractiveObject(TextureManager::textureParameters[SingleTexture::Chest], Static, Rectangle, SDL_SCANCODE_E), SpriteAnimation(3, 30, 3, srcRect) {
	position.x = posX;
	position.y = posY;
	setOnEndOfFrame();
}


ChestObj::~ChestObj() {

}
