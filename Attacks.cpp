#include "Attacks.h"
#include "Unit.h"
#include "DataBase.h"



AttackPattern::AttackPattern() {

}


AttackPattern::~AttackPattern() {

}

void ProjectileDirection::makeAttack(Unit* unit, std::list <Projectile*>& attacksContainer, SDL_Point* attackPoint) {
	angle = startAngle;
	for (int i = 0; i < numbOfProj; i++) {
		Projectile* p = new Projectile(DataBase::animations[AnimationName::Projectile], unit->getPassives());
		angle = startAngle + (360.0 / (numbOfProj )) * i;
		if (angle >= 360)
			angle -= 360;

		if (angle > 180)
			p->setAngle(180 - (angle - 180));
		else
			p->setAngle(-1 * angle);

		p->setPosition(unit->getPositionX(), unit->getPositionY());
		attacksContainer.push_back(p);
		if (i > 25)
			i = i;
	}
}

void MultipleProjectiles::makeAttack(Unit* unit, std::list <Projectile*>& attacksContainer, SDL_Point* posToShot) {
	
	float dir = atan2((posToShot->y - unit->getPositionY()), (posToShot->x - unit->getPositionX()));
	int startingAngle = dir * 180.0 / 3.14159265;
	double cross = unit->getPositionX() * posToShot->y - unit->getPositionY() * posToShot->x;

	double angleBetween = 5;
	double change = angleBetween * (numbOfProjectiles - 1) / 2;
	double angle =  startingAngle;

	angle -= change;

	if (angle < -180)
		angle = 180 + (angle + 180);

	for (int i = 0; i < numbOfProjectiles; i++) {
		Projectile* p = new Projectile(DataBase::animations[AnimationName::Projectile], unit->getPassives());
		p->setAngle(angle);
		p->setPosition(unit->getPositionX(), unit->getPositionY());
		attacksContainer.push_back(p);

		angle += angleBetween;

		if (angle > 180)
			angle = -180 + (angle - 180);
	}












}

















