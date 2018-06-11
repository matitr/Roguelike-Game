#pragma once
#include "InteractiveObject.h"
#include "SpriteAnimation.h"

class SpriteAnimation;
class Player;
class Map;

class ChestObj : public InteractiveObject, public SpriteAnimation {
	bool open = false;

public:
	void onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) override;
	bool update(Player *player) override;

	ChestObj(double posX, double posY);
	~ChestObj();
};

