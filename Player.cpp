#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "DataBase.h"
#include "Attacks.h"
#include "Input.h"
#include "UnitAction.h"
#include "PassivesManager.h"
#include "Passive.h"
#include <math.h>


bool Player::update(std::list <AttackType*>& playerProjectiles, Map* map, SDL_Rect& fieldRect) {
	if (staticPassives[StaticPassiveName::hp] <= 0) {
		passivesManager->activatePassives(PassiveActivateOn::Death, playerProjectiles);
	}

	if (staticPassives[StaticPassiveName::hp] <= 0) {
		isAlive = false;
		return actionsManager.updateDeathAction(this, playerProjectiles, &attackPos);
	}

	passivesManager->activatePassives(PassiveActivateOn::Passive, playerProjectiles);
	passivesManager->updateAllPassives(this);
	speed = staticPassives[StaticPassiveName::unitSpeed];
	if (isInteractionBlocked) {
		attack = false;
		velocity.x = 0;
		velocity.y = 0;
	}
	if (!attack) {
		attackPos.x = Input::mousePosX + map->getStartRender().x;
		attackPos.y = Input::mousePosY + map->getStartRender().y;
	}
	if (staticPassives[StaticPassiveName::numbOfProjectiles])
		attackP->setNumberOfProj((int)staticPassives[StaticPassiveName::numbOfProjectiles]);
	else
		attackP->setNumberOfProj(1);
	if (attackFrame == ATTACK_POSSIBLE)
		makeAttack(playerProjectiles, DataBase::animations[AnimationName::Projectile]);
	attackCancel = false;
	if (attackFrame > -1) {
		if (attackFrame + 1 == int(60 / (attackSpeed + attackSpeed * (1 + staticPassives[StaticPassiveName::attackSpeedMult]))))
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

	unitDetectedCollisionUnit = false;
	unitDetectedCollisionWall = false;

	Field *field = nullptr;
	// Check if player have collision with door. Change room
	if (velocity.x < 0)
		field = map->getField(int(position.x - radius - speed) / fieldRect.w, int(position.y) / fieldRect.h);
	else if (velocity.x > 0)
		field = map->getField(int(position.x + radius + speed) / fieldRect.w, int(position.y) / fieldRect.h);

	if (velocity.x != 0)
		if (field->type() == FieldType::Door && !map->currentRoom()->battle) {
			const PointInt& fieldPos = field->getFieldPos();
			const PointInt& fieldToMovePos = map->currentRoom()->doorsConnection[fieldPos];
			map->changeRoom(map->currentRoom()->roomConnection[fieldPos], map->getField(fieldToMovePos.x, fieldToMovePos.y));
			setPosition(map->getCameraX(), map->getCameraY());
			velocity.x = 0;
			velocity.y = 0;
//			setAnimation(Idle);
			return true;
		}

	if (velocity.y < 0)
		field = map->getField(int(position.x) / fieldRect.w, int(position.y - radius - speed) / fieldRect.h);
	else if (velocity.y > 0)
		field = map->getField(int(position.x) / fieldRect.w, int(position.y + radius + speed) / fieldRect.h);

	if (velocity.y != 0)
		if (field->type() == FieldType::Door && !map->currentRoom()->battle) {
			const PointInt& fieldPos = field->getFieldPos();
			const PointInt& fieldToMovePos = map->currentRoom()->doorsConnection[fieldPos];
			map->changeRoom(map->currentRoom()->roomConnection[fieldPos], map->getField(fieldToMovePos.x, fieldToMovePos.y));
			setPosition(map->getCameraX(), map->getCameraY());
			velocity.x = 0;
			velocity.y = 0;
//			setAnimation(Idle);
			return true;
		}

	if (!velocity.y && !velocity.x)
		//		setAnimation(Idle);
		;
	else { // Make move
		if (actionsManager.currActionType() == Dash) { // Dash
			float dir = (float)atan2(velocity.y, velocity.x);
			position.x += cos(dir) * rollSpeed * (1 + staticPassives[StaticPassiveName::unitSpeedMult]);
			position.y += sin(dir) * rollSpeed * (1 + staticPassives[StaticPassiveName::unitSpeedMult]);
			map->setCamera(int(position.x), int(position.y));
		}
		else { // Normal move
			float dir = (float)atan2(velocity.y, velocity.x);
			position.x += cos(dir) * speed * (1 + staticPassives[StaticPassiveName::unitSpeedMult]);
			position.y += sin(dir) * speed * (1 + staticPassives[StaticPassiveName::unitSpeedMult]);
			map->setCamera(int(position.x), int(position.y));
		}
	}

	actionsManager.updateAction(velocity);

	return true;
}

void Player::drawStatus() {
	statusDstRest.x = 5;
	statusDstRest.y = 5;
	statusSrcRect.y = 0;
	statusSrcRect.x = 0;

	SDL_RenderCopy(Game::renderer, playerStatsTxt, &statusSrcRect, &statusDstRest);
	int width = statusSrcRect.w;
	statusDstRest.w = int((statusDstRest.w - 4) * (staticPassives[StaticPassiveName::hp] / staticPassives[StaticPassiveName::hpMax]));
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

	if (!attack)
		return;

	if (Input::mouseStates[SDL_BUTTON_LEFT]) {
		if (staticPassives[StaticPassiveName::chargeProjectiles]) {
			return;
		}
	}
	else {
		if (!staticPassives[StaticPassiveName::chargeProjectiles])
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

Player::Player(SDL_Texture* txt, SDL_Point& windowResolution) : Unit(TextureManager::textureParameters[SingleTexture::PlayerT], UnitType::Player), playerIntentory(passivesManager, windowResolution) {
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

	passivesManager->setStartingStat(StaticPassiveName::damage, 1);
	passivesManager->setStartingStat(StaticPassiveName::hp, 899);
	passivesManager->setStartingStat(StaticPassiveName::hpMax, 899);
	passivesManager->setStartingStat(StaticPassiveName::unitSpeed, 4);

	money = 0;
	playerStatsTxt = TextureManager::textures[TextureFile::PLAYER_STATS];
	attackSpeed = 3;
	attackFrames = int(60 / attackSpeed);
	attackFrame = -1;

	statusSrcRect.w = 200;
	statusSrcRect.h = 30;
	statusDstRest.w = 200;
	statusDstRest.h = 30;
	rollSpeed = 6;

	attack = false;
	attackP = new MultipleProjectiles(DataBase::animations[AnimationName::Projectile], 5);

	setPositionShift(0.5f, 0.8f, 0.55f);
	setAnimation(Walk);
	setAnimation(Idle);
};


Player::~Player(){
	if (attackP)
		delete attackP;
}
