#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "DataBase.h"
#include <math.h>


bool Player::update(std::list <Projectile*>& playerProjectiles, Map* map, SDL_Rect& fieldRect) {
	if (isInteractionBlocked) {
		attack = false;
		velocity.x = 0;
		velocity.y = 0;
	}

	if (attackFrame == ATTACK_POSSIBLE && attack)
		makeAttack(playerProjectiles, DataBase::animations[AnimationName::Projectile]);
	attack = false;

	if (attackFrame > -1) {
		if (attackFrame + 1 == attackFrames)
			attackFrame = ATTACK_POSSIBLE;
		else
			attackFrame++;
	}

	if (lastRollFramesAgo < rollCooldown)
		lastRollFramesAgo++;

	if (unitActionName == Roll) {
		velocity.x = rollVelocity.x;
		velocity.y = rollVelocity.y;
	}

	Field *field = nullptr;

	if (velocity.x < 0)
		field = map->map[(position.x - radius - speed) / fieldRect.w][(position.y) / fieldRect.h];
	else if (velocity.x > 0)
		field = map->map[(position.x + radius + speed) / fieldRect.w][(position.y) / fieldRect.h];

	if (velocity.x != 0)
		if (field->type() == Door && !map->currentRoom()->battle) {
			Field * f = map->currentRoom()->doorsConnection[field];
			map->changeRoom(map->currentRoom()->roomConnection[field], map->currentRoom()->doorsConnection[field]);
			resetAnimation();
			setPosition(map->getCameraX(), map->getCameraY());
			velocity.x = 0;
			velocity.y = 0;
			setAnimation(Stand);
			return true;
		}

	if (velocity.y < 0)
		field = map->map[(position.x) / fieldRect.w][(position.y - radius - speed) / fieldRect.h];
	else if (velocity.y > 0)
		field = map->map[(position.x) / fieldRect.w][(position.y + radius + speed) / fieldRect.h];

	if (velocity.y != 0)
		if (field->type() == Door && !map->currentRoom()->battle) {
			map->changeRoom(map->currentRoom()->roomConnection[field], map->currentRoom()->doorsConnection[field]);
			resetAnimation();
			setPosition(map->getCameraX(), map->getCameraY());
			velocity.x = 0;
			velocity.y = 0;
			setAnimation(Stand);
			return true;
		}

	if (!velocity.y && !velocity.x)
		setAnimation(Stand);
	else {
		if (unitActionName == Roll) {
			float dir = atan2(velocity.y, velocity.x);
			position.x += cos(dir) * rollSpeed;
			position.y += sin(dir) * rollSpeed;
			map->setCamera(int(position.x), int(position.y));
		}
		else {
			float dir = atan2(velocity.y, velocity.x);
			position.x += cos(dir) * speed;
			position.y += sin(dir) * speed;
			map->setCamera(int(position.x), int(position.y));
		}
	}

	updateFrame();
	return true;
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
	if (attackFrame == ATTACK_POSSIBLE)
		return true;

	return false;
}

void Player::attackPressed(int x, int y) {
	attackPos.x = x;
	attackPos.y = y;
	attack = true;
}

void Player::makeAttack(std::list <Projectile*>& playerProjectiles, AnimationDetails& animationD) {
	if (unitActionName == Roll)
		return;
	attackFrame = 0;

	Projectile* p = new Projectile(animationD, staticPassives);

	float dir = atan2((attackPos.y - position.y), (attackPos.x - position.x));

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

	srcRect.y = dstRect.h * textureY;
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

	srcRect.y = dstRect.h * textureY;
}

void Player::cancelAttack() {
	attack = false;
}

void Player::takeMoney(int& m) {
	if (money - m < 0) 
		m = money - m; 
	
	money -= m; 
}

Player::Player(SDL_Texture* txt, SDL_Point& windowResolution) : Unit(txt, 60, 60), playerIntentory(staticPassives, windowResolution) {
	addAnimation(Stand, 0, 2, 15);
	addAnimation(Walk, 1, 2, 15);
	addAnimation(Roll, 2, 4, 10);

	rollCooldown = 2 * 60;
	lastRollFramesAgo = rollCooldown;
	hp = 8;
	maxHp = 8;
	money = 0;
	playerStatsTxt = TextureManager::textures[PLAYER_STATS];
	attackSpeed = 9.5;
	attackFrames = 60 / attackSpeed;
	attackFrame = -1;

	statusSrcRect.w = 20;
	statusSrcRect.h = 20;
	statusDstRest.w = 40;
	statusDstRest.h = 40;
	speed = 5;
	rollSpeed = 10;

	attack = false;

	setPositionShift(0.5, 0.9, 0.7);
	setAnimation(Walk);
	setAnimation(Stand);
};


Player::~Player(){

}
