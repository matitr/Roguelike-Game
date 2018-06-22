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
		attackP->setNumberOfProj((int)staticPassives[StaticPassiveName::numbOfProjectiles] + 1);
	else
		attackP->setNumberOfProj(1);
	if (attackFrame == ATTACK_POSSIBLE)
		makeAttack(playerProjectiles, DataBase::animations[AnimationName::Projectile]);
	attackCancel = false;
	if (attackFrame > -1) {
		if (attackFrame + 1 == int(60 / (attackSpeed + attackSpeed * staticPassives[StaticPassiveName::attackSpeed] / 100)))
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
	// Check if player have collision with door. Change room
	if (velocity.x < 0)
		field = map->getField(int(position.x - radius - speed) / fieldRect.w, int(position.y) / fieldRect.h);
	else if (velocity.x > 0)
		field = map->getField(int(position.x + radius + speed) / fieldRect.w, int(position.y) / fieldRect.h);

	if (velocity.x != 0)
		if (field->type() == Door && !map->currentRoom()->battle) {
			Field * f = map->currentRoom()->doorsConnection[field];
			map->changeRoom(map->currentRoom()->roomConnection[field], map->currentRoom()->doorsConnection[field]);
			setPosition(map->getCameraX(), map->getCameraY());
			velocity.x = 0;
			velocity.y = 0;
//			setAnimation(Stand);
			return true;
		}

	if (velocity.y < 0)
		field = map->getField(int(position.x) / fieldRect.w, int(position.y - radius - speed) / fieldRect.h);
	else if (velocity.y > 0)
		field = map->getField(int(position.x) / fieldRect.w, int(position.y + radius + speed) / fieldRect.h);

	if (velocity.y != 0)
		if (field->type() == Door && !map->currentRoom()->battle) {
			map->changeRoom(map->currentRoom()->roomConnection[field], map->currentRoom()->doorsConnection[field]);
			setPosition(map->getCameraX(), map->getCameraY());
			velocity.x = 0;
			velocity.y = 0;
//			setAnimation(Stand);
			return true;
		}

	if (!velocity.y && !velocity.x)
		//		setAnimation(Stand);
		;
	else { // Make move
		double speedMultiplier = staticPassives[StaticPassiveName::unitSpeed] ? 1 + staticPassives[StaticPassiveName::unitSpeed] / 100 : 1;
		if (actionsManager.currActionType() == Dash) { // Dash
			float dir = (float)atan2(velocity.y, velocity.x);
			position.x += cos(dir) * rollSpeed * speedMultiplier;
			position.y += sin(dir) * rollSpeed * speedMultiplier;
			map->setCamera(int(position.x), int(position.y));
		}
		else { // Normal move
			float dir = (float)atan2(velocity.y, velocity.x);
			position.x += cos(dir) * speed * speedMultiplier;
			position.y += sin(dir) * speed * speedMultiplier;
			map->setCamera(int(position.x), int(position.y));
		}
	}

	actionsManager.updateAction();

	return true;
}

void Player::drawStatus() {
	statusDstRest.x = 5;
	statusDstRest.y = 5;
	statusSrcRect.y = 0;
	statusSrcRect.x = 0;

	SDL_RenderCopy(Game::renderer, playerStatsTxt, &statusSrcRect, &statusDstRest);
	int width = statusSrcRect.w;
	statusDstRest.w = int((statusDstRest.w - 4) * (hp / 8.0));
	statusSrcRect.w = statusDstRest.w;
	statusSrcRect.y = 30;
	SDL_RenderCopy(Game::renderer, playerStatsTxt, &statusSrcRect, &statusDstRest);

	statusDstRest.w = width;
	statusSrcRect.w = width;

	// Draw attack charge
	if (attack) {
		int chargeBarWidth = 60;
		int chargeBarHeight = 10;

		SDL_Rect chargeBar = {
			dstRect.x + dstRect.w / 2 - chargeBarWidth / 2,
			dstRect.y - chargeBarHeight - 4,
			chargeBarWidth, chargeBarHeight
		};

		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(Game::renderer, &chargeBar);
		SDL_SetRenderDrawColor(Game::renderer, 0, 102, 255, 255);
		chargeBar.x++;
		chargeBar.y++;

		chargeBar.w -= 2;
		chargeBar.h -= 2;
		double chargeTime = attack / (2 * 60 / attackSpeed);
		if (chargeTime > 1.0) {
			chargeTime = 1.0;
			SDL_SetRenderDrawColor(Game::renderer, 0, 51, 204, 255);
		}
		chargeBar.w = int(chargeBar.w * chargeTime);
		SDL_RenderFillRect(Game::renderer, &chargeBar);
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
	attack++;
}

void Player::makeAttack(std::list <AttackType*>& playerProjectiles, AnimationDetails& animationD) {
	if (actionsManager.currActionType() == Dash || attackCancel) {
		attack = false;
		return;
	}

	if (Input::mouseStates[SDL_BUTTON_LEFT]) {
		if (staticPassives[StaticPassiveName::chargeProjectiles]) {
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

void Player::cancelAttack() {
	attackCancel = true;
}

void Player::takeMoney(int& m) {
	if (money - m < 0) 
		m = money - m; 
	
	money -= m; 
}

Player::Player(SDL_Texture* txt, SDL_Point& windowResolution) : Unit(TextureManager::textureParameters[SingleTexture::PlayerT]), playerIntentory(staticPassives, windowResolution) {
	actionsManager.addAction(Walk, NULL, NULL);
	actionsManager.addAnimations(Walk, DataBase::unitAnimations[UnitName::Unit][Walk]);

	actionsManager.addAction(Dash, NULL, NULL);
	actionsManager.addAnimations(Dash, DataBase::unitAnimations[UnitName::Unit][Walk]);

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
	attackSpeed = 3;
	attackFrames = int(60 / attackSpeed);
	attackFrame = -1;

	statusSrcRect.w = 200;
	statusSrcRect.h = 30;
	statusDstRest.w = 200;
	statusDstRest.h = 30;
	speed = 4;
	rollSpeed = 10;

	attack = false;
	attackP = new MultipleProjectiles(DataBase::animations[AnimationName::Projectile], 5);

	setPositionShift(0.5f, 0.8f, 0.55f);
	setAnimation(Walk);
	setAnimation(Stand);
};


Player::~Player(){
	if (attackP)
		delete attackP;
}
