#include "TextureManager.h"
#include "Game.h"

std::unordered_map <int, SDL_Texture*> TextureManager::textures;

void TextureManager::loadAllTextures() {
	textures[PLAYER] = TextureManager::LoadTexture("Textures/player.png");
	textures[WOOD_FLOOR] = TextureManager::LoadTexture("Textures/woodFloor.png");
	textures[WATER] = TextureManager::LoadTexture("Textures/water.png");
	textures[STONE] = TextureManager::LoadTexture("Textures/stone.png");
	textures[PLAYER] = TextureManager::LoadTexture("Textures/player.png");
	textures[WALL_SIDE] = TextureManager::LoadTexture("Textures/wallSide.png");
	textures[WALL_TOP_T] = TextureManager::LoadTexture("Textures/wallTopT.png");
	textures[WALL_TOP_R] = TextureManager::LoadTexture("Textures/wallTopR.png");
	textures[WALL_TOP_B] = TextureManager::LoadTexture("Textures/wallTopB.png");
	textures[WALL_TOP_L] = TextureManager::LoadTexture("Textures/wallTopL.png");
	
	textures[PROJECTILES] = TextureManager::LoadTexture("Textures/projectiles.png");
	textures[DOORS] = TextureManager::LoadTexture("Textures/doors.png");
	textures[PLAYER_STATS] = TextureManager::LoadTexture("Textures/playerStats.png");
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