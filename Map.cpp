#include "Map.h"
#include "TextureManager.h"
#include <time.h>
#include "Game.h"
#include "Teleporter.h"
#include "Chest.h"
#include "Player.h"
#include <algorithm>
#include "CombatTextManager.h"
#include "myMath.h"


void Map::generateNewLevel() {
	generator.generateNewMap();
	setSpawn(rooms[0], (rooms[0]->x2 - rooms[0]->x1) / 2.0f + rooms[0]->x1, (rooms[0]->y2 - rooms[0]->y1) / 2.0f + rooms[0]->y1);
	rooms[0]->setVisited(true);
	createMinimap();
}

void Map::createMinimap() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 184, 77, 200);
	SDL_Rect r;

	r.h = MAP_HEIGHT;
	r.w = MAP_WIDTH;
	r.x = 0;
	r.y = 0;

	// Background color
	SDL_SetRenderTarget(Game::renderer, minimapBackground);
	SDL_SetRenderDrawColor(Game::renderer, 0, 51, 51, 100);
	SDL_RenderFillRect(Game::renderer, &r);

	// Minimap
	SDL_SetRenderTarget(Game::renderer, minimap);
	SDL_RenderClear(Game::renderer);
	SDL_SetRenderDrawColor(Game::renderer, 255, 184, 77, 200);

	r.w = 1;
	r.h = 1;

	for (int i = 0; i < rooms.size(); i++) { // for every room addToMinimap if already visited
		if (std::find(roomsOnMiniman.begin(), roomsOnMiniman.end(), rooms[i]) == roomsOnMiniman.end()) {
			addToMinimap(rooms[i]);
		}
	}

	SDL_SetRenderTarget(Game::renderer, NULL);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void Map::addToMinimap(Room* room) {
	SDL_SetRenderDrawColor(Game::renderer, 255, 184, 77, 200);
	SDL_SetRenderTarget(Game::renderer, minimap);
	SDL_Rect r;
	r.w = 1;
	r.h = 1;
	int x, y;

	// Render room on minimap if is not renderer already
	if (std::find(roomsOnMiniman.begin(), roomsOnMiniman.end(), room) == roomsOnMiniman.end()){
		for (y = room->y1; y < room->y2; y++) {
			for (x = room->x1; x < room->x2; x++) {
				if (getField(x, y) && (getField(x, y)->type() == FieldType::Floor 
					|| (getField(x, y)->type() == FieldType::Wall && getField(x, y - 1) && getField(x, y - 1)->type() == FieldType::Floor))) {
					r.x = x;
					r.y = y;
					SDL_RenderFillRect(Game::renderer, &r);
				}
			}
		}
		roomsOnMiniman.push_back(room);

		// Draw teleport
		if (room->telporter) {
			SDL_SetRenderDrawColor(Game::renderer, 0, 102, 255, 200);
			r.w = 3;
			r.h = 3;
			r.x = int(room->telporter->getPositionX() / fieldRect.w - 1);
			r.y = int(room->telporter->getPositionY() / fieldRect.h - 1);
			SDL_RenderFillRect(Game::renderer, &r);
			// Undo color and r.w and r.h
			SDL_SetRenderDrawColor(Game::renderer, 255, 184, 77, 200);
			r.w = 1;
			r.h = 1;
		}
	}

	// Draw hallways
	for (std::list<Room*>::iterator it = room->hallways.begin(); it != room->hallways.end(); it++) { // for every hallway in room
		if (std::find(roomsOnMiniman.begin(), roomsOnMiniman.end(), (*it)) == roomsOnMiniman.end()) {
			for (y = (*it)->y1; y <= (*it)->y2; y++) {
				for (x = (*it)->x1; x <= (*it)->x2; x++) {
					if (getField(x, y) && (getField(x, y)->type() == FieldType::Floor || getField(x, y)->type() == FieldType::Door)) {
						r.x = x;
						r.y = y;
						SDL_RenderFillRect(Game::renderer, &r);
					}
				}
			}
			roomsOnMiniman.push_back(*it);
		}
	}

	SDL_SetRenderTarget(Game::renderer, NULL);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void Map::createTeleportMap() {
	// teleportMap background
	teleportMap = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, getResolution().x, getResolution().y);
	SDL_SetTextureBlendMode(teleportMap, SDL_BLENDMODE_BLEND);

	SDL_Rect r = { 0, 0, getResolution().x, getResolution().y };

	SDL_SetRenderTarget(Game::renderer, teleportMap);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 100);
	SDL_RenderFillRect(Game::renderer, &r);
	SDL_SetRenderTarget(Game::renderer, NULL);
}

