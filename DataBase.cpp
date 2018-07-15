#include "DataBase.h"
#include "Item.h"
#include "Game.h"
#include "ActionsManager.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>

#define ITEM_DESCRIPTION_PRECISION 1

InventoryDetails DataBase::inventoryDelails;
std::unordered_map<AnimationName, AnimationDetails> DataBase::animations;
std::unordered_map<TextColor, SDL_Color> DataBase::colors;
std::unordered_map<FontPurpose, SDL_RWops*> DataBase::RWops;
std::unordered_map<FontPurpose, TTF_Font*> DataBase::fonts;
std::unordered_map<UnitName, std::unordered_map<ActionType, std::array<AnimationDetails, Direction::Name::enum_size>>> DataBase::unitAnimations;
std::unordered_map<ItemName::Name, ItemDetails> DataBase::items;
ItemPassivesLimits DataBase::passivesLimits;

void DataBase::loadAllDataBases() {
	DataBase::loadInventoryDetails();
	DataBase::loadAnimationsDetails();
	DataBase::loadFontData();
	DataBase::loadItems();
	DataBase::loadPassivesLimits();
}

void DataBase::loadInventoryDetails() {
	DataBase::inventoryDelails.texture = TextureManager::textures[TextureFile::INVENTORY];

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
		inventoryDelails.eqDetails.push_back({ ItemType::Passive,
			{ slot.x,slot.y + (slot.h + space) * i,inventoryDelails.slotSize.x,inventoryDelails.slotSize.x } });

}

void DataBase::loadAnimationsDetails() {
	animations[AnimationName::Projectile] = { {0,0}, 4, 7, 4 };
	animations[AnimationName::Projectile2] = { { 0,64 }, 4, 7, 4 };

	animations[AnimationName::ChestOpening] = { { 0,0 }, 3, 30, 3 };
	animations[AnimationName::CoinSpin] = { { 0,0 }, 8, 5, 8 };

	unitAnimations[UnitName::Unit][Walk][Direction::N] = { { 0,512 }, 8, 5, 8 };
	unitAnimations[UnitName::Unit][Walk][Direction::W] = { { 0,576 }, 8, 5, 8 };
	unitAnimations[UnitName::Unit][Walk][Direction::S] = { { 0,640 }, 8, 5, 8 };
	unitAnimations[UnitName::Unit][Walk][Direction::E] = { { 0,704 }, 8, 5, 8 };

	unitAnimations[UnitName::Unit][Attack][Direction::N] = { { 0,768 }, 5, 5, 5 };
	unitAnimations[UnitName::Unit][Attack][Direction::W] = { { 0,832 }, 5, 5, 5 };
	unitAnimations[UnitName::Unit][Attack][Direction::S] = { { 0,896 }, 5, 5, 5 };
	unitAnimations[UnitName::Unit][Attack][Direction::E] = { { 0,960 }, 5, 5, 5 };

	unitAnimations[UnitName::Unit][Dash][Direction::N] = { { 0,512 }, 8, 2, 8 };
	unitAnimations[UnitName::Unit][Dash][Direction::W] = { { 0,576 }, 8, 2, 8 };
	unitAnimations[UnitName::Unit][Dash][Direction::S] = { { 0,640 }, 8, 2, 8 };
	unitAnimations[UnitName::Unit][Dash][Direction::E] = { { 0,704 }, 8, 2, 8 };

	unitAnimations[UnitName::Unit][AttackProj][Direction::N] = { { 0,1024 }, 13, 4, 13 };
	unitAnimations[UnitName::Unit][AttackProj][Direction::W] = { { 0,1088 }, 13, 4, 13 };
	unitAnimations[UnitName::Unit][AttackProj][Direction::S] = { { 0,1152 }, 13, 4, 13 };
	unitAnimations[UnitName::Unit][AttackProj][Direction::E] = { { 0,1216 }, 13, 4, 13 };
}

void DataBase::loadFontData() {
	TTF_Init();
	RWops[FontPurpose::ItemDescription] = SDL_RWFromFile("Font/font.ttf", "r");
	RWops[FontPurpose::GameEndResult] = SDL_RWFromFile("Font/font.ttf", "r");
	RWops[FontPurpose::MenuButtonsText] = SDL_RWFromFile("Font/font.ttf", "r");

	fonts[FontPurpose::ItemDescription] = TTF_OpenFontRW(RWops[FontPurpose::ItemDescription], 0, 18);
	fonts[FontPurpose::GameEndResult] = TTF_OpenFontRW(RWops[FontPurpose::GameEndResult], 0, 64);
	fonts[FontPurpose::MenuButtonsText] = TTF_OpenFontRW(RWops[FontPurpose::MenuButtonsText], 0, 32);

	for (auto it = fonts.begin(); it != fonts.end(); it++)
		if (!it->second)
			std::cout << "Error while opening font" << std::endl;
	
	colors[TextColor::ItemStatText] = { 0, 153, 255,255 };
	colors[TextColor::ItemPassive] = { 249, 124, 0, 255 };
	colors[TextColor::ItemType] = { 255, 204, 0,255 };
	colors[TextColor::MenuButtonText] = { 255, 255, 255,255 };
}

