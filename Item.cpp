#include "Item.h"



Item::Item(SDL_Texture* _texture, int numberOfItems, int maxNumber) {
	texture = _texture;
	quantity = numberOfItems;
	maxQuantity = maxNumber;
}


Item::~Item(){

}