void Map::render(std::vector <GameObject*>& gameObjects) {
	if (!Game::renderer)
		return;

	int fieldRectH = fieldRect.h;
	fieldRect.h *= HEIGHT_SCALE;

	int fieldX, fieldY;
	int fieldCounterX, fieldCounterY;

	// Draw floor
	fieldY = startRenderPos.yField;
	for (fieldCounterY = 0; fieldCounterY <= fieldsToRender.y; fieldCounterY++, fieldY++) { // Y
		fieldX = startRenderPos.xField;
		fieldRect.y = fieldCounterY * fieldRect.h - startRenderPos.yAdditionalPixels;
		for (fieldCounterX = 0; fieldCounterX <= fieldsToRender.x; fieldCounterX++, fieldX++) { // X
			fieldRect.x = fieldCounterX * fieldRect.w - startRenderPos.xAdditionalPixels;
			if (getField(fieldX, fieldY) && getField(fieldX, fieldY)->ground())
				getField(fieldX, fieldY)->drawField(fieldRect.x, fieldRect.y);
		}
	}

	std::sort(gameObjects.begin(), gameObjects.end(),
		[](const GameObject* a, const GameObject* b)->bool
	{return (a->flatTextureOnFloor() && !b->flatTextureOnFloor()) || (!a->flatTextureOnFloor() && !b->flatTextureOnFloor() && a->getPositionY() < b->getPositionY()); });

	size_t numbOfGameObj = gameObjects.size(), iGameObject = 0;

	// Draw objects that are flat on floor
	while (iGameObject < numbOfGameObj && gameObjects[iGameObject]->flatTextureOnFloor()) {
		gameObjects[iGameObject]->draw(&startRender);
		iGameObject++;
	}

	// Draw rest
	fieldY = startRenderPos.yField;
	for (fieldCounterY = 0; fieldCounterY <= fieldsToRender.y; fieldCounterY++, fieldY++) { // Y
		fieldX = startRenderPos.xField;
		fieldRect.y = fieldCounterY * fieldRect.h - startRenderPos.yAdditionalPixels;

		// Draw gameObjects
		while (iGameObject < numbOfGameObj && gameObjects[iGameObject]->getPositionY() < fieldY * fieldRect.h) {
			gameObjects[iGameObject]->draw(&startRender);
			iGameObject++;
		}

		for (fieldCounterX = 0; fieldCounterX <= fieldsToRender.x; fieldCounterX++, fieldX++) { // X
			fieldRect.x = fieldCounterX * fieldRect.w - startRenderPos.xAdditionalPixels;
			if (getField(fieldX, fieldY) && !getField(fieldX, fieldY)->ground())
				getField(fieldX, fieldY)->drawField(fieldRect.x, fieldRect.y);
		}
	}

	// Draw the remaining gameObjects
	while (iGameObject < numbOfGameObj) {
		gameObjects[iGameObject]->draw(&startRender);
		iGameObject++;
	}

	// Draw drawLast fields
	fieldY = startRenderPos.yField;
	for (fieldCounterY = 0; fieldCounterY <= fieldsToRender.y; fieldCounterY++, fieldY++) { // Y
		fieldX = startRenderPos.xField;
		fieldRect.y = fieldCounterY * fieldRect.h - startRenderPos.yAdditionalPixels;

		for (fieldCounterX = 0; fieldCounterX <= fieldsToRender.x; fieldCounterX++, fieldX++) { // X
			fieldRect.x = fieldCounterX * fieldRect.w - startRenderPos.xAdditionalPixels;
			if (getField(fieldX, fieldY) && getField(fieldX, fieldY)->drawLast())
				getField(fieldX, fieldY)->drawField(fieldRect.x, fieldRect.y);
		}
	}
	CombatTextManager::get().drawAndUpdate(&startRender);

	renderMinimap();
	fieldRect.h = fieldRectH;
}

