#pragma once
#include <unordered_map>
#include <list>
#include "TextureManager.h"


class UnitAction;
class AttackPattern;
class GameObject;
class Movement;
class Unit;
class AttackType;
struct AnimationDetails;
enum Name;

enum ActionType { Stand, Walk, Dash, AttackProj, Attack };
struct PointDouble;

class ActionsManager {
	std::unordered_map <ActionType, UnitAction*> actions;

	std::list<ActionType> pattern;
	std::list<ActionType>::iterator currAction;

	SDL_Rect& srcRectRef;
	const PointDouble& velocity;
	const PointDouble& position;
public:
	void onClosestObj(GameObject* closestObj, double closestObjDist);
	void updateAction();

	void addAction(ActionType action, Movement* move, AttackPattern* attack, int attackFrame = -1);
	void addAnimation(ActionType action, Direction::Name dir, AnimationDetails& animationD);
	void addAnimations(ActionType action, std::array<AnimationDetails, Direction::enum_size>& animations);
	void addPattern(ActionType actionType);
	void setStartingAction(ActionType action, Direction::Name dir);

	void setActionActivationDistMax(ActionType action, double dist);
	void setActionActivationDistMin(ActionType action, double dist);
	void setActionDynamicOnly(ActionType action);
	void changeAction(std::list<ActionType>::iterator actionIt);
	bool changeActionType(ActionType action);

	ActionType currActionType() { return *currAction; }
	void setCurrentDirection(double x, double y);

	void makeMove(Unit* unitToMove);
	void makeAttack(Unit* unit, std::list <AttackType*>& monsterAttacks, SDL_Point* attackPoint);

	ActionsManager(SDL_Rect& srcRect, PointDouble& velocityObj, PointDouble& positionObj);
	~ActionsManager();
};

