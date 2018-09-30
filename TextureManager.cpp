#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include <string>

std::unordered_map <TextureFile, SDL_Texture*> TextureManager::textures;
std::unordered_map <SingleFieldTexture, SDL_Rect> TextureManager::fieldTextureSrcRect;
std::unordered_map <SingleTexture, TextureInfo> TextureManager::textureParameters;
std::unordered_map <ItemName::Name, ItemTextureInfo> TextureManager::itemTextureDetails;

void TextureManager::loadAllTextures() {
	try {
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
	}
	catch (const char* dir) {
		std::cout << "Error while opening texture from file: " << dir << std::endl;
	}
	catch (...) {
		std::cout << " Unknown error while opening texture file" << std::endl;
	}

	TextureManager::loadAllTextureSrcRect();
}

void TextureManager::loadAllTextureSrcRect() { // srcRect = { x, y, w, h }
	int fieldSize = 60;
	// FLOORS
	fieldTextureSrcRect[SingleFieldTexture::WOOD_FLOOR] = { fieldSize * 0,fieldSize * 0,fieldSize,fieldSize };

	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_N] = { fieldSize * 6, fieldSize * 0, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_E] = { fieldSize * 7, fieldSize * 1, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_S] = { fieldSize * 7, fieldSize * 0, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_W] = { fieldSize * 6, fieldSize * 1, fieldSize, fieldSize };

	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_NW] = { fieldSize * 6, fieldSize * 2, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_NE] = { fieldSize * 7, fieldSize * 2, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_SW] = { fieldSize * 6, fieldSize * 3, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_WALL_SE] = { fieldSize * 7, fieldSize * 3, fieldSize, fieldSize };

	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_COLUMN_SE] = { fieldSize * 4, fieldSize * 2, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_COLUMN_SW] = { fieldSize * 5, fieldSize * 2, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_COLUMN_NE] = { fieldSize * 4, fieldSize * 3, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::FLOOR_NEAR_COLUMN_NW] = { fieldSize * 5, fieldSize * 3, fieldSize, fieldSize };

	// WALLS
	fieldTextureSrcRect[SingleFieldTexture::DOORS] = { fieldSize * 1,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_FRONT0] = { fieldSize * 2,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_FRONT1] = { fieldSize * 3,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_CORNER_LT] = { fieldSize * 5,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_CORNER_RT] = { fieldSize * 4,fieldSize * 1,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_CORNER_LB] = { fieldSize * 5,fieldSize * 0,fieldSize,fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_CORNER_RB] = { fieldSize * 4,fieldSize * 0,fieldSize,fieldSize };

	fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_T] = { fieldSize * 0, fieldSize * 1, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_R] = { fieldSize * 1, fieldSize * 1, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_B] = { fieldSize * 2, fieldSize * 1, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_TOP_L] = { fieldSize * 3, fieldSize * 1, fieldSize, fieldSize };

	fieldTextureSrcRect[SingleFieldTexture::WALL_COLUMN_SW] = { fieldSize * 0, fieldSize * 2, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_COLUMN_SE] = { fieldSize * 1, fieldSize * 2, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_COLUMN_NW] = { fieldSize * 2, fieldSize * 2, fieldSize, fieldSize };
	fieldTextureSrcRect[SingleFieldTexture::WALL_COLUMN_NE] = { fieldSize * 3, fieldSize * 2, fieldSize, fieldSize };

	fieldTextureSrcRect[SingleFieldTexture::WALL_TOP] = { fieldSize * 0, fieldSize * 3, fieldSize, fieldSize };

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

	if (!texture)
		throw dir;

	return texture;
}

SDL_Texture* TextureManager::textureFromText(std::string textStr, TTF_Font* font, SDL_Color& color, int maxTextWidth) {
	SDL_Surface* surfaceText = nullptr;
	int lineWidth = 0;
	TTF_SizeText(font, textStr.c_str(), &lineWidth, NULL);

	if (lineWidth > maxTextWidth) {
		int surfaceWidth = 0;
		int surfaceHeight = 0;

		// Split textStr into lines
		std::vector<std::string> lines;
		std::string test = textStr.substr(0, -1);
		do {
			bool deleteSplitChar = true;
			std::size_t foundSplitPos = 0;
			std::size_t tempSplitPos = -1;

			do {
				foundSplitPos = tempSplitPos;
				tempSplitPos = textStr.find(" ", tempSplitPos + 1);
				TTF_SizeText(font, textStr.substr(0, tempSplitPos).c_str(), &lineWidth, NULL);
			} while (tempSplitPos != std::string::npos && lineWidth < maxTextWidth);

			if (tempSplitPos == std::string::npos && lineWidth < maxTextWidth) { // Not found split point
				lines.push_back(textStr);
				textStr = "";
			}
			else {
				lines.push_back(textStr.substr(0, foundSplitPos));
				textStr.erase(0, foundSplitPos + int(deleteSplitChar));
			}
		} while (!textStr.empty());

		std::vector<SDL_Surface*> surfaces;
		for (int i = 0; i < lines.size(); i++) {
			SDL_Surface* surfaceLine = TTF_RenderText_Blended(font, lines[i].c_str(), color);
			
			surfaces.push_back(surfaceLine);
			surfaceHeight += surfaceLine->h;
			if (surfaceLine->w > surfaceWidth)
				surfaceWidth = surfaceLine->w;
		}

//		Uint32 rmask = 0x000000ff, gmask = 0x0000ff00, bmask = 0x00ff0000, amask = 0xff000000;
//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
//		rmask = 0xff000000;
//		gmask = 0x00ff0000;
//		bmask = 0x0000ff00;
//		amask = 0x000000ff;
//#endif

		surfaceText = SDL_CreateRGBSurface(SDL_SWSURFACE, surfaceWidth, surfaceHeight, 32, 0, 0, 0, 0);
		
		surfaceHeight = 0;
		for (int i = 0; i < surfaces.size(); i++) { // Make one surface from all surfaces(lines)
			SDL_Rect r = { 0, surfaceHeight, 0, 0 };
			surfaceHeight += surfaces[i]->h;
			SDL_BlitSurface(surfaces[i], NULL, surfaceText, &r);
			SDL_FreeSurface(surfaces[i]);
		}
	}
	else {
		surfaceText = TTF_RenderText_Blended(font, textStr.c_str(), color);
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surfaceText);
	SDL_FreeSurface(surfaceText);
	return texture;
}

void TextureManager::clearData() {
	for (auto it = textures.begin(); it != textures.end(); it++)
		if (it->second)
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