void Map::renderMinimap() {
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 100);

	// Render minimap
	if (minimapSize != MinimapClosed) {
		SDL_RenderCopy(Game::renderer, minimapBackground, &minimapSrcRect, &minimapDstRect);
		SDL_RenderCopy(Game::renderer, minimap, &minimapSrcRect, &minimapDstRect);
		SDL_RenderDrawRect(Game::renderer, &minimapDstRect);
	}

	// Show player on minimap
	SDL_Rect r = { minimapDstRect.x + cameraPos.x / fieldRect.w, minimapDstRect.y + cameraPos.y / fieldRect.h, MINIMAP_SCALE, MINIMAP_SCALE };
	if (r.h < 0) {
		r.w = 1; r.h = 1;
	}

	if (minimapSize == MinimapLarge) {
		minimapDstRect.x -= (int)r.w;
		minimapDstRect.y -= (int)r.h;
		SDL_RenderFillRect(Game::renderer, &r);
		minimapDstRect.x += (int)r.w;
		minimapDstRect.y += (int)r.h;
	}
	else if (minimapSize == MinimapSmall) {
		r.x = minimapDstRect.x + MINIMAP_WIDTH / 2;
		r.y = minimapDstRect.y + MINIMAP_HEIGHT / 2;
		minimapDstRect.x -= (int)r.w;
		minimapDstRect.y -= (int)r.h;
		SDL_RenderFillRect(Game::renderer, &r);
		minimapDstRect.x += (int)r.w;
		minimapDstRect.y += (int)r.h;
	}

}

void Map::setFieldsPositions() {
	int x, y;
	for (y = 0; y < MAP_HEIGHT; y++)
		for (x = 0; x < MAP_WIDTH; x++)
			if (getField(x, y))
				getField(x, y)->setPosition(x, y);
}

void Map::changeRoom(Room* room, Field* fieldToMove) {
	int x = fieldToMove->x(), y = fieldToMove->y();
	int newX, newY;
	
	if (getField(x + 1, y)->type() == FieldType::Door) { // Doors are horizontally
		newX = x * fieldRect.w + fieldRect.w;
		if (y + 1 <= room->y2) // Top
			newY = (y + 1.5) * fieldRect.h;
		else
			newY = (y - 0.5) * fieldRect.h;
	}
	else if (getField(x - 1, y)->type() == FieldType::Door) { // Doors are horizontally
		newX = x * fieldRect.w;
		if (y + 1 <= room->y2) // Top
			newY = (y + 1.5) * fieldRect.h;
		else
			newY = (y - 0.5) * fieldRect.h;
	}
	else if (getField(x, y + 1)->type() == FieldType::Door) { // Doors are vertically
		newY = y * fieldRect.w + fieldRect.w;
		if (x + 1 <= room->x2) // Left
			newX = (x + 1.5) * fieldRect.w;
		else
			newX = (x - 0.5) * fieldRect.w;

	}
	else { // Doors are vertically
		newY = y * fieldRect.w;
		if (x + 1 <= room->x2)
			newX = (x + 1.5) * fieldRect.w;
		else
			newX = (x - 0.5) * fieldRect.w;
	}

	currRoom = room;
	setCamera(newX, newY);
	addToMinimap(room);
	_roomChanged = true;
}

void Map::changeRoom(Room* room, Teleporter* tele) {
	currRoom = room;
	player->setPosition(tele->getPositionX(), tele->getPositionY());
	_roomChanged = true;
}

