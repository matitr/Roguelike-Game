#include "InteractiveObject.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"


void InteractiveObject::onPlayerTouch() {

}

void InteractiveObject::onPlayerInteract(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {

}

void InteractiveObject::updateInteraction(Map* map, std::vector <InteractiveObject*>& objects, Player* player) {

}

bool InteractiveObject::update(Player *player) {


	return true;
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

InteractiveObject::InteractiveObject(ItemTextureInfo& txtInfo, SDL_Point& dstR, SDL_Scancode _interactKey)
	: GameObject(txtInfo, dstR), interactObjKey(_interactKey), interactObjOnKey(true) {

}

InteractiveObject::~InteractiveObject() {

}
