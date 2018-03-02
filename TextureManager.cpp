#include "TextureManager.h"
#include "Game.h"



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