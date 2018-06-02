#include "DataBase.h"
#include "Item.h"
#include "Game.h"
#include "ActionsManager.h"
#include <string>
#include <iomanip>
#include <sstream>

InventoryDetails DataBase::inventoryDelails;
std::unordered_map<AnimationName, AnimationDetails> DataBase::animations;
std::unordered_map<TextColor, SDL_Color> DataBase::colors;
std::unordered_map<FontPurpose, TTF_Font*> DataBase::fonts;
std::unordered_map<UnitName, std::unordered_map<ActionType, std::array<AnimationDetails, Direction::Name::enum_size>>> DataBase::unitAnimations;

void DataBase::loadAllDataBases() {
	DataBase::loadInventoryDetails();
	DataBase::loadAnimationsDetails();
	DataBase::loadFontData();
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


	animations[AnimationName::PlayerWalkN] = { { 0,512 }, 8, 5, 8 };
	animations[AnimationName::PlayerWalkW] = { { 0,576 }, 8, 5, 8 };
	animations[AnimationName::PlayerWalkS] = { { 0,640 }, 8, 5, 8 };
	animations[AnimationName::PlayerWalkE] = { { 0,704 }, 8, 5, 8 };

	animations[AnimationName::SlashN] = { { 0,768 }, 5, 5, 5 };
	animations[AnimationName::SlashW] = { { 0,832 }, 5, 5, 5 };
	animations[AnimationName::SlashS] = { { 0,896 }, 5, 5, 5 };
	animations[AnimationName::SlashE] = { { 0,960 }, 5, 5, 5 };

	animations[AnimationName::DashN] = { { 0,512 }, 8, 2, 8 };
	animations[AnimationName::DashW] = { { 0,576 }, 8, 2, 8 };
	animations[AnimationName::DashS] = { { 0,640 }, 8, 2, 8 };
	animations[AnimationName::DashE] = { { 0,704 }, 8, 2, 8 };

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
	fonts[FontPurpose::ItemDescription] = TTF_OpenFont("Font/font.ttf", 18);

	colors[TextColor::ItemPassivesText] = { 0, 153, 255,255 };
	colors[TextColor::ItemType] = { 255, 204, 0,255 };

}

void DataBase::getPassiveText(int passive, float value, SDL_Texture*& firstTexture) {
	std::string passiveText = "";

	if (passive == StaticPassiveName::numbOfProjectiles) {
		passiveText = "Increase number of projectiles by " + std::to_string(int(value));
	}
	else if (passive == StaticPassiveName::pierceShots) {
		passiveText = "Increase pierce by " + std::to_string(int(value));
	}
	else if (passive == StaticPassiveName::homing) {
		passiveText = "Increase homing by " + std::to_string(int(value));
	}
	else if (passive == StaticPassiveName::unitSpeed) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << value;
		passiveText = "Increase movement speed by " + stream.str() + "%";
	}
	else if (passive == StaticPassiveName::chargeProjectiles) {
		passiveText = "Charge shots";
	}
	else if (passive == StaticPassiveName::projectileSpeed) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << value;
		passiveText = "Increase projectile speed by " + stream.str() + "%";
	}


	char text[100];
	strcpy_s(text, passiveText.c_str());
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(fonts[FontPurpose::ItemDescription], text, colors[TextColor::ItemPassivesText]);

	firstTexture = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
}

SDL_Texture* DataBase::getItemTypeText(enum ItemType itemType) {
	std::string itemTypeStr = "";

	 if (itemType == Universal)
		 itemTypeStr = "Universal";
	 else if (itemType == MainWeapon)
		 itemTypeStr = "Main Weapon";
	 else if (itemType == Active)
		 itemTypeStr = "Active";
	 else if (itemType == Passive)
		 itemTypeStr = "Passive";


	 char text[100];
	 strcpy_s(text, itemTypeStr.c_str());
	 SDL_Surface* surfaceMessage = TTF_RenderText_Blended(fonts[FontPurpose::ItemDescription], text, colors[TextColor::ItemType]);

	 SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	 SDL_FreeSurface(surfaceMessage);
	 return messageTexture;
 }

DataBase::DataBase() {

}


DataBase::~DataBase() {

}