void DataBase::loadItems() {
	items[ItemName::Item1].type = ItemType::MainWeapon;
	items[ItemName::Item1].passives[StaticPassiveName::damage] = 10;
	items[ItemName::Item1].passives[StaticPassiveName::chargeProjectiles] = 1;

	items[ItemName::Item2].type = ItemType::MainWeapon;
	items[ItemName::Item2].passives[StaticPassiveName::attackSpeedMult] = 0.5;

	items[ItemName::Item3].type = ItemType::MainWeapon;
	items[ItemName::Item3].passives[StaticPassiveName::attackSpeedMult] = 0.7;
	items[ItemName::Item3].passives[StaticPassiveName::numbOfProjectiles] = 72;
	items[ItemName::Item3].passives[StaticPassiveName::unitSpeedMult] = 0.5;
	items[ItemName::Item3].passiveName = PassiveName::OnEnemyKillMoveSpeed;

	items[ItemName::Item4].type = ItemType::Passive;
	items[ItemName::Item4].passives[StaticPassiveName::attackSpeedMult] = 2;

}

void DataBase::loadPassivesLimits() {
	passivesLimits[StaticPassiveName::hp] = { 0,3000 };
	passivesLimits[StaticPassiveName::hpMax] = { 0,3000 };
	passivesLimits[StaticPassiveName::damage] = { -10,3000 };
	passivesLimits[StaticPassiveName::damageMult] = { -60,300 };
	passivesLimits[StaticPassiveName::numbOfProjectiles] = { 1,5 };
	passivesLimits[StaticPassiveName::pierceShots] = { 0,5 };
	passivesLimits[StaticPassiveName::chargeProjectiles] = { 0,1 };
	passivesLimits[StaticPassiveName::homing] = { -10,25 };
	passivesLimits[StaticPassiveName::projectileSpeedMult] = { -50,300 };
	passivesLimits[StaticPassiveName::projectileSizeMult] = { -50,300 };
	passivesLimits[StaticPassiveName::attackSpeedMult] = { -80,300 };
	passivesLimits[StaticPassiveName::unitSpeed] = { 1,9 };
	passivesLimits[StaticPassiveName::unitSpeedMult] = { -70,300 };
}

void DataBase::getPassiveText(int passive, float value, SDL_Texture*& firstTexture) {
	std::string passiveText = "";

	if (passive == StaticPassiveName::numbOfProjectiles) {
		passiveText = "Increases number of projectiles by " + std::to_string(int(value));
	}
	else if (passive == StaticPassiveName::pierceShots) {
		passiveText = "Increases pierce by " + std::to_string(int(value));
	}
	else if (passive == StaticPassiveName::homing) {
		passiveText = "Increases homing by " + std::to_string(int(value));
	}
	else if (passive == StaticPassiveName::unitSpeed) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(ITEM_DESCRIPTION_PRECISION) << value;
		passiveText = "Increases movement speed by " + stream.str();
	}
	else if (passive == StaticPassiveName::unitSpeedMult) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(ITEM_DESCRIPTION_PRECISION) << value * 100;
		passiveText = "Increases movement speed by " + stream.str() + "%";
	}
	else if (passive == StaticPassiveName::chargeProjectiles) {
		passiveText = "Charge shots";
	}
	else if (passive == StaticPassiveName::projectileSpeedMult) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(ITEM_DESCRIPTION_PRECISION) << value * 100;
		passiveText = "Increases projectile speed by " + stream.str() + "%";
	}
	else if (passive == StaticPassiveName::damage) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(ITEM_DESCRIPTION_PRECISION) << value;
		passiveText = "Increases damage by " + stream.str();
	}
	else if (passive == StaticPassiveName::damageMult) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(ITEM_DESCRIPTION_PRECISION) << value * 100;
		passiveText = "Increases damage by " + stream.str() + "%";
	}
	else if (passive == StaticPassiveName::projectileSizeMult) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(ITEM_DESCRIPTION_PRECISION) << value * 100;
		passiveText = "Increases projectile size by " + stream.str() + "%";
	}
	else if (passive == StaticPassiveName::attackSpeedMult) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(ITEM_DESCRIPTION_PRECISION) << value * 100;
		passiveText = "Increases attack speed by " + stream.str() + "%";
	}
	else if (passive == StaticPassiveName::hp) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(ITEM_DESCRIPTION_PRECISION) << value;
		passiveText = "Heal for " + stream.str();
	}
	else if (passive == StaticPassiveName::hpMax) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(ITEM_DESCRIPTION_PRECISION) << value;
		passiveText = "Increases max health by " + stream.str();
	}

	char text[100];
	strcpy_s(text, passiveText.c_str());
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(fonts[FontPurpose::ItemDescription], text, colors[TextColor::ItemStatText]);

	firstTexture = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
}

SDL_Texture* DataBase::getItemTypeText(enum ItemType itemType) {
	std::string itemTypeStr = "";

	 if (itemType == ItemType::Universal)
		 itemTypeStr = "Universal";
	 else if (itemType == ItemType::MainWeapon)
		 itemTypeStr = "Main Weapon";
	 else if (itemType == ItemType::Active)
		 itemTypeStr = "Active";
	 else if (itemType == ItemType::Passive)
		 itemTypeStr = "Passive";


	 char text[100];
	 strcpy_s(text, itemTypeStr.c_str());
	 SDL_Surface* surfaceMessage = TTF_RenderText_Blended(fonts[FontPurpose::ItemDescription], text, colors[TextColor::ItemType]);

	 SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	 SDL_FreeSurface(surfaceMessage);
	 return messageTexture;
 }

void DataBase::clearData() {
	animations.clear();
	colors.clear();

	fonts.clear();

	unitAnimations.clear();
	items.clear();

	for (auto it = RWops.begin(); it != RWops.end(); it++)
		SDL_RWclose(it->second);
}

DataBase::DataBase() {

}


DataBase::~DataBase() {

}
