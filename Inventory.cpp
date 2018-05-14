#include "Inventory.h"
#include "Game.h"
#include "Input.h"
#include "Item.h"


void Inventory::closeInventory() {
	if (clickedSlot) {
		clickedSlot->item = clickedItem;
		clickedItem->setPositionX(clickedSlot->coord.x + itemSize.x / 2);
		clickedItem->setPositionY(clickedSlot->coord.y + itemSize.y / 2);
	}

	isOpened = false;
	clickedSlot = nullptr;
	clickedItem = nullptr;
	slotUnderMouse = nullptr;
	slotToShowOptions = nullptr;
}

void Inventory::updateInventory() {
	if (!isOpened) {
		isOpened = false;
		return;
	}

	int mouseX = Input::mousePosX, mouseY = Input::mousePosY;
	double x = (mouseX - dstRectInv.x - startInventoryTab.x) / (float(itemSize.x) + float(spaceBetweenItems));
	double y = (mouseY - dstRectInv.y - startInventoryTab.y) / (float(itemSize.y) + float(spaceBetweenItems));
	slotUnderMouse = nullptr;

	if (clickedSlot) {
		clickedItem->setPositionX(mouseX);
		clickedItem->setPositionY(mouseY);
	}

	// selected item in inventory
	if (x >= 0 && x < numerOfItemsInv.x && y >= 0 && y < numerOfItemsInv.y
		&& (x - int(x)) <= float(itemSize.x) / (itemSize.x + spaceBetweenItems) && (y - int(y)) <= float(itemSize.y) / (itemSize.y + spaceBetweenItems)) {

		slotUnderMouse = slots[int(x)][int(y)];
	}

	updateFocusOnSlot();
}

void Inventory::updateFocusOnSlot() {
	if (slotUnderMouse) {
		if (Input::mousePressed[SDL_BUTTON_LEFT]) { // Move item
			if (!clickedSlot) { // First click
				clickedSlot = slotUnderMouse;
				clickedItem = slotUnderMouse->item;
				slotUnderMouse->item = nullptr;;
			}
			else { // Move item
				clickedSlot->item = slotUnderMouse->item;
				slotUnderMouse->item = clickedItem;
				clickedItem->setPositionX(slotUnderMouse->coord.x + itemSize.x / 2);
				clickedItem->setPositionY(slotUnderMouse->coord.y + itemSize.y / 2);
				clickedSlot = nullptr;
				clickedItem = nullptr;
			}
		}
		else if (Input::mousePressed[SDL_BUTTON_RIGHT]) { // Show item options
			slotToShowOptions = slotUnderMouse;
		}
	}
	else if (Input::mousePressed[SDL_BUTTON_LEFT] || Input::mousePressed[SDL_BUTTON_RIGHT]) { // Cancel selection / pickUp
		if (slotToShowOptions) {
			slotToShowOptions = nullptr;
		}
		else if (clickedSlot) {
			clickedSlot->item = clickedItem;
			clickedItem->setPositionX(clickedSlot->coord.x + itemSize.x / 2);
			clickedItem->setPositionY(clickedSlot->coord.y + itemSize.y / 2);
			clickedSlot = nullptr;
			clickedItem = nullptr;
		}
	}
}

void Inventory::drawInventory() {
	SDL_RenderCopy(Game::renderer, texture, NULL, &dstRectInv);

	if (slotToShowOptions) {
		// Show item options

	}
	else if (!clickedSlot && slotUnderMouse) {
		// Show item details

	}

	// Draw items
	for (int i = 0; i < slots.size(); i++)
		for (int j = 0; j < slots[i].size(); j++) {
			if (slots[i][j]->item)
				slots[i][j]->item->draw();
		}

	if (clickedItem)
		clickedItem->draw();
}

void Inventory::pickUpItem(Item* item) {
	InventorySlot* emptySlot = nullptr;

	for (int i = 0; i < slots.size() && !emptySlot; i++)
		for (int j = 0; j < slots[i].size() && !emptySlot; j++) {
			if (!slots[i][j]->item)
				emptySlot = slots[i][j];
		}

	if (emptySlot) {
		emptySlot->item = item;
		item->setPositionX(emptySlot->coord.x + itemSize.x / 2);
		item->setPositionY(emptySlot->coord.y + itemSize.y / 2);
	}
	else // Show message todo
		int kgu = 0;
}

void Inventory::dropItem(Item* item) {

}

Inventory::Inventory() : InventoryDetails(DataBase::inventoryDelails) {
	dstRectInv.w = width;
	dstRectInv.h = height;

	dstRectInv.x = 0;
	dstRectInv.y = 0;

	slots.resize(numerOfItemsInv.x);
	for (int i = 0; i < slots.size(); i++) {
		slots[i].resize(numerOfItemsInv.y);

		for (int j = 0; j < slots[i].size(); j++)
			slots[i][j] = new InventorySlot(startInventoryTab.x + i * (float(itemSize.x) + spaceBetweenItems),
				startInventoryTab.y + j * (float(itemSize.y) + spaceBetweenItems));
	}
}


Inventory::~Inventory() {

}
