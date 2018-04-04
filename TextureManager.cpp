#include "TextureManager.h"
#include "Game.h"

std::unordered_map <int, SDL_Texture*> TextureManager::textures;
std::unordered_map <SingleTexture, SDL_Rect> TextureManager::textureSrcRect;

void TextureManager::loadAllTextures() {
	textures[PLAYER] = TextureManager::LoadTexture("Textures/player.png");
	
	textures[PROJECTILES] = TextureManager::LoadTexture("Textures/projectiles.png");
	textures[PLAYER_STATS] = TextureManager::LoadTexture("Textures/playerStats.png"); 

	textures[LEVEL_1] = TextureManager::LoadTexture("Textures/level_1.png");

	TextureManager::loadAllTextureSrcRect();
}

void TextureManager::loadAllTextureSrcRect() { // srcRect = { x, y, w, h }
	int fieldSize = 60;

	textureSrcRect[WOOD_FLOOR] = { fieldSize * 0,fieldSize * 0,fieldSize,fieldSize };
	textureSrcRect[DOORS] = { fieldSize * 1,fieldSize * 0,fieldSize,fieldSize };
	textureSrcRect[WALL_SIDE] = { fieldSize * 2,fieldSize * 0,fieldSize,fieldSize };
	textureSrcRect[WALL_TOP_T] = { fieldSize * 0,fieldSize * 1,fieldSize,fieldSize };
	textureSrcRect[WALL_TOP_R] = { fieldSize * 1,fieldSize * 1,fieldSize,fieldSize };
	textureSrcRect[WALL_TOP_B] = { fieldSize * 2,fieldSize * 1,fieldSize,fieldSize };
	textureSrcRect[WALL_TOP_L] = { fieldSize * 3,fieldSize * 1,fieldSize,fieldSize };
}

SDL_Texture* TextureManager::LoadTexture(const char* dir) {
	SDL_Surface* surface = IMG_Load(dir);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

TextureManager::TextureManager() {

}


TextureManager::~TextureManager() {

}