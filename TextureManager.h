#pragma once
#include "SDL_image.h"
#include <unordered_map>


#define PLAYER 0
#define PROJECTILES 1
#define PLAYER_STATS 2
#define LEVEL_1 3



enum SingleTexture { WOOD_FLOOR , WALL_SIDE, WALL_TOP_T, WALL_TOP_R, WALL_TOP_B, WALL_TOP_L, DOORS};

class TextureManager{

public:
	static std::unordered_map <int, SDL_Texture*> textures;
	static std::unordered_map <SingleTexture, SDL_Rect> textureSrcRect;

	static void loadAllTextures();
	static void loadAllTextureSrcRect();
	static SDL_Texture* LoadTexture(const char*);

	TextureManager();
	~TextureManager();
};

