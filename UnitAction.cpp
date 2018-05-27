#include "UnitAction.h"
#include "Attacks.h"
#include "Movements.h"


void UnitAction::makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks, SDL_Point* attackPoint) {
	attack->makeAttack(unit, monsterAttacks, attackPoint);
}

void UnitAction::makeMove(Unit* unitToMove) {
	movement->makeMove(unitToMove);
}

UnitAction::UnitAction( Movement* _move, AttackPattern* _attack, int _yPosTexture, int _frames, int _frameTime, int _attackFrame) {
	movement = _move;
	attack = _attack;
	yPosTexture = _yPosTexture;
	frames = _frames;
	frameTime = _frameTime;
	attackFrame = _attackFrame;

	framesInRow = _frames;
}


UnitAction::~UnitAction() {

}
