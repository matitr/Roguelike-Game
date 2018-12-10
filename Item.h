#pragma once
#ifndef ITEM_H
#define ITEM_H


#include "InteractiveObject.h"
#include "TextureManager.h"
#include <array>


namespace StaticPassiveName {
	enum StaticPassiveName { hp, hpMax, damage, damageMult, damageTakenMult, numbOfProjectiles, pierceShots, chargeProjectiles, homing
		, projectileSpeed, projectileSpeedMult, projectileSizeMult, attackSpeedMult, unitSpeed, unitSpeedMult, enum_size };
}

typedef std::array<float, StaticPassiveName::enum_size> ItemPassives;

enum class ItemType;
class Passive;

class Item : public InteractiveObject {
	ItemType type;

	ItemPassives staticPassives;
	Passive* passive = nullptr;

	SDL_Texture* itemDescription = nullptr;
	SDL_Rect descriptionDstRect;

	void createDescriptionTxt();
public:
	ItemType itemType() { return type; }
	ItemPassives& getStaticPassives() { return staticPassives; }
	Passive* getPassive() { return passive; }

	void onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) override;

	void drawDescription(SDL_Rect& slotRect, SDL_Point& WindowResolution);

	Item(ItemName::Name itemName, double posX, double posY);
	Item(double posX, double posY);
	~Item();
};


#endif // ! ITEM_H