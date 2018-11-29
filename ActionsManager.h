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
class Map;
struct AnimationDetails;
struct PointInt;
enum Name;

enum ActionType { Idle, Death, Walk, Dash, AttackProj, Attack };
struct PointDouble;

class ActionsManager {
	std::unordered_map <ActionType, UnitAction*> actions;

	std::list<ActionType> pattern; // Actions order
	std::list<ActionType>::iterator currAction;
	bool actionChanged = true;

	int checkClearPathCooldown;
	int checkClearPathCurrCooldown;
	Unit* unitParent;
	SDL_Rect& srcRectRef;
	const float& moveSpeedMult;
	const float& attackSpeedMult;
public:
	void onClosestObj(Map* map, GameObject* closestObj, double closestObjDist, const PointDouble& position);
	void updateAction(const PointDouble& velocity);

	void addAction(ActionType action, Movement* move, AttackPattern* attack, int attackFrame = -1);
	void addAction(ActionType actionName, UnitAction* action);
	void addAnimations(ActionType actionName, std::array<AnimationDetails, Direction::enum_size>& animationsToAdd);
	void addPattern(ActionType actionType);
	void setStartingAction(ActionType action, Direction::Name dir);

	void setActionActivationDistMax(ActionType action, double dist);
	void setActionActivationDistMin(ActionType action, double dist);
	void setActionDynamicOnly(ActionType action);
	void changeAction(std::list<ActionType>::iterator actionIt);
	bool changeActionType(ActionType action);

	bool updateDeathAction(Unit* unit, std::list <AttackType*>& monsterAttacks, PointInt* attackPoint);

	ActionType currActionType() { return *currAction; }
	void setCurrentDirection(double x, double y);

	void makeMove(Unit* unitToMove);
	void updateMove();
	void makeAttack(Unit* unit, std::list <AttackType*>& monsterAttacks, PointInt* attackPoint);

	ActionsManager(SDL_Rect& srcRect, float& unitMoveSpeedMult, float& unitAttackSpeedMult, Unit* unit);
	~ActionsManager();
};

