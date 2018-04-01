#include "Unit.h"
#include "Game.h"
#include "UnitAction.h"
#include "Attacks.h"

bool Unit::update(std::list <Projectile*>& monsterAttacks, Map* map, SDL_Rect& fieldRect) {
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

			srcrect.y = dstrect.h * textureY;
		}
		else
			textureFrame++;
	}
	frameCounter++;

	if (frameCounter == actions[*currAction]->makeAttackFrame() && actions[*currAction]->attackExists())
		actions[*currAction]->makeAttack(this, monsterAttacks);

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
	srcrect.x = srcrect.w * textureFrame;
	dstrect.x = position.x - startRender->x - positionShiftX;
	dstrect.y = position.y - startRender->y - positionShiftY;
	if (velocity.x < 0)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(Game::renderer, texture, &srcrect, &dstrect, NULL, NULL, flip);	
	
	SDL_Rect r;
	r.h = 4;
	r.w = radius * 2;
	r.x = position.x - positionShiftX - startRender->x;
	r.y = position.y - startRender->y;
	SDL_SetRenderDrawColor(Game::renderer, rand() % 225, 0, 102, 255);
	renderCircle(position.x - startRender->x, position.y - startRender->y, radius);
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

void Unit::addAction(ActionType action, Movement* move, Attack* attack, int yPosTexture, int frames, int frameTime, int attackFrame, int loops) {
	actions[action] = new UnitAction(move, attack, yPosTexture, frames, frameTime, attackFrame, loops);
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

		srcrect.y = dstrect.h * textureY;
	}
	else
		pattern.push_back(actionType);
}

void Unit::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void Unit::setPositionShift(float _positionShiftX, float _positionShiftY, float _hitboxRange) {
	positionShiftX = _positionShiftX * dstrect.w;
	positionShiftY = _positionShiftY * dstrect.h;
	radius = (_hitboxRange * dstrect.w) / 2;
}

Unit::Unit(SDL_Texture *txt, int width, int height) : GameObject(Dynamic, Circle) {
	speed = 3;
	hp = 10;

	texture = txt;

	velocity.x = 0;
	velocity.y = 0;

	dstrect.x = 100;
	dstrect.y = 100;
	srcrect.w = width;
	dstrect.w = width;
	srcrect.h = height;
	dstrect.h = height;
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