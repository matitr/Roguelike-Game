#include "Inventory.h"
#include "Game.h"
#include "Input.h"
#include "Item.h"
#include "Map.h"
#include "Player.h"
#include "DataBase.h"
#include "PassivesManager.h"


void Inventory::close() {
	if (clickedSlot) {
		clickedSlot->item = clickedItem;
		clickedItem->setPositionX(clickedSlot->rect.x + details.slotSize.x / 2);
		clickedItem->setPositionY(clickedSlot->rect.y + details.slotSize.y / 2);
	}

	invIsOpened = false;
	clickedSlot = nullptr;
	clickedItem = nullptr;
	slotUnderMouse = nullptr;
}

void Inventory::update(Map* map, Player* player) {
	if (!invIsOpened || map->currentRoom()->battle) {
		invIsOpened = false;
		return;
	}

	int mouseX = Input::mousePosX, mouseY = Input::mousePosY;
	double x = (mouseX - dstRectInv.x - details.startInventoryTab.x) / (float(details.slotSize.x) + float(details.spaceBetweenSlots));
	double y = (mouseY - dstRectInv.y - details.startInventoryTab.y) / (float(details.slotSize.y) + float(details.spaceBetweenSlots));
	slotUnderMouse = nullptr;

	// Mouse on inventory
	if (mouseX >= dstRectInv.x && mouseX <= dstRectInv.x + dstRectInv.w && mouseY >= dstRectInv.y && mouseY <= dstRectInv.y + dstRectInv.h)
		player->cancelAttack();

	if (clickedSlot && clickedItem) {
		clickedItem->setPositionX(mouseX);
		clickedItem->setPositionY(mouseY);
	}

	// selected item in inventory
	if (x >= 0 && x < details.numerOfSlots.x && y >= 0 && y < details.numerOfSlots.y
		&& (x - int(x)) <= float(details.slotSize.x) / (details.slotSize.x + details.spaceBetweenSlots) 
		&& (y - int(y)) <= float(details.slotSize.y) / (details.slotSize.y + details.spaceBetweenSlots)) {

		slotUnderMouse = inventorySlots[int(x)][int(y)];
	}

	slotUnderMouseEq = false;
	for (int i = 0; i < equippedSlots.size(); i++) { // Check if mouse is on equippedSlot
		if (mouseX >= equippedSlots[i]->rect.x && mouseX <= equippedSlots[i]->rect.x + equippedSlots[i]->rect.w
			&& mouseY >= equippedSlots[i]->rect.y && mouseY <= equippedSlots[i]->rect.y + equippedSlots[i]->rect.h) {

			slotUnderMouseEq = true;
			slotUnderMouse = equippedSlots[i];
		}
	}

	updateFocusOnSlot(player);
}

void Inventory::updateFocusOnSlot(Unit* unit) {
	if (slotUnderMouse) {
		if (Input::mousePressed[SDL_BUTTON_LEFT]) { // Move item
			if (!clickedSlot && slotUnderMouse->item) { // First click
				clickedSlot = slotUnderMouse;
				clickedItem = slotUnderMouse->item;
				slotUnderMouse->item = nullptr;
				clickedSlotEq = (slotUnderMouseEq) ? true : false;
			}
			else if (clickedSlot) { // Move item
				if (!slotUnderMouseEq || (slotUnderMouse->itemType == clickedItem->itemType())) { // Check item type
					if (clickedSlotEq && !slotUnderMouseEq)
						unitPassivesManager->unequipItem(clickedItem);
					else if (!clickedSlotEq && slotUnderMouseEq)
						unitPassivesManager->equipItem(clickedItem, unit);
					if (slotUnderMouse->item) {
						slotUnderMouse->item->setPositionX(clickedSlot->rect.x + clickedSlot->rect.w / 2);
						slotUnderMouse->item->setPositionY(clickedSlot->rect.y + clickedSlot->rect.h / 2);
						if (clickedSlotEq && !slotUnderMouseEq)
							unitPassivesManager->equipItem(slotUnderMouse->item, unit);
						else if (!clickedSlotEq && slotUnderMouseEq)
							unitPassivesManager->unequipItem(slotUnderMouse->item);
					}
					clickedSlot->item = slotUnderMouse->item;
					slotUnderMouse->item = clickedItem;
					clickedItem->setPositionX(slotUnderMouse->rect.x + slotUnderMouse->rect.w / 2);
					clickedItem->setPositionY(slotUnderMouse->rect.y + slotUnderMouse->rect.h / 2);
					clickedSlot = nullptr;
					clickedItem = nullptr;
				}
			}
		}
		else if (Input::mousePressed[SDL_BUTTON_RIGHT]) { // Equip / Unequip
			if (slotUnderMouse->item) {
				if (slotUnderMouseEq) {
					unequipItem(slotUnderMouse);
				}
				else { // Slot in inventory
					equipItem(slotUnderMouse, unit);
				}
			}
		}
	}
	else if (Input::mousePressed[SDL_BUTTON_LEFT] || Input::mousePressed[SDL_BUTTON_RIGHT]) { // Cancel selection / pickUp
		if (clickedSlot) {
			clickedSlot->item = clickedItem;
			clickedItem->setPositionX(clickedSlot->rect.x + clickedSlot->rect.w / 2);
			clickedItem->setPositionY(clickedSlot->rect.y + clickedSlot->rect.h / 2);
			clickedSlot = nullptr;
			clickedItem = nullptr;
		}
	}
}

