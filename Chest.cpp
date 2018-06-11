#include "Chest.h"
#include "InteractiveObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Player.h"


void ChestObj::onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {
	open = true;
	objCanInteract = false;

	objects.push_back(new Item(ItemName::Name(rand() % ItemName::enum_size), getPositionX(), getPositionY() + 40));
}

bool ChestObj::update(Player *player) {
	if (open && !lastFrameEnded()) {
		updateTexture();
	}

	return true;
}

ChestObj::ChestObj(double posX, double posY)
	: InteractiveObject(TextureManager::textureParameters[SingleTexture::Chest], Static, Rectangle, SDL_SCANCODE_E)
	, SpriteAnimation(DataBase::animations[AnimationName::ChestOpening], srcRect) {

	position.x = posX;
	position.y = posY;
	radiusY = 20;
	setPositionShiftY(50);
	setOnEndOfFrame();
}


ChestObj::~ChestObj() {

}
