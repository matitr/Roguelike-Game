#include "Teleporter.h"
#include "InteractiveObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Player.h"
#include "Game.h"
#include "Input.h"


void Teleporter::onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {
	if (map->currentRoom()->battle)
		return;

	if (!interactingNow) {
		interactingNow = true;
		Input::keyPressed[interactObjKey] = false; // Disable "interactObjKey" key for one frame
		map->changeMinimapSize(MinimapClosed);
		map->getMinimapDstRect().w *= TELEPORT_MAP_SIZE_MULTIPLER;
		map->getMinimapDstRect().h *= TELEPORT_MAP_SIZE_MULTIPLER;
		map->getMinimapDstRect().x = map->getResolution().x / TELEPORT_MAP_SIZE_MULTIPLER - map->getMinimapDstRect().w / TELEPORT_MAP_SIZE_MULTIPLER;
		map->getMinimapDstRect().y = map->getResolution().y / TELEPORT_MAP_SIZE_MULTIPLER - map->getMinimapDstRect().h / TELEPORT_MAP_SIZE_MULTIPLER;
		player->changeInteractionBlock(true);
		player->inventory().close();
	}
}

void Teleporter::updateInteraction(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {
	SDL_Rect rect = { 0, 0, map->getResolution().x, map->getResolution().y };
	SDL_RenderCopy(Game::renderer, map->getTeleportMap(), &rect, NULL);
	SDL_RenderCopy(Game::renderer, map->minimap, NULL, &map->getMinimapDstRect());

	int x = Input::mousePosX, y = Input::mousePosY, i, drawRect;
	bool mouseLeftButton = Input::mousePressed[SDL_BUTTON_LEFT];

	x = (x - map->getMinimapDstRect().x) / TELEPORT_MAP_SIZE_MULTIPLER;
	y = (y - map->getMinimapDstRect().y) / TELEPORT_MAP_SIZE_MULTIPLER;

	for (i = 0; i < map->rooms.size(); i++) {
		if (map->rooms[i]->telporter && map->rooms[i]->visited && map->rooms[i] != map->currentRoom()
			&& x >= map->rooms[i]->x1 && x <= map->rooms[i]->x2 && y >= map->rooms[i]->y1 && y <= map->rooms[i]->y2) {

			SDL_SetRenderDrawColor(Game::renderer, rand() % 100 + 150, 0, 92, 200);
			SDL_Rect r = { // Draw rect for selection
				map->getMinimapDstRect().x + map->rooms[i]->x1 * TELEPORT_MAP_SIZE_MULTIPLER + 1,
				map->getMinimapDstRect().y + map->rooms[i]->y1 * TELEPORT_MAP_SIZE_MULTIPLER + 1,
				(map->rooms[i]->x2 - map->rooms[i]->x1) * TELEPORT_MAP_SIZE_MULTIPLER,
				(map->rooms[i]->y2 - map->rooms[i]->y1) * TELEPORT_MAP_SIZE_MULTIPLER };

			// Width of lines
			SDL_RenderDrawRect(Game::renderer, &r);
			for (drawRect = 0; drawRect < 5; drawRect++) {
				r.x--;
				r.y--;
				r.w += 2;
				r.h += 2;
				SDL_RenderDrawRect(Game::renderer, &r);
			}

			if (mouseLeftButton && i < map->rooms.size()) {
				map->changeRoom(map->rooms[i], map->rooms[i]->telporter);
				interactingNow = false;
				map->changeMinimapSize(MinimapSmall);
				player->changeInteractionBlock(false);
				player->inventory().close();
			}
			break;
		}
	}

	// Close teleporter
	if (Input::keyPressed[interactObjKey] || Input::keyPressed[SDL_SCANCODE_ESCAPE]) {
		interactingNow = false;
		map->changeMinimapSize(MinimapSmall);
		player->changeInteractionBlock(false);
	}
}

Teleporter::Teleporter(double posX, double posY) : InteractiveObject(TextureManager::textureParameters[SingleTexture::Teleport], Static, Circle, SDL_SCANCODE_T) {
	position.x = posX;
	position.y = posY;
	setFlatTextureOnFloor(true);
}


Teleporter::~Teleporter() {

}
