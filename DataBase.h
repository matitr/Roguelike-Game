#pragma once
#include "SDL.h"


struct InventoryDetails {
	SDL_Texture* texture;

	int width;
	int height;

	SDL_Point startInventoryTab;
	SDL_Point numerOfItemsInv;

	SDL_Point itemSize;

	int spaceBetweenItems;
};

struct ItemPassives{
	int numbOfProjectiles;

	int pierceShots;

	bool homing;

	bool explodeOnHit;




};

class DataBase {
	

public:
	static InventoryDetails inventoryDelails;


	static void loadAllDataBases();
	static void loadInventoryDetails();

	DataBase();
	~DataBase();
};

