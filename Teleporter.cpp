#include "Teleporter.h"
#include "InteractiveObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Player.h"
#include "Game.h"


void Teleporter::onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {
	if (!interactingNow) {
		interactingNow = true;
		map->changeMinimapSize(MinimapClosed);
	}
	else {

	}
}

void Teleporter::updateInteraction(Map* map, std::vector <InteractiveObject*>& objects, Player* player, SDL_Event& event) {
	SDL_Rect rect = { 0, 0, map->getResolution().x, map->getResolution().y };
	SDL_RenderCopy(Game::renderer, map->getTeleportMap(), &rect, NULL);
	SDL_RenderCopy(Game::renderer, map->minimap, &rect, NULL);
}

Teleporter::Teleporter(float posX, float posY) : InteractiveObject(TextureManager::textureParameters[Teleport], Static, Circle, SDL_SCANCODE_T) {
	position.x = posX;
	position.y = posY;
}


Teleporter::~Teleporter() {

}