bool Map::checkClearPath(GameObject* object, GameObject* objectTarget) {

	double angle = atan2(((int)objectTarget->getPositionY() - (int)object->getPositionY()), ((int)objectTarget->getPositionX() - (int)object->getPositionX()));
	bool goHorizontal = (abs(angle) > (M_PI / 4) && abs(angle) < (3 * M_PI / 4)) ? false : true;
	angle -= M_PI / 2; // - 90 degrees

	PointDouble p1(object->getPositionX() + cos(angle) * object->getRadius(), object->getPositionY() + sin(angle) * object->getRadius());
	PointDouble p2(objectTarget->getPositionX() + cos(angle) * objectTarget->getRadius(), objectTarget->getPositionY() + sin(angle) * objectTarget->getRadius());

	angle += M_PI;


	for (int i = 0; i < 3; i++) { // Check 3 lines
		LineSegment lineS(p1, p2);

		if (goHorizontal) {
			if (p2.x < p1.x) {
				PointDouble temp(p1);
				p1 = p2;
				p2 = temp;
			}

			int fieldX = p1.x / fieldRect.w;
			int fieldY = p1.y / fieldRect.h;

			if (!checkClearField(getField(fieldX, fieldY), lineS))
				return false;
			fieldX++;

			int goalFieldX = p2.x / fieldRect.w + 1;
			int prevFieldY = fieldY;

			while (fieldX < goalFieldX) {
				double d = lineS.y(fieldX * fieldRect.w + fieldRect.w / 2) / fieldRect.w;
				fieldY = lineS.y(fieldX * fieldRect.w + fieldRect.w / 2) / fieldRect.w;
				if (fieldY != prevFieldY) { // Move vertical
					int y = lineS.y(fieldX * fieldRect.w) / fieldRect.h;
					if (y == fieldY) { // Left
						if (!checkClearField(getField(fieldX - 1, fieldY), lineS))
							return false;
					}
					else { // Check prevFieldY
						if (!checkClearField(getField(fieldX, prevFieldY), lineS))
							return false;
					}
					prevFieldY = fieldY;
				}

				if (!checkClearField(getField(fieldX, fieldY), lineS))
					return false;
				fieldX++;
			}
		}
		else {
			if (p2.y < p1.y) {
				PointDouble temp(p1);
				p1 = p2;
				p2 = temp;
			}

			int fieldX = p1.x / fieldRect.w;
			int fieldY = p1.y / fieldRect.h;

			if (!checkClearField(getField(fieldX, fieldY), lineS))
				return false;
			fieldY++;

			int goalFieldY = p2.y / fieldRect.h + 1;
			int prevFieldX = fieldX;

			while (fieldY < goalFieldY) {
				fieldX = lineS.x(fieldY * fieldRect.h + fieldRect.h / 2) / fieldRect.h;
				if (fieldX < prevFieldX) { // Move vertical
					int x = lineS.x(fieldY * fieldRect.h) / fieldRect.w;
					if (x == fieldX) { // Check up
						if (!checkClearField(getField(fieldX, fieldY - 1), lineS))
							return false;
					}
					else { // Check prevFieldX
						if (!checkClearField(getField(prevFieldX, fieldY), lineS))
							return false;
					}
					prevFieldX = fieldX;
				}

				if (!checkClearField(getField(fieldX, fieldY), lineS))
					return false;
				fieldY++;
			}
		}

		p1.x += cos(angle) * object->getRadius();
		p1.y += sin(angle) * object->getRadius();
		p2.x += cos(angle) * object->getRadius();
		p2.y += sin(angle) * object->getRadius();
	}

	return true;
}

bool Map::checkClearField(Field* field, LineSegment& lineS) {
	if (field->type() == FieldType::Wall) {
		PointInt fieldPos((int)field->getPositionX(), (int)field->getPositionY());
		PointInt radius((int)field->getRadius(), (int)field->getRadiusY());

		if (lineS.checkInserction(fieldPos.x - radius.x, fieldPos.y - radius.y, fieldPos.x - radius.x, fieldPos.y + radius.y))
			return false;
		if (lineS.checkInserction(fieldPos.x - radius.x, fieldPos.y - radius.y, fieldPos.x + radius.x, fieldPos.y - radius.y))
			return false;
		if (lineS.checkInserction(fieldPos.x + radius.x, fieldPos.y - radius.y, fieldPos.x + radius.x, fieldPos.y + radius.y))
			return false;
		if (lineS.checkInserction(fieldPos.x + radius.x, fieldPos.y + radius.y, fieldPos.x - radius.x, fieldPos.y + radius.y))
			return false;
	}

	for (auto it = field->getCollisionObj().begin(); it != field->getCollisionObj().end(); it++) {
		PointInt fieldPos((int)(*it)->getPositionX(), (int)(*it)->getPositionY());
		PointInt radius((int)(*it)->getRadius(), (int)(*it)->getRadiusY());

		if (lineS.checkInserction(fieldPos.x - radius.x, fieldPos.y - radius.y, fieldPos.x - radius.x, fieldPos.y + radius.y))
			return false;
		if (lineS.checkInserction(fieldPos.x - radius.x, fieldPos.y - radius.y, fieldPos.x + radius.x, fieldPos.y - radius.y))
			return false;
		if (lineS.checkInserction(fieldPos.x + radius.x, fieldPos.y - radius.y, fieldPos.x + radius.x, fieldPos.y + radius.y))
			return false;
		if (lineS.checkInserction(fieldPos.x + radius.x, fieldPos.y + radius.y, fieldPos.x - radius.x, fieldPos.y + radius.y))
			return false;
	}

	return true;
}

Map::Map(Player* p, int _hCenter, int _wCenter) : MapCore(_hCenter, _wCenter), player(p), generator(this) {
	hCenter = _hCenter;
	wCenter = _wCenter;

	createTeleportMap();
}

Map::~Map() {
	for (size_t y = 0; y < MAP_HEIGHT; y++)
		for (size_t x = 0; x < MAP_WIDTH; x++)
			if (getField(x, y))
				delete getField(x, y);

	map.clear();

	for (std::vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
		delete (*it);
}   