#pragma once
#include <vector>
#include "DataBase.h"
#include "Item.h"
class Item;
class Map;
class Player;
class PassivesManager;
enum class PassiveActivateOn;

struct InventorySlot {
	SDL_Rect rect;
	Item* item = nullptr;
	ItemType itemType;

	InventorySlot(int x, int y, SDL_Point s) : itemType(ItemType::Universal), rect({ x,y, s.x, s.y }), item(nullptr)  {}
	InventorySlot(ItemType t, SDL_Rect& r, SDL_Rect& dstR) : itemType(t), rect({ r.x + dstR.x, r.y + dstR.y, r.w,r.h }), item(nullptr) {}
	~InventorySlot() {
		if (item)
			delete item;
	}
};


class Inventory {
	InventoryDetails details;
	SDL_Rect dstRectInv;

	bool invIsOpened = false;
	std::vector<std::vector<InventorySlot*>> inventorySlots;
	std::vector<InventorySlot*> equippedSlots;

	InventorySlot* slotUnderMouse = nullptr;
	bool slotUnderMouseEq = false;

	InventorySlot* clickedSlot = nullptr;
	Item* clickedItem = nullptr;
	bool clickedSlotEq = false;

	PassivesManager* unitPassivesManager;

	SDL_Point windowResolution;

	void updateFocusOnSlot();
public:
	void open() { invIsOpened = true; }
	void close();
	bool isOpened() { return invIsOpened; }

	void update(Map* map, Player* player);
	void draw();

	void pickUpItem(Item* item);
	void dropItem(Item* item);

	void equipItem(InventorySlot* item);
	void unequipItem(InventorySlot* item);

	void calculatePassives(); // Add passives from all equipped items

	void highlightAllSlots(); // For testing

	Inventory(PassivesManager* passivesManager, SDL_Point& windowResolution);
	~Inventory();
};

