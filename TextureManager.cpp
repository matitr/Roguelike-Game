#include "TextureManager.h"
#include "Game.h"

std::unordered_map <TextureFromFile, SDL_Texture*> TextureManager::textures;
std::unordered_map <SingleFieldTexture, SDL_Rect> TextureManager::fieldTextureSrcRect;
std::unordered_map <SingleTexture, TextureInfo> TextureManager::textureParameters;

void TextureManager::loadAllTextures() {
	textures[PLAYER] = TextureManager::LoadTexture("Textures/player.png");
	
	textures[PROJECTILES] = TextureManager::LoadTexture("Textures/projectiles.png");
	textures[PLAYER_STATS] = TextureManager::LoadTexture("Textures/playerStats.png"); 

	textures[LEVEL_1] = TextureManager::LoadTexture("Textures/level_1.png");
	textures[OBJECTS] = TextureManager::LoadTexture("Textures/objects.png");
	textures[COIN] = TextureManager::LoadTexture("Textures/coin.png");
	textures[CHEST] = TextureManager::LoadTexture("Textures/chest.png");
	textures[INVENTORY] = TextureManager::LoadTexture("Textures/inventory.png");

	TextureManager::loadAllTextureSrcRect();
}

void TextureManager::loadAllTextureSrcRect() { // srcRect = { x, y, w, h }
	int fieldSize = 60;

	fieldTextureSrcRect[WOOD_FLOOR] = { fieldSize * 0,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[DOORS] = { fieldSize * 1,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[WALL_SIDE] = { fieldSize * 2,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[WALL_TOP_T] = { fieldSize * 0,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[WALL_TOP_R] = { fieldSize * 1,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[WALL_TOP_B] = { fieldSize * 2,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[WALL_TOP_L] = { fieldSize * 3,fieldSize * 1,fieldSize,fieldSize };

	// Parameters:
	//  { SDL_Rect srcRect = { x, y, w, h }, Rect dstRect = { w, h }, SDL_Texture* texture };
	textureParameters[Teleport] = { { 0, 0, 468, 468 },{ 120,120 }, textures[OBJECTS] };
	textureParameters[TeleportOff] = { { 470,0,468,468 },{ 120,120 }, textures[OBJECTS] };
	textureParameters[TeleportOn] = { { 940,0,468,468 },{ 120,120 }, textures[OBJECTS] };

	textureParameters[Coin] = { { 0,0,16,16 },{ 16,16 }, textures[COIN] };
	textureParameters[Chest] = { { 0,0,100,75 },{ 100,75 }, textures[CHEST] };
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