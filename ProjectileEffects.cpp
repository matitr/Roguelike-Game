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


void ProjEffectRandAngleChange::update(Projectile* projectile) {
	int dist = int(projectile->getTravelDist() / distance);
	if (dist != lastChange) {
		double angleToChange = (rand() % int(angleMax * 1000)) / 1000.0;
		if (rand() % 2)
			angleToChange *= -1;	
		projectile->changeAngleBy(angleToChange);
		lastChange = dist;
	}
}

ProjEffectRandAngleChange::ProjEffectRandAngleChange(int dist, float angle) : distance(dist), angleMax(angle) {

}


void ProjEffectSinusPath::update(Projectile* projectile) {
	double projectileDist = fmod(projectile->getTravelDist(), dist);

	double angleSinus = (projectileDist / dist) * 2 * M_PI;
	double angleNew = cos(angleSinus) * maxAngle;

	projectile->changeAngleBy(angleNew - prevAngle);
	prevAngle = angleNew;
}

ProjEffectSinusPath::ProjEffectSinusPath(int distance, double maxAngle) : dist(distance), maxAngle(maxAngle) {

}


void ProjEffectRightAngle::update(Projectile* projectile) {
	double travelDist = projectile->getTravelDist();
	if (travelDist / distance == 1 && !lastChange) {
		if (turnRight)
			projectile->changeAngleBy(90);
		else
			projectile->changeAngleBy(-90);

		turnRight = !turnRight;
		lastChange = 1;
	}
	else if (int(travelDist / distance) != lastChange) {
		if (lastChange % 3 == 0) {
			turnRight = !turnRight;
			lastChange = int(travelDist / distance);
			return;
		}

		if (turnRight)
			projectile->changeAngleBy(90);
		else
			projectile->changeAngleBy(-90);

		lastChange = int(travelDist / distance);
	}
}

ProjEffectRightAngle::ProjEffectRightAngle(int dist, bool _turnRight) : distance(dist), turnRight(_turnRight) {

}


void ProjEffectSlowToFast::update(Projectile* projectile) {
	float currTravelDist = (float)projectile->getTravelDist();

	if (currTravelDist > distance) {
		projectile->addSpeedMult(endSpeedMult - currSpeedMult);
		currSpeedMult = endSpeedMult;
	}
	else {
		float speedMult = startSpeedMult + (abs(endSpeedMult) - abs(startSpeedMult)) * currTravelDist / distance;
		projectile->addSpeedMult(speedMult - currSpeedMult);
		currSpeedMult = speedMult;
	}
}

ProjEffectSlowToFast::ProjEffectSlowToFast(int _distance, float _startSpeedMult, float _endSpeedMult)
	: distance(_distance), startSpeedMult(_startSpeedMult), endSpeedMult(_endSpeedMult), currSpeedMult(0) {


}


void ProjEffectStop::update(Projectile* projectile) {
	if ((int)projectile->getTravelDist() / distance > lastStopCounter) {
		lastStopCounter = projectile->getTravelDist() / distance;
		if (currentDuration < 0)
			projectile->addSpeedMult(-999999);
		currentDuration = duration;
	}

	
	if (currentDuration >= 0) {
		if (currentDuration == 0)
			projectile->addSpeedMult(999999);

		currentDuration--;
	}
}

ProjEffectStop::ProjEffectStop(int dur, int dist) : duration(dur), distance(dist) {

}








