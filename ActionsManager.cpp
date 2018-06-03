#include "ActionsManager.h"
#include "UnitAction.h"
#include "GameObject.h"
#include "Unit.h"
#include "DataBase.h"


void ActionsManager::updateAction() {
	Direction::Name dirPast = actions[*currAction]->getDirection();

	if (actions[*currAction]->actionEnded()) { // Next action
		Direction::Name dirPast = actions[*currAction]->getDirection();

		do {
			if (++currAction == pattern.end()) // Last action
				currAction = pattern.begin();
		} while (actions[*currAction]->dynamicActivationOnly());

		actions[*currAction]->setFirstFrame();
	}

	if (velocity.x || velocity.y) {
		actions[*currAction]->setDirection(velocity.x, velocity.y);
	}
	else {
		if (!actions[*currAction]->dynamicActivationOnly())
			actions[*currAction]->setFirstFrame();

		actions[*currAction]->setDirection(dirPast);
	}

	actions[*currAction]->updateFrame();
}

void ActionsManager::onClosestObj(GameObject* closestObj, double closestObjDist) {
	if (closestObj && (!actions[*currAction]->dynamicActivationOnly() || actions[*currAction]->actionEnded())) {
		// Force change action
		std::vector<std::list<ActionType>::iterator> actionsToForceChange;
		std::list<ActionType>::iterator temp_itAction = currAction;
		do {
			if (++temp_itAction == pattern.end()) // Last action
				temp_itAction = pattern.begin();

			if (actions[*temp_itAction]->canDynamicActivation(closestObjDist))
				actionsToForceChange.push_back(temp_itAction);

		} while (temp_itAction != currAction);

		if (!actionsToForceChange.empty()) {
			if (std::find(actionsToForceChange.begin(), actionsToForceChange.end(), currAction) == actionsToForceChange.end()) {

				int sizeVector = actionsToForceChange.size();
				if (sizeVector == 1)
					changeAction(actionsToForceChange[0]);
				else
					changeAction(actionsToForceChange[rand() % actionsToForceChange.size()]);
			}
			else if (actions[*currAction]->actionEnded()) { // Current action was forced changed. Change to it once more
				int sizeVector = actionsToForceChange.size();
				if (sizeVector == 1)
					changeAction(actionsToForceChange[0]);
				else
					changeAction(actionsToForceChange[rand() % actionsToForceChange.size()]);

			}
			actions[*currAction]->setDirection(closestObj->getPositionX() - position.x, closestObj->getPositionY() - position.y);
		}
	}
}

void ActionsManager::addAction(ActionType action, Movement* move, AttackPattern* attack, int attackFrame) {
	actions[action] = new UnitAction(move, attack, attackFrame);
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
	currAction = actionIt;
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

void ActionsManager::setCurrentDirection(double x, double y) {
	actions[*currAction]->setDirection(x, y);
}

void ActionsManager::makeMove(Unit* unitToMove) {
	if (actions[*currAction]->movementExists())
		actions[*currAction]->makeMove();
	else {
		unitToMove->velocity.x = 0;
		unitToMove->velocity.y = 0;
	}
}

void ActionsManager::makeAttack(Unit* unit, std::list <AttackType*>& monsterAttacks, SDL_Point* attackPoint) {
	actions[*currAction]->makeAttack(unit, monsterAttacks, attackPoint);
}

ActionsManager::ActionsManager(SDL_Rect& srcRect, PointDouble& velocityObj, PointDouble& positionObj)
	: srcRectRef(srcRect), velocity(velocityObj), position(positionObj) {

}


ActionsManager::~ActionsManager() {

}
