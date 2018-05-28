#pragma once
#include "Unit.h"
#include "TextureManager.h"
#include "Attacks.h"
#include "Movements.h"
#include "DataBase.h"

class UnitAction;

class MonRandMoveProjAround : public Unit {

public:
	MonRandMoveProjAround(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::UnitT]) {
		addAction(Walk, new MoveForwardPlayer(_map, _player), NULL, 50);
		addAnimation(Walk, Direction::N, DataBase::animations[AnimationName::PlayerWalkN]);
		addAnimation(Walk, Direction::E, DataBase::animations[AnimationName::PlayerWalkE]);
		addAnimation(Walk, Direction::S, DataBase::animations[AnimationName::PlayerWalkS]);
		addAnimation(Walk, Direction::W, DataBase::animations[AnimationName::PlayerWalkW]);

		addAction(Attack, NULL, NULL, 50);
		addAnimation(Attack, Direction::N, DataBase::animations[AnimationName::SlashN]);
		addAnimation(Attack, Direction::W, DataBase::animations[AnimationName::SlashW]);
		addAnimation(Attack, Direction::S, DataBase::animations[AnimationName::SlashS]);
		addAnimation(Attack, Direction::E, DataBase::animations[AnimationName::SlashE]);
		setActionDistActivation(Attack, 5);
		setStartingAction(Walk, Direction::S);

		addPattern(Walk);
		addPattern(Attack);
//		addAnimation
		//		addAction(AttackProj, new MoveForwardPlayer(_map, _player), new ProjectileDirection(90, 4), 0, 2, 100, 50);

		setPositionShift(0.5, 0.9, 0.7);
	}

	~MonRandMoveProjAround() {}
};

class Boss1 : public Unit {
public:
	Boss1(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::UnitT]) {
		addAction(Walk, new MoveForwardPlayer(_map, _player), new ProjectileDirection(90, 40), 1);
		addAnimation(Walk, Direction::N, DataBase::animations[AnimationName::PlayerWalkN]);
		addAnimation(Walk, Direction::E, DataBase::animations[AnimationName::PlayerWalkE]);
		addAnimation(Walk, Direction::S, DataBase::animations[AnimationName::PlayerWalkS]);
		addAnimation(Walk, Direction::W, DataBase::animations[AnimationName::PlayerWalkW]);

		addAction(Attack, NULL, new MultipleProjectiles(5), 1);
		addAnimation(Attack, Direction::N, DataBase::animations[AnimationName::SlashN]);
		addAnimation(Attack, Direction::W, DataBase::animations[AnimationName::SlashE]);
		addAnimation(Attack, Direction::S, DataBase::animations[AnimationName::SlashS]);
		addAnimation(Attack, Direction::E, DataBase::animations[AnimationName::SlashW]);

		addPattern(Walk);
		addPattern(Attack);

		setStartingAction(Walk, Direction::S);
		setPositionShift(0.5, 0.9, 0.7);
	}

	~Boss1() {}
};
