#include "Player.h"
#include "Game.h"
#include "Map.h"
#include <math.h>


void Player::update(Map* map, SDL_Rect& fieldRect) {
	if (attackFrame > -1) {
		if (attackFrame + 1 == attackFrames)
			attackFrame = -1;
		else
			attackFrame++;
	}

	if (lastRollFramesAgo < rollCooldown)
		lastRollFramesAgo++;

	if (unitActionName == Roll) {
		velocity.x = rollVelocity.x;
		velocity.y = rollVelocity.y;
	}

	Field *field = map->map[(position.x + velocity.x * speed + srcrect.w) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 2) / fieldRect.h];

	if (velocity.x < 0)
		field = map->map[(position.x + velocity.x * speed) / fieldRect.w][(position.y + srcrect.h / 4 * 3) / fieldRect.h];
	else if (velocity.x > 0)
		field = map->map[(position.x + velocity.x * speed + srcrect.w) / fieldRect.w][(position.y + srcrect.h / 4 * 3) / fieldRect.h];

	if (velocity.x != 0 && field->type() == Door && !map->currentRoom()->battle) {
		Field * f = map->currentRoom()->doorsConnection[field];
		map->changeRoom(map->currentRoom()->roomConnection[field], map->currentRoom()->doorsConnection[field]);
		resetAnimation();
		setPosition(map->getCameraX(), map->getCameraY());
		velocity.x = 0;
		velocity.y = 0;
		setAnimation(Stand);
		return;
	}
	else if (!field->ground())
		velocity.x = 0;

	if (velocity.y < 0)
		field = map->map[(position.x) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h / 4 * 3) / fieldRect.h];
	else if (velocity.y > 0)
		field = map->map[(position.x) / fieldRect.w][(position.y + velocity.y * speed + srcrect.h) / fieldRect.h];

	if (velocity.y != 0 && field->type() == Door && !map->currentRoom()->battle) {
		map->changeRoom(map->currentRoom()->roomConnection[field], map->currentRoom()->doorsConnection[field]);
		resetAnimation();
		setPosition(map->getCameraX(), map->getCameraY());
		velocity.x = 0;
		velocity.y = 0;
		setAnimation(Stand);
		return;
	}
	else if (!field->ground())
		velocity.y = 0;

	if (!velocity.y && !velocity.x)
		setAnimation(Stand);
	else {
		if (unitActionName == Roll) {
			float dir = atan2(velocity.y, velocity.x);
			position.x += cos(dir) * rollSpeed;
			position.y += sin(dir) * rollSpeed;
			map->setCamera(int(position.x + srcrect.w * 3 / 4), int(position.y + srcrect.w * 1));
		}
		else {
			float dir = atan2(velocity.y, velocity.x);
			position.x += cos(dir) * speed;
			position.y += sin(dir) * speed;
			map->setCamera(int(position.x + srcrect.w * 3 / 4), int(position.y + srcrect.w * 1));
		}
	}

	updateFrame();
}

void Player::drawStatus() {
	statusDstRest.y = 5;
	statusSrcRect.y = 0;
	statusSrcRect.x = 0;
	int i;
	for (i = 1; i < hp; i += 2) {
		statusDstRest.x = (i / 2) * statusDstRest.w + 40;
		SDL_RenderCopy(Game::renderer, playerStatsTxt, &statusSrcRect, &statusDstRest);
	}
	if (int(hp) % 2) {
		statusSrcRect.x = statusSrcRect.w;
		statusDstRest.x = (int(hp) / 2) * statusDstRest.w + 40;
		SDL_RenderCopy(Game::renderer, playerStatsTxt, &statusSrcRect, &statusDstRest);
	}
	statusSrcRect.x = statusSrcRect.w * 2;
	for (i = hp + 1; i < maxHp; i += 2) {
		statusDstRest.x = i / 2 * statusDstRest.w + 40;
		SDL_RenderCopy(Game::renderer, playerStatsTxt, &statusSrcRect, &statusDstRest);
	}
}

void Player::movement(int x, int y) {
	velocity.x = x;
	velocity.y = y;
}

bool Player::attackPossible() {
	if (attackFrame == -1)
		return true;

	return false;
}

void Player::attack(std::list <Projectile*>& playerProjectiles, SDL_Texture* txt, int x, int y) {
	if (unitActionName == Roll)
		return;
	attackFrame = 0;

	Projectile* p = new Projectile(txt, 25, 25, 0, 3, 10);

	float dir = atan2(y - 17 - position.y, x - 17 - position.x);

	p->setDirection(dir);

	p->setPosition(position.x, position.y);
	playerProjectiles.push_back(p);
}

void Player::addAnimation(ActionType actionName, int _yPosTexture, int _frames, int _frameTime) {
	animations[actionName] = new Animation(_yPosTexture, _frames, _frameTime);
}

void Player::setAnimation(ActionType actionName) {
	if (unitActionName == actionName)
		return;

	if (actionName == Roll && (lastRollFramesAgo < rollCooldown || (velocity.x == 0 && velocity.y == 0)))
		return;

	if (unitActionName == Roll && lastRollFramesAgo < animations[Roll]->frames * animations[Roll]->frameTime)
		return;

	if (actionName == Roll) {
		rollVelocity.x = velocity.x;
		rollVelocity.y = velocity.y;
		lastRollFramesAgo = -1;
	}

	unitActionName = actionName;
	frameCounter = 0;
	textureY = animations[actionName]->yPosTexture;
	textureFrame = 0;
	textureFrameTime = animations[actionName]->frameTime;
	textureFrames = animations[actionName]->frames;

	srcrect.y = dstrect.h * textureY;
}

void Player::resetAnimation() {
	attackFrame = -1;
	lastRollFramesAgo = 100000;

	unitActionName = Stand;
	frameCounter = 0;
	textureY = animations[Stand]->yPosTexture;
	textureFrame = 0;
	textureFrameTime = animations[Stand]->frameTime;
	textureFrames = animations[Stand]->frames;

	srcrect.y = dstrect.h * textureY;
}

Player::Player(SDL_Texture* txt, SDL_Texture* _playerStatsTxt) : Unit(txt, 60, 60){
	addAnimation(Stand, 0, 2, 15);
	addAnimation(Walk, 1, 2, 15);
	addAnimation(Roll, 2, 4, 10);
	rollCooldown = 2 * 60;
	lastRollFramesAgo = rollCooldown;
	hp = 8;
	maxHp = 8;
	playerStatsTxt = _playerStatsTxt;
	attackSpeed = 31.5;
	attackFrames = 60 / attackSpeed;
	attackFrame = -1;

	statusSrcRect.w = 20;
	statusSrcRect.h = 20;
	statusDstRest.w = 40;
	statusDstRest.h = 40;
};


Player::~Player(){

}
