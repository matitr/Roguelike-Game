#pragma once
#include "InteractiveObject.h"

#define TELEPORT_MAP_SIZE_MULTIPLER 2

class Map;
class Player;

class Teleporter : public InteractiveObject {

public:
	void onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) override;
	void updateInteraction(Map* map, std::vector <InteractiveObject*>& objects, Player* player) override;

	Teleporter(float posX, float posY);
	~Teleporter();
};

