#pragma once
#ifndef DATA_BASE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include <unordered_map>
#include "TextureManager.h"
#include "Item.h"
#include "Passive.h"


enum class ItemType { Universal, MainWeapon, Active, Passive };

enum class AnimationName { Projectile, Projectile2, ChestOpening, CoinSpin };


enum class TextColor { ItemStatText, ItemPassive, ItemType, MenuButtonText, CombatTextDamage, CombatTextFireDmg, CombatTextHeal };
enum class FontPurpose { ItemDescription, GameEndResult, MenuButtonsText, CombatTextDmg };

enum class UnitName { Unit, Player };


struct TextureInfo;
enum ActionType;

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
	SDL_Point firstFrame;
	int frames;
	int frameTime;
	int framesInRow;
};

struct ItemDetails {
	ItemType type;
	ItemPassives passives;
	PassiveName passiveName;
};

struct Limits_t {
	float min;
	float max;
};

typedef std::array<Limits_t, StaticPassiveName::enum_size> ItemPassivesLimits;

class DataBase {
	

public:
	static InventoryDetails inventoryDelails;
	static std::unordered_map<AnimationName, AnimationDetails> animations;
	static std::unordered_map<TextColor, SDL_Color> colors;
	static std::unordered_map<FontPurpose, SDL_RWops*> RWops;
	static std::unordered_map<FontPurpose, TTF_Font*> fonts;

	static std::unordered_map<UnitName, std::unordered_map<ActionType, std::array<AnimationDetails, Direction::Name::enum_size>>> unitAnimations;
	static std::unordered_map<ItemName::Name, ItemDetails> items;
	static ItemPassivesLimits passivesLimits;

	static void loadAllDataBases();
	static void loadInventoryDetails();
	static void loadAnimationsDetails();
	static void loadFontData();
	static void loadItems();
	static void loadPassivesLimits();

	static void getPassiveText(int passive, float value, SDL_Texture*& first);
	static SDL_Texture* getItemTypeText(enum ItemType);

	static void clearData();

	DataBase();
	~DataBase();
};



#endif // !DATA_BASE_H