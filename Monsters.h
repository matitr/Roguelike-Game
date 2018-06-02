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
		staticPassives[StaticPassiveName::projectileSpeed] = 0.5;
//		actionsManager.addAction(Walk, new MoveForwardPlayer(_map, _player), new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 5), 1);
		actionsManager.addAction(Walk, new MoveForwardPlayer(_map, _player), NULL, 1);
		actionsManager.addAnimation(Walk, Direction::N, DataBase::animations[AnimationName::PlayerWalkN]);
		actionsManager.addAnimation(Walk, Direction::E, DataBase::animations[AnimationName::PlayerWalkE]);
		actionsManager.addAnimation(Walk, Direction::S, DataBase::animations[AnimationName::PlayerWalkS]);
		actionsManager.addAnimation(Walk, Direction::W, DataBase::animations[AnimationName::PlayerWalkW]);

		actionsManager.addAction(AttackProj, new NoMoveFaceEnemy(_player), new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 1), 9);
//		actionsManager.addAnimation(AttackProj, Direction::N, DataBase::animations[AnimationName::SlashN]);
//		actionsManager.addAnimation(AttackProj, Direction::W, DataBase::animations[AnimationName::SlashW]);
//		actionsManager.addAnimation(AttackProj, Direction::S, DataBase::animations[AnimationName::SlashS]);
//		actionsManager.addAnimation(AttackProj, Direction::E, DataBase::animations[AnimationName::SlashE]);
		actionsManager.addAnimations(AttackProj, DataBase::unitAnimations[UnitName::Unit][AttackProj]);
		actionsManager.setActionActivationDistMax(AttackProj, 500);
		actionsManager.setActionActivationDistMin(AttackProj, 50);

		actionsManager.addAction(Attack, NULL, NULL, 50);
		actionsManager.addAnimation(Attack, Direction::N, DataBase::animations[AnimationName::SlashN]);
		actionsManager.addAnimation(Attack, Direction::W, DataBase::animations[AnimationName::SlashW]);
		actionsManager.addAnimation(Attack, Direction::S, DataBase::animations[AnimationName::SlashS]);
		actionsManager.addAnimation(Attack, Direction::E, DataBase::animations[AnimationName::SlashE]);
		actionsManager.setActionActivationDistMax(Attack, 5);

		actionsManager.setStartingAction(Walk, Direction::S);
		actionsManager.addPattern(Walk);
		actionsManager.addPattern(Attack);
		actionsManager.addPattern(AttackProj);
//		addAnimation
		//		actionsManager.addAction(AttackProj, new MoveForwardPlayer(_map, _player), new ProjectileDirection(90, 4), 0, 2, 100, 50);

		setPositionShift(0.5, 0.8, 0.55);
	}

	~MonRandMoveProjAround() {}
};

class Boss1 : public Unit {
public:
	Boss1(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::UnitT]) {
		actionsManager.addAction(Walk, new MoveForwardPlayer(_map, _player), new ProjectileDirection(DataBase::animations[AnimationName::Projectile2], 90, 40), 1);
		actionsManager.addAnimation(Walk, Direction::N, DataBase::animations[AnimationName::PlayerWalkN]);
		actionsManager.addAnimation(Walk, Direction::E, DataBase::animations[AnimationName::PlayerWalkE]);
		actionsManager.addAnimation(Walk, Direction::S, DataBase::animations[AnimationName::PlayerWalkS]);
		actionsManager.addAnimation(Walk, Direction::W, DataBase::animations[AnimationName::PlayerWalkW]);

		actionsManager.addAction(Attack, NULL, new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 5), 1);
		actionsManager.addAnimation(Attack, Direction::N, DataBase::animations[AnimationName::SlashN]);
		actionsManager.addAnimation(Attack, Direction::W, DataBase::animations[AnimationName::SlashE]);
		actionsManager.addAnimation(Attack, Direction::S, DataBase::animations[AnimationName::SlashS]);
		actionsManager.addAnimation(Attack, Direction::E, DataBase::animations[AnimationName::SlashW]);

		actionsManager.addPattern(Walk);
		actionsManager.addPattern(Attack);

		actionsManager.setStartingAction(Walk, Direction::S);
		setPositionShift(0.5, 0.8, 0.55);
	}

	~Boss1() {}
};
