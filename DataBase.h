#pragma once
#include "SDL.h"
#include <vector>
#include <unordered_map>


enum ItemType { Universal, MainWeapon, Active, Passive };
enum class AnimationName { Projectile };

struct InventoryDetails {

	struct EquippedDetails {
		ItemType itemType;
		SDL_Rect slotRect;
	};

	SDL_Texture* texture;

	int width;
	int height;

	SDL_Point startInventoryTab;
	SDL_Point numerOfSlots;
	SDL_Point slotSize;
	int spaceBetweenSlots;

	std::vector <EquippedDetails> eqDetails;
};

struct AnimationDetails {
	SDL_Texture* txt;
	int width;
	int height;
	int yIter;
	int frames;
	int frameTime;
};


class DataBase {
	

public:
	static InventoryDetails inventoryDelails;
	static std::unordered_map<AnimationName, AnimationDetails> animations;

	static void loadAllDataBases();
	static void loadInventoryDetails();
	static void loadAnimationsDetails();

	static std::string getPassiveText(int passive, float value);
	static std::string getItemTypeText(enum ItemType);

	DataBase();
	~DataBase();
};

