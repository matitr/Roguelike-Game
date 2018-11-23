#include "ProjectileEffects.h"
#include "Projectile.h"
#include <math.h>



ProjectileEffect::ProjectileEffect() {

}


ProjectileEffect::~ProjectileEffect() {

}


void ProjEffectChangingAngle::update(Projectile* projectile) {
	projectile->changeAngleBy(angleChange);
}

ProjEffectChangingAngle::ProjEffectChangingAngle(double angle) : angleChange(angle) {

}

ProjEffectChangingAngle::~ProjEffectChangingAngle() {

}


void ProjEffectSinusPath::update(Projectile* projectile) {
	double projectileDist = fmod(projectile->getTravelDist(), dist);

	if (projectileDist == 0.0) {
		int iu = 0;
		int iu4 = 0;
	}

	double angleSinus = (projectileDist / dist) * 2 * M_PI;
	double angleNew = cos(angleSinus) * maxAngle;

	projectile->changeAngleBy(angleNew - prevAngle);
	prevAngle = angleNew;
}

ProjEffectSinusPath::ProjEffectSinusPath(int distance, double maxAngle) : dist(distance), maxAngle(maxAngle) {

}





