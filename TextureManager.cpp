#include "TextureManager.h"
#include "Game.h"

std::unordered_map <TextureFile, SDL_Texture*> TextureManager::textures;
std::unordered_map <SingleFieldTexture, SDL_Rect> TextureManager::fieldTextureSrcRect;
std::unordered_map <SingleTexture, TextureInfo> TextureManager::textureParameters;
std::unordered_map <ItemName::Name, ItemTextureInfo> TextureManager::itemTextureDetails;

void TextureManager::loadAllTextures() {
	textures[TextureFile::PLAYER] = TextureManager::LoadTexture("Textures/player.png");
	
	textures[TextureFile::PROJECTILES] = TextureManager::LoadTexture("Textures/projectiles.png");
	textures[TextureFile::PLAYER_STATS] = TextureManager::LoadTexture("Textures/playerStats.png"); 

	textures[TextureFile::LEVEL_1] = TextureManager::LoadTexture("Textures/level_1.png");
	textures[TextureFile::OBJECTS] = TextureManager::LoadTexture("Textures/objects.png");
	textures[TextureFile::COIN] = TextureManager::LoadTexture("Textures/coin.png");
	textures[TextureFile::CHEST] = TextureManager::LoadTexture("Textures/chest.png");
	textures[TextureFile::INVENTORY] = TextureManager::LoadTexture("Textures/inventory.png");
	textures[TextureFile::UNIT] = TextureManager::LoadTexture("Textures/unit.png");
	textures[TextureFile::Items] = TextureManager::LoadTexture("Textures/items.png");

	TextureManager::loadAllTextureSrcRect();
}

void TextureManager::loadAllTextureSrcRect() { // srcRect = { x, y, w, h }
	int fieldSize = 60;

	fieldTextureSrcRect[SingleFieldTexture::WOOD_FLOOR] = { fieldSize * 0,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::DOORS] = { fieldSize * 1,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_SIDE0] = { fieldSize * 2,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_SIDE1] = { fieldSize * 3,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_CORSEN_LT] = { fieldSize * 5,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_CORSEN_RT] = { fieldSize * 4,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_CORSEN_LB] = { fieldSize * 5,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_CORSEN_RB] = { fieldSize * 4,fieldSize * 0,fieldSize,fieldSize };

	fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_T] = { fieldSize * 0,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_R] = { fieldSize * 1,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_B] = { fieldSize * 2,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_L] = { fieldSize * 3,fieldSize * 1,fieldSize,fieldSize };

	// Parameters:
	//  { SDL_Rect srcRect = { x, y, w, h }, Rect dstRect = { w, h }, SDL_Texture* texture };
	textureParameters[SingleTexture::Teleport] = { { 0, 0, 468, 468 },{ 120,120 }, textures[TextureFile::OBJECTS] };
	textureParameters[SingleTexture::TeleportOff] = { { 470,0,468,468 },{ 120,120 }, textures[TextureFile::OBJECTS] };
	textureParameters[SingleTexture::TeleportOn] = { { 940,0,468,468 },{ 120,120 }, textures[TextureFile::OBJECTS] };

	textureParameters[SingleTexture::Coin] = { { 0,0,16,16 },{ 16,16 }, textures[TextureFile::COIN] };
	textureParameters[SingleTexture::Chest] = { { 0,0,100,75 },{ 100,75 }, textures[TextureFile::CHEST] };

	textureParameters[SingleTexture::ProjectileT] = { { 0,0,64,64 },{ 32,32 }, textures[TextureFile::PROJECTILES] };

	textureParameters[SingleTexture::PlayerT] = { { 0,0,64,64 },{ 64,64 }, textures[TextureFile::PLAYER] };
	textureParameters[SingleTexture::UnitT] = { { 0,0,64,64 },{ 64,64 }, textures[TextureFile::UNIT] };

	int itemSizeFile = 100;
	itemTextureDetails[ItemName::Item1] = { { 0,0,itemSizeFile,itemSizeFile }, textures[TextureFile::Items] };
	itemTextureDetails[ItemName::Item2] = { { 100,0,itemSizeFile,itemSizeFile }, textures[TextureFile::Items] };
	itemTextureDetails[ItemName::Item3] = { { 200,0,itemSizeFile,itemSizeFile }, textures[TextureFile::Items] };
	itemTextureDetails[ItemName::Item4] = { { 0,100,itemSizeFile,itemSizeFile }, textures[TextureFile::Items] };
	itemTextureDetails[ItemName::Item5] = { { 100,100,itemSizeFile,itemSizeFile }, textures[TextureFile::Items] };
	itemTextureDetails[ItemName::Item6] = { { 200,100,itemSizeFile,itemSizeFile }, textures[TextureFile::Items] };
}

SDL_Texture* TextureManager::LoadTexture(const char* dir) {
	SDL_Surface* surface = IMG_Load(dir);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

void TextureManager::clearData() {
	for (auto it = textures.begin(); it != textures.end(); it++)
		SDL_DestroyTexture(it->second);

	textures.clear();
	fieldTextureSrcRect.clear();
	textureParameters.clear();
	itemTextureDetails.clear();
}

TextureManager::TextureManager() {

}


TextureManager::~TextureManager() {

}