#pragma once
#include "SDL_image.h"
#include <unordered_map>


#define WOOD_FLOOR 0
#define WATER 1
#define STONE 2
#define PLAYER 3
#define WALL_SIDE 4
#define WALL_TOP_T 5
#define WALL_TOP_R 6
#define WALL_TOP_B 7
#define WALL_TOP_L 8
#define PROJECTILES 9
#define DOORS 10
#define PLAYER_STATS 11


class TextureManager{

public:
	static std::unordered_map <int, SDL_Texture*> textures;
	static void loadAllTextures();
	static SDL_Texture* LoadTexture(const char*);

	TextureManager();
	~TextureManager();

};

