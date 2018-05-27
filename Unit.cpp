#include "Unit.h"
#include "Game.h"
#include "UnitAction.h"
#include "Attacks.h"
#include <math.h>

bool Unit::update(std::list <Projectile*>& monsterAttacks, Map* map) {
	if (hp <= 0)
		return false;

	if (!(frameCounter % textureFrameTime)) { // Next texture frame
		if (textureFrame == textureFrames - 1) { // The last texture frame has ended
			if (++currAction == pattern.end()) // Last action
				currAction = pattern.begin();

			frameCounter = 0;
			textureY = actions[*currAction]->texturePosY();
			textureFrame = 0;
			textureFrameTime = actions[*currAction]->textureFrameTime();
			textureFrames = actions[*currAction]->textureFrames();

			srcRect.y = dstRect.h * textureY;
			velocity.x = 0;
			velocity.y = 0;
		}
		else
			textureFrame++;
	}
	frameCounter++;

	if (frameCounter == actions[*currAction]->makeAttackFrame() && actions[*currAction]->attackExists()) {
		SDL_Point p = { map->getPlayer()->getPositionX(), map->getPlayer()->getPositionY() };
		actions[*currAction]->makeAttack(this, monsterAttacks, &p);
	}

	if (actions[*currAction]->movementExists())
		actions[*currAction]->makeMove(this);
	if (!(!velocity.y && !velocity.x)) {
		float dir = atan2(velocity.y, velocity.x);
		position.x += cos(dir) * speed;
		position.y += sin(dir) * speed;
	}
	return true;
}

void Unit::draw(SDL_Point* startRender) {
	srcRect.x = srcRect.w * textureFrame;
	dstRect.x = position.x - startRender->x - positionShiftX;
	dstRect.y = (position.y - startRender->y) * HEIGHT_SCALE - positionShiftY;
	if (velocity.x < 0)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &dstRect, NULL, NULL, flip);	

	SDL_Rect r;
	r.h = 4;
	r.w = radius * 2;
	r.x = position.x - positionShiftX - startRender->x;
	r.y = position.y - startRender->y;
	SDL_SetRenderDrawColor(Game::renderer, rand() % 225, 0, 102, 255);
	renderCircle(position.x - startRender->x, (position.y - startRender->y) * HEIGHT_SCALE, radius);
	//	SDL_RenderFillRect(Game::renderer, &r);
}

void Unit::updateFrame() {
	if (frameCounter == textureFrameTime) { // Next texture frame
		frameCounter = 0;
		if (textureFrame == textureFrames - 1) // The last texture frame has ended
			textureFrame = 0;
		else
			textureFrame++;
	}
	frameCounter++;
}

void Unit::addAction(ActionType action, Movement* move, AttackPattern* attack, int yPosTexture, int frames, int frameTime, int attackFrame) {
	actions[action] = new UnitAction(move, attack, yPosTexture, frames, frameTime, attackFrame);
}

void  Unit::addPattern(ActionType actionType) {
	if (pattern.empty()) {
		pattern.push_back(actionType);
		currAction = pattern.begin();

		frameCounter = 0;
		textureY = actions[*currAction]->texturePosY();
		textureFrame = 0;
		textureFrameTime = actions[*currAction]->textureFrameTime();
		textureFrames = actions[*currAction]->textureFrames();

		srcRect.y = dstRect.h * textureY;
	}
	else
		pattern.push_back(actionType);
}

Unit::Unit(SDL_Texture *txt, int width, int height) : GameObject(txt, Dynamic, Circle, width / 2) {
	speed = 3;
	hp = 10;

	velocity.x = 0;
	velocity.y = 0;

	dstRect.x = 100;
	dstRect.y = 100;
	srcRect.w = width;
	dstRect.w = width;
	srcRect.h = height;
	dstRect.h = height;
}


Unit::~Unit() {

}


void Unit::renderCircle(int _x, int _y, int radius) {
	int x = radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int err = tx - (radius << 1);
								 
	while (x >= y) {
		SDL_RenderDrawPoint(Game::renderer, _x + x, _y - y);
		SDL_RenderDrawPoint(Game::renderer, _x + x, _y + y);
		SDL_RenderDrawPoint(Game::renderer, _x - x, _y - y);
		SDL_RenderDrawPoint(Game::renderer, _x - x, _y + y);
		SDL_RenderDrawPoint(Game::renderer, _x + y, _y - x);
		SDL_RenderDrawPoint(Game::renderer, _x + y, _y + x);
		SDL_RenderDrawPoint(Game::renderer, _x - y, _y - x);
		SDL_RenderDrawPoint(Game::renderer, _x - y, _y + x);

		if (err <= 0){
			y++;
			err += ty;
			ty += 2;
		}
		else if (err > 0) {
			x--;
			tx += 2;
			err += tx - (radius << 1);
		}
	}
}