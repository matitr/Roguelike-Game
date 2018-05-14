#pragma once
#include "GameObject.h"

class Player;
class Map;

class InteractiveObject : public GameObject {
protected:
	bool objCanInteract;
	bool solidObj;
	bool pickupObj = false;
	bool interactingNow = false;

	bool interactObjOnKey;
	SDL_Scancode interactObjKey;

public:
	bool solid() { return solidObj; }
	bool interactOnKey() { return interactObjOnKey; }
	SDL_Scancode interactKey() { return interactObjKey; }
	bool interacting() { return interactingNow; }

	virtual void onPlayerTouch();
	virtual void onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player);
	virtual void updateInteraction(Map* map, std::vector <InteractiveObject*>& objects, Player* player);
	virtual bool update(Player *player);

	InteractiveObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType);
	InteractiveObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType, int r);
	InteractiveObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType, SDL_Scancode _interactKey);
	~InteractiveObject();
};

