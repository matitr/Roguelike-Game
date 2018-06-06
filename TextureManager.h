#pragma once
#include "SDL_image.h"
#include <unordered_map>


namespace Direction {
	enum Name { N, E, S, W, enum_size };
}

namespace ItemName {
	enum Name { Item1, Item2, Item3, Item4, Item5, Item6, Item7, Item8, enum_size };
}

struct Rect {
	int w, h;
};

//  { SDL_Rect srcRect = { x, y, w, h }, Rect dstRect = { w, h }, SDL_Texture* texture };
struct TextureInfo { 
	SDL_Rect srcRect;
	Rect dstRect;
	SDL_Texture* texture;
};

struct ItemTextureInfo {
	SDL_Rect srcRect;
	SDL_Texture* texture;
};


enum class TextureFile { PLAYER, PROJECTILES, PLAYER_STATS, LEVEL_1, OBJECTS, COIN, CHEST, INVENTORY, UNIT, Items };

enum SingleFieldTexture { WOOD_FLOOR ,
	WALL_SIDE0, WALL_SIDE1, WALL_TOP_T, WALL_TOP_R, WALL_TOP_B, WALL_TOP_L, WALL_CORSEN_LT, WALL_CORSEN_RT, WALL_CORSEN_LB, WALL_CORSEN_RB, 
	DOORS};

enum SingleTexture { Chest, Coin, Teleport, TeleportOff, TeleportOn, PlayerT, UnitT, ProjectileT };
enum TextureAnimation { ChestOpening, CoinSpin };



class TextureManager{

public:
	static std::unordered_map <TextureFile, SDL_Texture*> textures;
	static std::unordered_map <SingleFieldTexture, SDL_Rect> fieldTextureSrcRect;

	static std::unordered_map <SingleTexture, TextureInfo> textureParameters;
	static std::unordered_map <ItemName::Name, ItemTextureInfo> itemTextureDetails;


	static void loadAllTextures();
	static void loadAllTextureSrcRect();
	static SDL_Texture* LoadTexture(const char*);

	TextureManager();
	~TextureManager();
};

