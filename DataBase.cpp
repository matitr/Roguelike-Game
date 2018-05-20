#include "DataBase.h"
#include "TextureManager.h"
#include "Item.h"
#include <string>

InventoryDetails DataBase::inventoryDelails;
std::unordered_map<AnimationName, AnimationDetails> DataBase::animations;

void DataBase::loadAllDataBases() {
	DataBase::loadInventoryDetails();
	loadAnimationsDetails();
}

void DataBase::loadInventoryDetails() {
	DataBase::inventoryDelails.texture = TextureManager::textures[INVENTORY];

	DataBase::inventoryDelails.width = 431;
	DataBase::inventoryDelails.height = 927;

	DataBase::inventoryDelails.startInventoryTab.x = 80;
	DataBase::inventoryDelails.startInventoryTab.y = 614;
	DataBase::inventoryDelails.numerOfSlots.x = 6;
	DataBase::inventoryDelails.numerOfSlots.y = 5;

	DataBase::inventoryDelails.slotSize.x = 38;
	DataBase::inventoryDelails.slotSize.y = 38;

	DataBase::inventoryDelails.spaceBetweenSlots = 9;

	// Equipped slots
	// { ItemType, SDL_Rect { x, y, w, h }
	SDL_Rect slot = { 66, 174, inventoryDelails.slotSize.x, inventoryDelails.slotSize.y };
	int space = 15;

	inventoryDelails.eqDetails.push_back({ ItemType::MainWeapon,
		{ slot.x,slot.y,inventoryDelails.slotSize.x,inventoryDelails.slotSize.x } });

	for (int i = 1; i <= 4; i++)
		inventoryDelails.eqDetails.push_back({ ItemType::Active,
			{ slot.x,slot.y + (slot.h + space) * i,inventoryDelails.slotSize.x,inventoryDelails.slotSize.x } });

	slot.x = 330;

	for (int i = 0; i < 5; i++)
		inventoryDelails.eqDetails.push_back({ ItemType::Active,
			{ slot.x,slot.y + (slot.h + space) * i,inventoryDelails.slotSize.x,inventoryDelails.slotSize.x } });

}

void DataBase::loadAnimationsDetails() {
	animations[AnimationName::Projectile] = { TextureManager::textures[PROJECTILES], 25, 25, 0, 3, 10 };
}

 std::string DataBase::getPassiveText(int passive, float value) {
	if (passive == StaticPassiveName::numbOfProjectiles) {
		return "Increase number of projectiles by " + std::to_string(int(value));
	}
	else if (passive == StaticPassiveName::pierceShots) {
		return "Increase pierce by " + std::to_string(int(value));
	}
	else if (passive == StaticPassiveName::homing) {
		return "Increase homing by " + std::to_string(int(value));
	}
}

 std::string DataBase::getItemTypeText(enum ItemType itemType) {
	 if (itemType == Universal)
		 return "Universal";
	 else if (itemType == MainWeapon)
		 return "MainWeapon";
	 else if (itemType == Active)
		 return "Active";
	 else if (itemType == Passive)
		 return "Passive";
 }

DataBase::DataBase() {

}


DataBase::~DataBase() {

}
