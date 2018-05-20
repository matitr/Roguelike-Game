#pragma once
#ifndef ITEM_H
#define ITEM_H


#include "InteractiveObject.h"
#include <array>


namespace StaticPassiveName {
	enum StaticPassiveName { numbOfProjectiles, pierceShots, homing, enum_size };
}

typedef std::array<int, StaticPassiveName::enum_size> ItemPassives;

enum ItemType;
enum class PassiveActivateOn { RoomClear, size_of_enum };


class Item : public InteractiveObject {
	ItemType type;

	ItemPassives staticPassives;
	SDL_Texture* itemDescription;
	SDL_Rect descriptionDstRect;
public:
	ItemType itemType() { return type; }
	ItemPassives& getStaticPassives() { return staticPassives; }

	void onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) override;

	void createDescriptionTxt();

	Item(float posX, float posY);
	~Item();
};


#endif // ! ITEM_H