#include "Attacks.h"
#include "Unit.h"
#include "DataBase.h"
#include "Projectile.h"
#include "MeleeSwing.h"



AttackPattern::AttackPattern() {

}


AttackPattern::~AttackPattern() {

}

void ProjectileDirection::makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, SDL_Point* attackPoint) {
	angle = startAngle;
	for (int i = 0; i < numbOfProj; i++) {
		Projectile* p = new Projectile(animationD, unit->getPassives());
		angle = startAngle + ((float)360.0 / (numbOfProj )) * i;
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

void MultipleProjectiles::makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, SDL_Point* posToShot) {
	
	double dir = atan2((posToShot->y - (int)unit->getPositionY()), (posToShot->x - (int)unit->getPositionX()));
	int startingAngle = int(dir * 180.0 / 3.14159265);
	double cross = unit->getPositionX() * posToShot->y - unit->getPositionY() * posToShot->x;

	double angleBetween = 5;
	double change = angleBetween * (numbOfProjectiles - 1) / 2;
	double angle =  startingAngle;

	angle -= change;

	if (angle < -180)
		angle = 180 + (angle + 180);

	for (int i = 0; i < numbOfProjectiles; i++) {
		Projectile* p = new Projectile(animationD, unit->getPassives());
		p->setAngle(angle);
		p->setPosition(unit->getPositionX(), unit->getPositionY());
		attacksContainer.push_back(p);

		angle += angleBetween;

		if (angle > 180)
			angle = -180 + (angle - 180);
	}
}

void MeleeSwingAttack::makeAttack(Unit* unit, std::list <AttackType*>& attacksContainer, SDL_Point* attackPoint) {
	MeleeSwing* attack = new MeleeSwing(animationD, unit->getPassives());

	SDL_Point attackPos = { attackPoint->x - (int)unit->getPositionX(), attackPoint->y - (int)unit->getPositionY() };
	if (abs(attackPos.x) < abs(attackPos.y))
		attackPos.x = 0;
	else
		attackPos.y = 0;

	double dir = atan2(attackPos.y, attackPos.x);
	int angle = int(dir * 180.0 / 3.14159265 + 360) % 360;

	attack->setAngles(angle, attackWidthAngle);
	attack->setPosition(unit->getPositionX(), unit->getPositionY());
	attack->setRadius(radius);

	attacksContainer.push_back(attack);
}















