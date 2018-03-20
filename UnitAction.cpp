#include "UnitAction.h"
#include "Attacks.h"
#include "Movements.h"


void UnitAction::makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks) {
	attack->makeAttack(unit, monsterAttacks);
}

void UnitAction::makeMove(Unit* unitToMove) {
	movement->makeMove(unitToMove);
}

UnitAction::UnitAction(ActionType _action, Movement* _move, Attack* _attack, int _yPosTexture, int _frames, int _frameTime, int _attackFrame, int _loops) {
	action = _action;
	movement = _move;
	attack = _attack;
	yPosTexture = _yPosTexture;
	frames = _frames;
	frameTime = _frameTime;
	attackFrame = _attackFrame;
	loops = _loops;
	currLoop = 0;
}


UnitAction::~UnitAction() {

}
