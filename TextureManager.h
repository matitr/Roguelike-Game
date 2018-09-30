#pragma once
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <unordered_map>


namespace Direction {
	enum Name { N, E, S, W, enum_size };
}

namespace ItemName {
	enum Name { Item1, Item2, Item3, Item4, Item5, Item6, enum_size };
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

enum class SingleFieldTexture { WOOD_FLOOR, FLOOR_NEAR_WALL_N, FLOOR_NEAR_WALL_E, FLOOR_NEAR_WALL_S, FLOOR_NEAR_WALL_W,
	FLOOR_NEAR_WALL_SW, FLOOR_NEAR_WALL_SE, FLOOR_NEAR_WALL_NW, FLOOR_NEAR_WALL_NE,
	FLOOR_NEAR_COLUMN_SW, FLOOR_NEAR_COLUMN_SE, FLOOR_NEAR_COLUMN_NW, FLOOR_NEAR_COLUMN_NE,
	WALL_FRONT0, WALL_FRONT1, WALL_TOP_T, WALL_TOP_R, WALL_TOP_B, WALL_TOP_L, WALL_CORNER_LT, WALL_CORNER_RT, WALL_CORNER_LB, WALL_CORNER_RB, 
	WALL_COLUMN_SW, WALL_COLUMN_SE, WALL_COLUMN_NW, WALL_COLUMN_NE,
	WALL_TOP,
	DOORS};

enum class SingleTexture { Chest, Coin, Teleport, TeleportOff, TeleportOn, PlayerT, UnitT, ProjectileT };
enum class TextureAnimation { ChestOpening, CoinSpin };



class TextureManager{

public:
	static std::unordered_map <TextureFile, SDL_Texture*> textures;
	static std::unordered_map <SingleFieldTexture, SDL_Rect> fieldTextureSrcRect;

	static std::unordered_map <SingleTexture, TextureInfo> textureParameters;
	static std::unordered_map <ItemName::Name, ItemTextureInfo> itemTextureDetails;


	static void loadAllTextures();
	static void loadAllTextureSrcRect();
	static SDL_Texture* LoadTexture(const char*);

	static SDL_Texture* textureFromText(std::string textStr, TTF_Font* font, SDL_Color& color, int maxTextWidth);

	static void clearData();

	TextureManager();
	~TextureManager();
};

