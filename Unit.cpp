#include "Unit.h"
#include "Game.h"
#include "UnitAction.h"
#include "Attacks.h"

void Unit::update(std::list <Projectile*>& monsterAttacks, Map* map, SDL_Rect& fieldRect) {
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

	if (frameCounter == actions[*currAction]->makeAttackFrame())
		actions[*currAction]->makeAttack(this, monsterAttacks);

	actions[*currAction]->makeMove(this);
	if (!(!velocity.y && !velocity.x)) {
		float dir = atan2(velocity.y, velocity.x);
		position.x += cos(dir) * speed;
		position.y += sin(dir) * speed;
	}
}

void Unit::draw(SDL_Point* startRender) {
	srcrect.x = srcrect.w * textureFrame;
	dstrect.x = position.x - startRender->x;
	dstrect.y = position.y - startRender->y;
	if (velocity.x < 0)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(Game::renderer, texture, &srcrect, &dstrect, NULL, NULL, flip);
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
	actions[action] = new UnitAction(action, move, attack, yPosTexture, frames, frameTime, attackFrame, loops);
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
	position.x = x - srcrect.w * 3 / 4;
	position.y = y - srcrect.w * 1;
}

Unit::Unit(SDL_Texture *txt, int width, int height) {
	speed = 5;

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
