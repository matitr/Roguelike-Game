#pragma once
#include "Unit.h"
#include "TextureManager.h"
#include "Attacks.h"
#include "Movements.h"

class UnitAction;

class MonRandMoveProjAround : public Unit {

public:
	MonRandMoveProjAround(Map* _map, Unit* _player) : Unit(TextureManager::textures[UNIT], 64, 64) {
		addAction(Walk, NULL, NULL, 8, 9, 20, 50);
		//		addAction(AttackProj, new MoveForwardPlayer(_map, _player), new ProjectileDirection(90, 4), 0, 2, 100, 50);
		addPattern(Walk);

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
