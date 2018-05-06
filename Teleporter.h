#pragma once
#include "InteractiveObject.h"

class Map;
class Player;

class Teleporter : public InteractiveObject {

public:
	void onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) override;
	void updateInteraction(Map* map, std::vector <InteractiveObject*>& objects, Player* player, SDL_Event& event) override;

	Teleporter(float posX, float posY);
	~Teleporter();
};

