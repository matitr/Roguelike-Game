#pragma once
#include "InteractiveObject.h"

class Item : public InteractiveObject {

public:
	void onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) override;

	Item(float posX, float posY);
	~Item();
};

