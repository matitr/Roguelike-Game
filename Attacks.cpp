#include "Attacks.h"
#include "Unit.h"



Attack::Attack() {

}


Attack::~Attack() {

}

void ProjectileDirection::makeAttack(Unit* unit, std::list <Projectile*>& monsterAttacks) {
	angle = startAngle;
	for (int i = 0; i < numbOfProj; i++) {
		Projectile* p = new Projectile(TextureManager::textures[PROJECTILES], 25, 25, 0, 3, 10);
		angle = startAngle + (360 / numbOfProj) * i;
		if (angle >= 360)
			angle -= 360;

		if (angle > 180)
			p->setAngle(angle - 180);
		else
			p->setAngle(-1 * angle);

		p->setPosition(unit->getPositionX(), unit->getPositionY());
		monsterAttacks.push_back(p);
	}
}