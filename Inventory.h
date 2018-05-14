#pragma once
#include <vector>
#include "DataBase.h"

class Item;

struct InventorySlot {
	SDL_Point coord;
	Item* item = nullptr;

	InventorySlot(int x, int y) : coord({ x,y }) {
		item = nullptr;
	}
};

class Inventory : private InventoryDetails {
	SDL_Rect dstRectInv;

	bool isOpened = false;
	std::vector<std::vector<InventorySlot*>> slots;

	InventorySlot* slotUnderMouse = nullptr;
	InventorySlot* slotToShowOptions = nullptr;

	InventorySlot* clickedSlot = nullptr;
	Item* clickedItem = nullptr;

	void updateFocusOnSlot();
public:
	void openInventory() { isOpened = true; }
	void closeInventory();
	bool inventoryIsOpened() { return isOpened; }

	void updateInventory();
	void drawInventory();


	void pickUpItem(Item* item);
	void dropItem(Item* item);

	Inventory();
	~Inventory();
};

