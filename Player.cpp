#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "DataBase.h"
#include "Attacks.h"
#include "Input.h"
#include "UnitAction.h"
#include <math.h>


bool Player::update(std::list <AttackType*>& playerProjectiles, Map* map, SDL_Rect& fieldRect) {
	if (isInteractionBlocked) {
		attack = false;
		velocity.x = 0;
		velocity.y = 0;
	}
	if (staticPassives[StaticPassiveName::numbOfProjectiles])
		attackP->setNumberOfProj(staticPassives[StaticPassiveName::numbOfProjectiles]);
	else
		attackP->setNumberOfProj(1);
	if (attackFrame == ATTACK_POSSIBLE)
		makeAttack(playerProjectiles, DataBase::animations[AnimationName::Projectile]);
	attackCancel = false;
	if (attackFrame > -1) {
		if (attackFrame + 1 == attackFrames)
			attackFrame = ATTACK_POSSIBLE;
		else
			attackFrame++;
	}

	if (lastRollFramesAgo < rollCooldown)
		lastRollFramesAgo++;

	if (actionsManager.currActionType() == Dash) {
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
//			setAnimation(Stand);
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
//			setAnimation(Stand);
			return true;
		}

	if (!velocity.y && !velocity.x)
		//		setAnimation(Stand);
		;
	else {
		double speedMultiplier = staticPassives[StaticPassiveName::unitSpeed] ? 1 + staticPassives[StaticPassiveName::unitSpeed] / 100 : 1;
		if (actionsManager.currActionType() == Dash) {
			float dir = atan2(velocity.y, velocity.x);
			position.x += cos(dir) * rollSpeed * speedMultiplier;
			position.y += sin(dir) * rollSpeed * speedMultiplier;
			map->setCamera(int(position.x), int(position.y));
		}
		else {
			float dir = atan2(velocity.y, velocity.x);
			position.x += cos(dir) * speed * speedMultiplier;
			position.y += sin(dir) * speed * speedMultiplier;
			map->setCamera(int(position.x), int(position.y));
		}
	}

	actionsManager.updateAction();

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

void Player::makeAttack(std::list <AttackType*>& playerProjectiles, AnimationDetails& animationD) {
	if (actionsManager.currActionType() == Dash || attackCancel)
		return;

	if (Input::mouseStates[SDL_BUTTON_LEFT]) {
		if (staticPassives[StaticPassiveName::chargeProjectiles]) {
			attack++;
			return;
		}
	}
	else {
		if (!staticPassives[StaticPassiveName::chargeProjectiles])
			return;
		else if (!attack)
			return;
	}


	attackFrame = 0;
	attack = 0;
	attackP->makeAttack(this, playerProjectiles, &attackPos);
}

//void Player::addAnimation(ActionType actionName, int _yPosTexture, int _frames, int _frameTime) {
//	animations[actionName] = new Animation(_yPosTexture, _frames, _frameTime);
//}

void Player::setAnimation(ActionType actionName) {
	if (actionsManager.currActionType() == actionName)
		return;

	if (actionName == Dash && (lastRollFramesAgo < rollCooldown || (velocity.x == 0 && velocity.y == 0)))
  		return;

	if (actionsManager.currActionType() == Dash)
		return;

	if (!actionsManager.changeActionType(actionName))
		return;

	if (actionName == Dash) {
		rollVelocity.x = velocity.x;
		rollVelocity.y = velocity.y;
		lastRollFramesAgo = -1;
	}
}

void Player::resetAnimation() {
	return;
	attackFrame = -1;
	lastRollFramesAgo = 100000;

	actionsManager.changeActionType(Stand);
	frameCounter = 0;
	textureY = animations[Stand]->yPosTexture;
	textureFrame = 0;
	textureFrameTime = animations[Stand]->frameTime;
	textureFrames = animations[Stand]->frames;

	srcRect.y = dstRect.h * textureY;
}

void Player::cancelAttack() {
	attackCancel = true;
}

void Player::takeMoney(int& m) {
	if (money - m < 0) 
		m = money - m; 
	
	money -= m; 
}

Player::Player(SDL_Texture* txt, SDL_Point& windowResolution) : Unit(TextureManager::textureParameters[SingleTexture::PlayerT]), playerIntentory(staticPassives, windowResolution) {
//	addAnimation(Stand, 10, 1, 15);
//	addAnimation(Walk, 1, 2, 15);
//	addAnimation(Dash, 2, 4, 10);

	actionsManager.addAction(Walk, NULL, NULL);
	actionsManager.addAnimation(Walk, Direction::N, DataBase::animations[AnimationName::PlayerWalkN]);
	actionsManager.addAnimation(Walk, Direction::E, DataBase::animations[AnimationName::PlayerWalkE]);
	actionsManager.addAnimation(Walk, Direction::S, DataBase::animations[AnimationName::PlayerWalkS]);
	actionsManager.addAnimation(Walk, Direction::W, DataBase::animations[AnimationName::PlayerWalkW]);

	actionsManager.addAction(Dash, NULL, NULL);
	actionsManager.addAnimation(Dash, Direction::N, DataBase::animations[AnimationName::DashN]);
	actionsManager.addAnimation(Dash, Direction::E, DataBase::animations[AnimationName::DashE]);
	actionsManager.addAnimation(Dash, Direction::S, DataBase::animations[AnimationName::DashS]);
	actionsManager.addAnimation(Dash, Direction::W, DataBase::animations[AnimationName::DashW]);
	actionsManager.setActionDynamicOnly(Dash);
	actionsManager.setStartingAction(Walk, Direction::S);
	actionsManager.addPattern(Walk);
	actionsManager.addPattern(Dash);

	rollCooldown = 2 * 60;
	lastRollFramesAgo = rollCooldown;
	hp = 8;
	maxHp = 8;
	money = 0;
	playerStatsTxt = TextureManager::textures[TextureFile::PLAYER_STATS];
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
	attackP = new MultipleProjectiles(DataBase::animations[AnimationName::Projectile], 5);

	setPositionShift(0.5, 0.8, 0.55);
	setAnimation(Walk);
	setAnimation(Stand);
};


Player::~Player(){

}
