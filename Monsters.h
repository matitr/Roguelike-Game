#pragma once
#include "Unit.h"
#include "TextureManager.h"
#include "Attacks.h"
#include "Movements.h"
#include "DataBase.h"
#include "UnitAction.h"
#include "ProjectileEffects.h"

class UnitAction;

#pragma region StandardUnits
class UnitEnemy1 : public Unit {

public:
	UnitEnemy1(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::UnitT], UnitType::Monster) {
//		passivesManager->setStartingStat(StaticPassiveName::attackSpeedMult, 3);

		actionsManager.addAction(Walk, new MoveForwardPlayer(this, _map, _player), NULL, 1);
		actionsManager.addAnimations(Walk, DataBase::unitAnimations[UnitName::Unit][Walk]);

		UnitAction* action = new UnitAction(new NoMoveFaceEnemy(this, _player), new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 1), 9);
//		UnitAction* action = new UnitAction(NULL, NULL, 9);
		action->addAnimations(DataBase::unitAnimations[UnitName::Unit][AttackProj], srcRect);
		action->setDistActivationMax(100);
		action->setDistActivationMin(550);
		action->setCooldown(0);
		action->setClearPathRequired();
		actionsManager.addAction(AttackProj, action);

		actionsManager.addAction(Attack, NULL, new MeleeSwingAttack(DataBase::unitAnimations[UnitName::Unit][Attack][Direction::E], 60, 45), 2);
		actionsManager.addAnimations(Attack, DataBase::unitAnimations[UnitName::Unit][Attack]);
		actionsManager.setActionActivationDistMax(Attack, -222);

		actionsManager.setStartingAction(Walk, Direction::S);
		actionsManager.addPattern(Walk);
		actionsManager.addPattern(Attack);
		actionsManager.addPattern(AttackProj);
		actionsManager.addAction(Death, NULL, new ProjectilesAround(DataBase::animations[AnimationName::Projectile2], 60, 45), 2);

		setPositionShift(0.5f, 0.8f, 0.55f);
	}

	~UnitEnemy1() {}
};


class UnitEnemy2 : public Unit {

public:
	UnitEnemy2(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::UnitT], UnitType::Monster) {
//		staticPassives[StaticPassiveName::projectileSpeedMult] = -0.3f;

		actionsManager.addAction(Walk, new MoveForwardPlayer(this, _map, _player), NULL, 1);
		actionsManager.addAnimations(Walk, DataBase::unitAnimations[UnitName::Unit][Walk]);

		AttackPattern* attackP = new ProjectilesAround(DataBase::animations[AnimationName::Projectile2], 90, 1);
//		attackP->addProjectileEffect(new ProjEffectChangingAngle(0.5));
		attackP->addProjectileEffect(new ProjEffectSinusPath(300, 45));
		actionsManager.addAction(AttackProj, NULL, attackP, 9);
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
	Boss1(Map* _map, Unit* _player) : Unit(TextureManager::textureParameters[SingleTexture::UnitT], UnitType::Boss) {
		actionsManager.addAction(Walk, new MoveForwardPlayer(this, _map, _player), new ProjectilesAround(DataBase::animations[AnimationName::Projectile2], 90, 40), 1);
		actionsManager.addAnimations(Walk, DataBase::unitAnimations[UnitName::Unit][Walk]);

		actionsManager.addAction(Attack, new NoMoveFaceEnemy(this, _player), new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 5), 1);
		actionsManager.addAnimations(Attack, DataBase::unitAnimations[UnitName::Unit][AttackProj]);
		actionsManager.setActionActivationDistMax(Attack, 1000);

		actionsManager.setStartingAction(Walk, Direction::S);
		actionsManager.addPattern(Walk);
		actionsManager.addPattern(Attack);

		actionsManager.setStartingAction(Walk, Direction::S);
		setPositionShift(0.5f, 0.8f, 0.55f);
	}

	~Boss1() {}
};
