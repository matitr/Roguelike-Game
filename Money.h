#pragma once
#include "InteractiveObject.h"
#include "SpriteAnimation.h"
	
class SpriteAnimation;
class Player;

class Money : public InteractiveObject, public SpriteAnimation {
	int amount;
public:
	void onPlayerTouch() override;
	bool update(Player *player) override;

	Money(float posX, float posY);
	~Money();
};