void Inventory::draw() {
	SDL_RenderCopy(Game::renderer, details.texture, NULL, &dstRectInv);

	// Draw inventory items
	for (int i = 0; i < inventorySlots.size(); i++)
		for (int j = 0; j < inventorySlots[i].size(); j++) {
			if (inventorySlots[i][j]->item)
				inventorySlots[i][j]->item->draw();
		}

	// Draw equipped items
	for (int i = 0; i < equippedSlots.size(); i++)
		if (equippedSlots[i]->item)
			equippedSlots[i]->item->draw();

	if (clickedItem)
		clickedItem->draw();

	if (!clickedSlot && slotUnderMouse) {
		// Show item details
		if (slotUnderMouse->item)
			slotUnderMouse->item->drawDescription(slotUnderMouse->rect, windowResolution);
	}

	highlightAllSlots();
}

void Inventory::pickUpItem(Item* item) {
	InventorySlot* emptySlot = nullptr;
	int i = 0; // Find empty slot
	for (int j = 0; j < inventorySlots[i].size() && !emptySlot; j++) {
		for (i = 0; i < inventorySlots.size() && !emptySlot; i++) {
			if (!inventorySlots[i][j]->item && inventorySlots[i][j] != clickedSlot)
				emptySlot = inventorySlots[i][j];
		}
		i = 0;
	}

	if (emptySlot) {
		emptySlot->item = item;
		item->setPositionX(emptySlot->rect.x + details.slotSize.x / 2);
		item->setPositionY(emptySlot->rect.y + details.slotSize.y / 2);
	}
	else // Show message todo
		int kgu = 0;
}

void Inventory::dropItem(Item* item) {

}	

void Inventory::equipItem(InventorySlot* itemSlotToEquip, Unit* unit) {
	InventorySlot* toEquip = nullptr;

	for (int i = 0; i < equippedSlots.size(); i++) // Find slot
		if (!equippedSlots[i]->item && equippedSlots[i]->itemType == itemSlotToEquip->item->itemType()) {
			toEquip = equippedSlots[i];
			break;
		}

	if (toEquip) {
		unitPassivesManager->equipItem(itemSlotToEquip->item, unit);
		toEquip->item = itemSlotToEquip->item;
		toEquip->item->setPositionX(toEquip->rect.x + toEquip->rect.w / 2);
		toEquip->item->setPositionY(toEquip->rect.y + toEquip->rect.h / 2);
		itemSlotToEquip->item = nullptr;
	}

//	calculatePassives();
}

