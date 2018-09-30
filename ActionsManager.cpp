#include "ActionsManager.h"
#include "UnitAction.h"
#include "GameObject.h"
#include "Unit.h"
#include "DataBase.h"
#include "Movements.h"
#include "myMath.h"
#include "Map.h"


void ActionsManager::updateAction(const PointDouble& velocity) {
	Direction::Name dirPast = actions[*currAction]->getDirection();

	if (actions[*currAction]->actionEnded()) { // Next action
		Direction::Name dirPast = actions[*currAction]->getDirection();

		do {
			if (++currAction == pattern.end()) // Last action
				currAction = pattern.begin();
		} while (actions[*currAction]->dynamicActivationOnly());

		changeAction(currAction);
	}

	if (velocity.x || velocity.y) {
		actions[*currAction]->setDirection(velocity.x, velocity.y);
	}
	else {
		if (!actions[*currAction]->dynamicActivationOnly()) // Idle
			actions[*currAction]->setFirstFrame();

		actions[*currAction]->setDirection(dirPast);
	}

	if (!actionChanged)
		actions[*currAction]->updateFrame(moveSpeedMult, attackSpeedMult);

	std::unordered_map <ActionType, UnitAction*>::iterator it_action = actions.begin();
	for (it_action; it_action != actions.end(); it_action++)
		it_action->second->updateCooldown();

	actionChanged = false;
}

void ActionsManager::onClosestObj(Map* map, GameObject* closestObj, double closestObjDist, const PointDouble& position) {
	if (closestObj && (!actions[*currAction]->dynamicActivationOnly() || actions[*currAction]->actionEnded())) {
		// Force change action
		std::vector<std::list<ActionType>::iterator> actionsToForceChange;
		std::list<ActionType>::iterator temp_itAction = currAction;
		do {
			if (++temp_itAction == pattern.end()) // Last action
				temp_itAction = pattern.begin();

			if (actions[*temp_itAction]->canDynamicActivation(closestObjDist)
				&& (!actions[*temp_itAction]->clearPathRequired() || (checkClearPathCurrCooldown == -1 && map->checkClearPath(unitParent, closestObj)))) {
				actionsToForceChange.push_back(temp_itAction);
				checkClearPathCurrCooldown = checkClearPathCooldown;
			}

		} while (temp_itAction != currAction);

		if (!actionsToForceChange.empty()) {
			if (std::find(actionsToForceChange.begin(), actionsToForceChange.end(), currAction) == actionsToForceChange.end() 
				|| actions[*currAction]->actionEnded()) { // Current action was forced changed. Change to it once more

				if (actionsToForceChange.size() == 1)
					changeAction(actionsToForceChange[0]);
				else
					changeAction(actionsToForceChange[rand() % actionsToForceChange.size()]);
			}

			actions[*currAction]->resetMove();
			actions[*currAction]->setDirection(closestObj->getPositionX() - position.x, closestObj->getPositionY() - position.y);
		}
	}

	if (checkClearPathCurrCooldown > -1)
		checkClearPathCurrCooldown--;
}

void ActionsManager::addAction(ActionType action, Movement* move, AttackPattern* attack, int attackFrame) {
	actions[action] = new UnitAction(move, attack, attackFrame);
}

void ActionsManager::addAction(ActionType actionName, UnitAction* action) {
	actions[actionName] = action;
}

void ActionsManager::addAnimation(ActionType action, Direction::Name dir, AnimationDetails& animationD) {
	actions[action]->addAnimation(dir, animationD, srcRectRef);
}

void ActionsManager::addAnimations(ActionType action, std::array<AnimationDetails, Direction::enum_size>& animations) {
	for (int i = 0; i < Direction::enum_size; i++) {
		actions[action]->addAnimation(Direction::Name(i), animations[i], srcRectRef);
	}
}

void  ActionsManager::addPattern(ActionType actionType) {
	if (pattern.empty()) {
		pattern.push_back(actionType);
		currAction = pattern.begin();
	}
	else
		pattern.push_back(actionType);
}

void ActionsManager::setStartingAction(ActionType action, Direction::Name dir) {
	actions[action]->setDirection(dir);
	actions[action]->setFirstFrame();
}

void ActionsManager::setActionActivationDistMax(ActionType action, double dist) {
	actions[action]->setDistActivationMax(dist);
}

void ActionsManager::setActionActivationDistMin(ActionType action, double dist) {
	actions[action]->setDistActivationMin(dist);
}

void ActionsManager::setActionDynamicOnly(ActionType action) {
	actions[action]->setDynamicActivationOnly();
}

void ActionsManager::changeAction(std::list<ActionType>::iterator actionIt) {
	actions[*actionIt]->setFirstFrame();
	actions[*actionIt]->setDirection(*actions[*currAction]);
	actions[*actionIt]->resetCooldown();
	actions[*actionIt]->resetMove();
	currAction = actionIt;
	actionChanged = true;
}

bool ActionsManager::changeActionType(ActionType action) {
	std::list<ActionType>::iterator it_found = std::find(pattern.begin(), pattern.end(), action);

	if (it_found == pattern.end())
		return false;

	actions[*it_found]->setFirstFrame();
	actions[*it_found]->setDirection(*actions[*currAction]);
	currAction = it_found;
	return true;
}

bool ActionsManager::updateDeathAction(Unit* unit, std::list <AttackType*>& monsterAttacks, PointInt* attackPoint) {
	actionChanged = true;

	if (actionChanged) {
		actionChanged = false;
		std::unordered_map <ActionType, UnitAction*>::iterator it_found = actions.find(ActionType::Death);

		if (it_found == actions.end())
			return false;

		if (!(*it_found).second->animationsExists()) {
			if (actions[ActionType::Death]->attackExists())
				actions[ActionType::Death]->getAttack()->makeAttack(unit, monsterAttacks, attackPoint);

			return false;
		}

		actions[ActionType::Death]->setFirstFrame();
	}
	else {
		if (actions[ActionType::Death]->actionEnded())
			return false;

		actions[ActionType::Death]->updateFrame(0.0f, 0.0f);
	}

	actions[ActionType::Death]->makeAttack(unit, monsterAttacks, attackPoint, 0.0f);
	return true;
}

void ActionsManager::setCurrentDirection(double x, double y) {
	actions[*currAction]->setDirection(x, y);
}

void ActionsManager::makeMove(Unit* unitToMove) {
	if (actions[*currAction]->movementExists()) {
		actions[*currAction]->makeMove();
		unitToMove->setSpeed(actions[*currAction]->getMovement()->movementSpeed(unitToMove));
	}
	else {
		unitToMove->velocity.x = 0;
		unitToMove->velocity.y = 0;
	}
}

void ActionsManager::updateMove() {
	actions[*currAction]->updateMove();
}

void ActionsManager::makeAttack(Unit* unit, std::list <AttackType*>& monsterAttacks, PointInt* attackPoint) {
	actions[*currAction]->makeAttack(unit, monsterAttacks, attackPoint, attackSpeedMult);
}

ActionsManager::ActionsManager(SDL_Rect& srcRect, float& unitMoveSpeedMult, float& unitAttackSpeedMult, Unit* unit)
	: srcRectRef(srcRect), moveSpeedMult(unitMoveSpeedMult), attackSpeedMult(unitAttackSpeedMult), unitParent(unit) {

	checkClearPathCooldown = 3 + rand() % 3;
	checkClearPathCurrCooldown = 0;
}


ActionsManager::~ActionsManager() {
	std::unordered_map <ActionType, UnitAction*>::iterator it = actions.begin();

	for (it; it != actions.end(); it++)
		delete it->second;
}
