#include "Money.h"
#include "TextureManager.h"
#include "Player.h"


void Money::onPlayerTouch() {
	pickupObj = true;
}

bool Money::update(Player *player) {
	if (pickupObj) {
		player->addMoney(amount);
		return false;
	}

	updateTexture();
	return true;
}

Money::Money(float posX, float posY) : InteractiveObject(TextureManager::textureParameters[Coin], Static, Circle), SpriteAnimation(DataBase::animations[AnimationName::CoinSpin], srcRect) {
	position.x = posX;
	position.y = posY;
	amount = 1;
}


Money::~Money() {

}
