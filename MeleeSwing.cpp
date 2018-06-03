#include "MeleeSwing.h"
#include "Unit.h"
#include "DataBase.h"


bool MeleeSwing::update(Map* map, SDL_Rect& fieldRect, Unit* closestUnit) {
	if (frameCounter == frames * frameCounter)
		return false;

	frameCounter++;

	return true;
}

bool MeleeSwing::collision(Unit* u) {
	if (!detectCollision(u))
		return false;

	double dir = atan2((u->getPositionY() - position.y), (u->getPositionX() - position.x));
	int angle = int(dir * 180.0 / 3.14159265 + 360) % 360 + 360;
	int tempAngle = attackAngle + 360;

	if (angle >= tempAngle - attackWidthAngle && angle <= tempAngle + attackWidthAngle) {
		std::cout << angle << std::endl;
		return true;
	}
	if (angle >= tempAngle - attackWidthAngle + 360 && angle <= tempAngle + attackWidthAngle + 360) {
		std::cout << angle << std::endl;
		return true;
	}

	return false;
}

void MeleeSwing::setAngles(int _attackAngle, int _attackWidthAngle) {
	attackAngle = _attackAngle;
	attackWidthAngle = _attackWidthAngle;
}

MeleeSwing::MeleeSwing(AnimationDetails& animation, ItemPassives& passives) 
	: AttackType(passives), frames(animation.frames - 2), frameTime(animation.frameTime) {

}


MeleeSwing::~MeleeSwing() {

}
