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
		action->addAnimations(DataBase::unitAnimations[UnitName::Unit][AttackProj], srcRect);

		ActionUtilities* actionUtilities = new ActionUtilities(new NoMoveFaceEnemy(this, _player), new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 1), 8);
		actionUtilities->addAnimations(DataBase::unitAnimations[UnitName::Unit][AttackProj], srcRect);
		action->addActionUtilities(actionUtilities);

		actionUtilities = new ActionUtilities(new NoMoveFaceEnemy(this, _player), new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 1), 7);
		actionUtilities->addAnimations(DataBase::unitAnimations[UnitName::Unit][AttackProj], srcRect);
		action->addActionUtilities(actionUtilities);

		actionUtilities = new ActionUtilities(new NoMoveFaceEnemy(this, _player), new MultipleProjectiles(DataBase::animations[AnimationName::Projectile2], 1), 6);
		actionUtilities->addAnimations(DataBase::unitAnimations[UnitName::Unit][AttackProj], srcRect);
		action->addActionUtilities(actionUtilities);

		action->setDistActivationMax(300);
		action->setDistActivationMin(150);
		action->setCooldown(240);
		action->setClearPathRequired();
		actionsManager.addAction(AttackProj, action);

		actionsManager.addAction(Attack, NULL, new MeleeSwingAttack(DataBase::unitAnimations[UnitName::Unit][Attack][Direction::E], 60, 45), 2);
		actionsManager.addAnimations(Attack, DataBase::unitAnimations[UnitName::Unit][Attack]);
		actionsManager.setActionActivationDistMax(Attack, 5);

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

		actionsManager.addAction(Walk, NULL, NULL, 1);
		actionsManager.addAnimations(Walk, DataBase::unitAnimations[UnitName::Unit][Walk]);

		AttackPattern* attackP = new ProjectilesAround(DataBase::animations[AnimationName::Projectile2], 270, 30);
//		attackP->addProjectileEffect(new ProjEffectChangingAngle(0.5));
//		attackP->addProjectileEffect(new ProjEffectSinusPath(300, 45));
//		attackP->addProjectileEffect(new ProjEffectStop(30, 50));
//		attackP->addProjectileEffect(new ProjEffectRightAngle(100, true));
//		attackP->addProjectileEffect(new ProjEffectSlowToFast(250, -0.5, 2));
		attackP->addProjectileEffect(new ProjEffectRandAngleChange(40, 30));
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
