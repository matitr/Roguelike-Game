#pragma once
#include "Unit.h"
#include "TextureManager.h"
#include "Attacks.h"
#include "Movements.h"
#include "DataBase.h"

class UnitAction;

class MonRandMoveProjAround : public Unit {

public:
	MonRandMoveProjAround(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::PlayerT]) {
		addAction(Walk, new MoveForwardPlayer(_map, _player), NULL, 50);
		addAnimation(Walk, Direction::N, DataBase::animations[AnimationName::PlayerWalkN]);
		addAnimation(Walk, Direction::E, DataBase::animations[AnimationName::PlayerWalkE]);
		addAnimation(Walk, Direction::S, DataBase::animations[AnimationName::PlayerWalkS]);
		addAnimation(Walk, Direction::W, DataBase::animations[AnimationName::PlayerWalkW]);
		setStartingAction(Walk, Direction::S);
		addPattern(Walk);
//		addAnimation
		//		addAction(AttackProj, new MoveForwardPlayer(_map, _player), new ProjectileDirection(90, 4), 0, 2, 100, 50);

		setPositionShift(0.5, 0.9, 0.7);
	}

	~MonRandMoveProjAround() {}
};

class Boss1 : public Unit {
public:
	Boss1(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::PlayerT]) {
		addAction(AttackProj, new MoveForwardPlayer(_map, _player), new ProjectileDirection(90, 40), 50);
		addPattern(AttackProj);

		setPositionShift(0.5, 0.9, 0.7);
	}

	~Boss1() {}
};
