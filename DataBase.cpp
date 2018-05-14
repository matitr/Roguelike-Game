#include "DataBase.h"
#include "TextureManager.h"

InventoryDetails DataBase::inventoryDelails;

void DataBase::loadAllDataBases() {
	DataBase::loadInventoryDetails();
}

void DataBase::loadInventoryDetails() {
	DataBase::inventoryDelails.texture = TextureManager::textures[INVENTORY];

	DataBase::inventoryDelails.width = 431;
	DataBase::inventoryDelails.height = 927;

	DataBase::inventoryDelails.startInventoryTab.x = 80;
	DataBase::inventoryDelails.startInventoryTab.y = 614;
	DataBase::inventoryDelails.numerOfItemsInv.x = 6;
	DataBase::inventoryDelails.numerOfItemsInv.y = 5;

	DataBase::inventoryDelails.itemSize.x = 38;
	DataBase::inventoryDelails.itemSize.y = 38;

	DataBase::inventoryDelails.spaceBetweenItems = 9;
}

DataBase::DataBase() {

}


DataBase::~DataBase() {

}
