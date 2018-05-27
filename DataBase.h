#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include <unordered_map>


enum ItemType { Universal, MainWeapon, Active, Passive };
enum class AnimationName { Projectile };
enum class TextColor { ItemPassivesText, ItemType };
enum class FontPurpose { ItemDescription };

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
	static std::unordered_map<TextColor, SDL_Color> colors;
	static std::unordered_map<FontPurpose, TTF_Font*> fonts;


	static void loadAllDataBases();
	static void loadInventoryDetails();
	static void loadAnimationsDetails();
	static void loadFontData();

	static void getPassiveText(int passive, float value, SDL_Texture*& first);
	static SDL_Texture* getItemTypeText(enum ItemType);

	DataBase();
	~DataBase();
};

