#include "Attacks.h"
#include "Unit.h"
#include "DataBase.h"



Attack::Attack() {

}


Attack::~Attack() {

}

void ProjectileDirection::makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks) {
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
		monsterAttacks.push_back(p);
		if (i > 25)
			i = i;
	}
}