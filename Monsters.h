#pragma once
#include "Unit.h"
#include "TextureManager.h"
#include "Attacks.h"
#include "Movements.h"
#include "DataBase.h"

class UnitAction;

#pragma region StandardUnits
class UnitEnemy1 : public Unit {

public:
	UnitEnemy1(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::UnitT]) {
		staticPassives[StaticPassiveName::projectileSpeed] = 0.5;

		actionsManager.addAction(Walk, new MoveForwardPlayer(this, _map, _player), NULL, 1);
		actionsManager.addAnimations(Walk, DataBase::unitAnimations[UnitName::Unit][Walk]);

		actionsManager.addAction(AttackProj, new NoMoveFaceEnemy(this, _player), new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 1), 9);
		actionsManager.addAnimations(AttackProj, DataBase::unitAnimations[UnitName::Unit][AttackProj]);
		actionsManager.setActionActivationDistMax(AttackProj, 500);
		actionsManager.setActionActivationDistMin(AttackProj, 50);

		actionsManager.addAction(Attack, NULL, new MeleeSwingAttack(DataBase::animations[AnimationName::SlashN], 60, 45), 2);
		actionsManager.addAnimations(Attack, DataBase::unitAnimations[UnitName::Unit][Attack]);
		actionsManager.setActionActivationDistMax(Attack, 10);

		actionsManager.setStartingAction(Walk, Direction::S);
		actionsManager.addPattern(Walk);
		actionsManager.addPattern(Attack);
		actionsManager.addPattern(AttackProj);

		setPositionShift(0.5f, 0.8f, 0.55f);
	}

	~UnitEnemy1() {}
};


class UnitEnemy2 : public Unit {

public:
	UnitEnemy2(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::UnitT]) {
		staticPassives[StaticPassiveName::projectileSpeed] = -0.3;

		actionsManager.addAction(Walk, new MoveForwardPlayer(this, _map, _player), NULL, 1);
		actionsManager.addAnimations(Walk, DataBase::unitAnimations[UnitName::Unit][Walk]);

		actionsManager.addAction(AttackProj, new NoMoveFaceEnemy(this, _player), new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 3), 9);
		actionsManager.addAnimations(AttackProj, DataBase::unitAnimations[UnitName::Unit][AttackProj]);
		actionsManager.setActionActivationDistMax(AttackProj, 1000);

		actionsManager.setStartingAction(Walk, Direction::S);
		actionsManager.addPattern(Walk);
		actionsManager.addPattern(AttackProj);

		setPositionShift(0.5f, 0.8f, 0.55f);
	}

	~UnitEnemy2() {}
};
#pragma endregion


class Boss1 : public Unit {
public:
	Boss1(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::UnitT]) {
		actionsManager.addAction(Walk, new MoveForwardPlayer(this, _map, _player), new ProjectileDirection(DataBase::animations[AnimationName::Projectile2], 90, 40), 1);
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
		setPositionShift(0.5f, 0.8f, 0.55f);
	}

	~Boss1() {}
};
