#pragma once
#include "Unit.h"
#include "TextureManager.h"
#include "Attacks.h"
#include "Movements.h"

class UnitAction;

class MonRandMoveProjAround : public Unit {

public:
	MonRandMoveProjAround(Map* _map, Unit* _player) : Unit(TextureManager::textures[PLAYER], 60, 60) {
		addAction(AttackProj, NULL, NULL, 0, 2, 100, 50);
		//		addAction(AttackProj, NULL, NULL, 0, 2, 100, 50);
//		addAction(Walk, NULL, NULL, 1, 2, 100);
//		addAction(Roll, NULL, NULL, 2, 4, 100);
		addPattern(AttackProj);
//		addPattern(Walk);
//		addPattern(Roll);

		setPositionShift(0.5, 0.9, 0.7);
	}

	~MonRandMoveProjAround() {}
};

class Boss1 : public Unit {
public:
	Boss1(Map* _map, Unit* _player) : Unit(TextureManager::textures[PLAYER], 60, 60) {
		addAction(AttackProj, new MoveForwardPlayer(_map, _player), new ProjectileDirection(90, 40), 0, 2, 100, 50);
		addPattern(AttackProj);

		setPositionShift(0.5, 0.9, 0.7);
	}

	~Boss1() {}
};
