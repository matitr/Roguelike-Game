#include "Projectile.h"
#include "Game.h"
#include "Player.h"



bool Projectile::update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit) {
	if (destroyObj)
		return false;

	if (enemyHitted) {
		enemyHitted = false;

		if (staticPassives[StaticPassiveName::pierceShots] <= -1)
			return false;
	}

	if (staticPassives[StaticPassiveName::homing] && closestUnit)
		homingShot(closestUnit);

	position.x += velocity.x;
	position.y += velocity.y;

	animation.updateTexture();

	return true;
}

void Projectile::draw(SDL_Point* startRender) {
	dstRect.x = int(position.x - startRender->x - dstRect.w / 2.0);
	dstRect.y = int((position.y - startRender->y) * HEIGHT_SCALE - dstRect.h / 2 - heightFromGround);

	SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

void Projectile::setDirection(double dir) {
	direction = dir;
	angle = dir * 180.0 / 3.14159265;

	velocity.x = cos(direction) * speed;
	velocity.y = sin(direction) * speed;
}

void Projectile::setAngle(double ang) {
	direction = ang * 3.14159265 / 180.0;
	angle = ang;

	velocity.x = cos(direction) * speed;
	velocity.y = sin(direction) * speed;
}

void Projectile::homingShot(Unit* closestUnit) {
	double dist;
	if ((dist = distanceEdges(closestUnit)) > 70 * staticPassives[StaticPassiveName::homing]) // Homing radius
		return;

	if (std::find(unitsHitted.begin(), unitsHitted.end(), closestUnit) != unitsHitted.end()) // Already hitted
		return;

	double x = closestUnit->getPositionX() - position.x;
	double y = closestUnit->getPositionY() - position.y;
	double vectorMultiply = x * velocity.x + y * velocity.y;
	double distanceMultiply = sqrt(pow(x, 2) + pow(y, 2)) * sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	double cosValue = (vectorMultiply / distanceMultiply);

	// Have to check whatever cosValue is not out of range, because of very small miss calculations
	if (cosValue > 1)
		cosValue = 1.0;
	else if (cosValue < 1)
		cosValue = -1.0;

	double direction2 = acos(cosValue);
	double angle2 = direction2 * 180.0 / 3.14159265;
	double cross = velocity.x * y - velocity.y * x;
	double change = (angle2 * 0.01);

	if (dist < 150)
		change = (angle2 * 0.09) + 1;

	if (dist < 40)
		change = rand() % 22;

	if (cross < 0) {
		angle -= change;

		if (angle < -180)
			angle = 180 - (angle + 180);
	}
	else {
		angle += change;

		if (angle > 180)
			angle = -180 + (angle - 180);
	}

	velocity.x = cos(angle * 3.14159265 / 180.0) * speed;
	velocity.y = sin(angle * 3.14159265 / 180.0) * speed;
}

void Projectile::onWallHit() {
	destroyObj = true;
}

Projectile::Projectile(AnimationDetails& animationD, PassivesManager* passivesManager, double attackDamage) : AttackType(passivesManager, attackDamage), animation(animationD, srcRect) {
	speed = 5;
	heightFromGround = 20;

	if (passivesManager->getUnitStatistics()[StaticPassiveName::projectileSpeedMult])
		speed = speed * (1 + passivesManager->getUnitStatistics()[StaticPassiveName::projectileSpeedMult]);

	if (passivesManager->getUnitStatistics()[StaticPassiveName::projectileSizeMult]) {
		dstRect.w = int(dstRect.w + dstRect.w * (1 + passivesManager->getUnitStatistics()[StaticPassiveName::projectileSizeMult]));
		dstRect.h = int(dstRect.h + dstRect.h * (1 + passivesManager->getUnitStatistics()[StaticPassiveName::projectileSizeMult]));
		setRadius(dstRect.w / 2);
	}
}


Projectile::~Projectile() {

}