void Inventory::unequipItem(InventorySlot* itemSlotToUnequip) {
	InventorySlot* toUnequip = nullptr;

	int i = 0;
	for (int j = 0; j < inventorySlots[i].size() && !toUnequip; j++) { // Find slot
		for (i = 0; i < inventorySlots.size() && !toUnequip; i++) {
			if (!inventorySlots[i][j]->item)
				toUnequip = inventorySlots[i][j];
		}
		i = 0;
	}

	if (toUnequip) {
		unitPassivesManager->unequipItem(itemSlotToUnequip->item);
		toUnequip->item = itemSlotToUnequip->item;
		toUnequip->item->setPositionX(toUnequip->rect.x + toUnequip->rect.w / 2);
		toUnequip->item->setPositionY(toUnequip->rect.y + toUnequip->rect.h / 2);
		itemSlotToUnequip->item = nullptr;
	}

//	calculatePassives();
}

void Inventory::calculatePassives() {
	/*
	// Default values
	for (int i = 0; i < staticPassives.size(); i++)
		staticPassives[i] = 0;

	for (int i = 0; i < equippedSlots.size(); i++)
		if (equippedSlots[i]->item) {

			// Add values
			for (int it_passive = 0; it_passive < staticPassives.size(); it_passive++) {
				staticPassives[it_passive] += equippedSlots[i]->item->getStaticPassives()[it_passive];
			}
		}

	// Limit passives values
	for (int i = 0; i < StaticPassiveName::enum_size; i++) {
		if (staticPassives[i] < DataBase::passivesLimits[i].min)
			staticPassives[i] = DataBase::passivesLimits[i].min;
		else if (staticPassives[i] > DataBase::passivesLimits[i].max)
			staticPassives[i] = DataBase::passivesLimits[i].max;
	}
	*/
}

void Inventory::highlightAllSlots() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, rand() % 30 + 70, 255);
	SDL_Rect r;

	// Inventory
	r.w = details.slotSize.x;
	r.h = details.slotSize.y;

	for (int i = 0; i < inventorySlots.size(); i++) {
		for (int j = 0; j < inventorySlots[i].size(); j++) {
			r.x = inventorySlots[i][j]->rect.x;
			r.y = inventorySlots[i][j]->rect.y;

			SDL_RenderDrawRect(Game::renderer, &r);
		}
	}

	// Equipped
	for (int i = 0; i < equippedSlots.size(); i++) {
		r.x = equippedSlots[i]->rect.x;
		r.y = equippedSlots[i]->rect.y;
		r.w = equippedSlots[i]->rect.w;
		r.h = equippedSlots[i]->rect.h;

		SDL_RenderDrawRect(Game::renderer, &r);

	}
}

Inventory::Inventory(PassivesManager* passivesManager, SDL_Point& _windowResolution) : details(DataBase::inventoryDelails), unitPassivesManager(passivesManager), windowResolution(_windowResolution){
	dstRectInv.w = details.width;
	dstRectInv.h = details.height;

	dstRectInv.x = 0;
	dstRectInv.y = 0;

	dstRectInv.x = _windowResolution.x - dstRectInv.w;
	dstRectInv.y = (_windowResolution.y - dstRectInv.h) / 2;

	// Set inventory slots
	inventorySlots.resize(details.numerOfSlots.x);
	for (int i = 0; i < inventorySlots.size(); i++) {
		inventorySlots[i].resize(details.numerOfSlots.y);

		for (int j = 0; j < inventorySlots[i].size(); j++)
			inventorySlots[i][j] = new InventorySlot(dstRectInv.x + details.startInventoryTab.x + i * ((details.slotSize.x) + details.spaceBetweenSlots),
				dstRectInv.y + details.startInventoryTab.y + j * ((details.slotSize.y) + details.spaceBetweenSlots), details.slotSize);
	}

	// Set equipped slots
	size_t numbSlits = details.eqDetails.size();
	for (int i = 0; i < numbSlits; i++) {
		equippedSlots.push_back(new InventorySlot(details.eqDetails[i].itemType, details.eqDetails[i].slotRect, dstRectInv));
	}
}


Inventory::~Inventory() {
	for (int i = 0; i < inventorySlots.size(); i++)
		for (int j = 0; j < inventorySlots[i].size(); j++) {
			delete inventorySlots[i][j];
		}

	for (int i = 0; i < equippedSlots.size(); i++)
		delete equippedSlots[i];

	if (clickedItem)
		delete clickedItem;
}
