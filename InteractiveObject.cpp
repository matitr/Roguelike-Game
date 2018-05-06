#include "InteractiveObject.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"


void InteractiveObject::onPlayerTouch() {

}

void InteractiveObject::onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {

}

void InteractiveObject::updateInteraction(Map* map, std::vector <InteractiveObject*>& objects, Player* player, SDL_Event& event) {

}

bool InteractiveObject::update(Player *player) {


	return true;
}

void  InteractiveObject::draw(SDL_Point* startRender) {
	dstRect.x = position.x - startRender->x - dstRect.w / 2;
	dstRect.y = (position.y - startRender->y) - dstRect.h / 2;


	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

InteractiveObject::InteractiveObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType)
	: GameObject(txtInfo, objType, hitbType), interactObjOnKey(false) {

}

InteractiveObject::InteractiveObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType, int r)
	: GameObject(txtInfo, objType, hitbType, r), interactObjOnKey(false) {


}

InteractiveObject::InteractiveObject(TextureInfo& txtInfo, GameObjectType objType, ObjectHitboxType hitbType, SDL_Scancode _interactKey)
	: GameObject(txtInfo, objType, hitbType), interactObjKey(_interactKey), interactObjOnKey(true) {

}

InteractiveObject::~InteractiveObject() {

}
