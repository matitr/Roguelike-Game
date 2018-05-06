#pragma once
#include "SDL_image.h"
#include <unordered_map>



struct Rect {
	int w, h;
};

//  { SDL_Rect srcRect = { x, y, w, h }, Rect dstRect = { w, h }, SDL_Texture* texture };
struct TextureInfo { 
	SDL_Rect srcRect;
	Rect dstRect;
	SDL_Texture* texture;
};

enum TextureFromFile { PLAYER, PROJECTILES, PLAYER_STATS, LEVEL_1, OBJECTS, COIN, CHEST };
enum SingleFieldTexture { WOOD_FLOOR , WALL_SIDE, WALL_TOP_T, WALL_TOP_R, WALL_TOP_B, WALL_TOP_L, DOORS};
enum SingleTexture { Chest, Coin, Teleport, TeleportOff, TeleportOn };
enum TextureAnimation { ChestOpening, CoinSpin };

class TextureManager{

public:
	static std::unordered_map <TextureFromFile, SDL_Texture*> textures;
	static std::unordered_map <SingleFieldTexture, SDL_Rect> fieldTextureSrcRect;

	static std::unordered_map <SingleTexture, TextureInfo> textureParameters;


	static void loadAllTextures();
	static void loadAllTextureSrcRect();
	static SDL_Texture* LoadTexture(const char*);

	TextureManager();
	~TextureManager();
};

