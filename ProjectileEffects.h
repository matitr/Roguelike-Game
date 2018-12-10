#pragma once


class Projectile;

// All effects
class ProjEffectChangingAngle;
class ProjEffectRandAngleChange;
class ProjEffectSinusPath;
class ProjEffectRightAngle;
class ProjEffectSlowToFast;
class ProjEffectStop;

class ProjectileEffect {

public:
	virtual void update(Projectile* projectile) = 0;
	virtual ProjectileEffect* getCopy() = 0;

	ProjectileEffect();
	virtual ~ProjectileEffect();
};


class ProjEffectChangingAngle : public ProjectileEffect {
	double angleChange;
public:
	void update(Projectile* projectile) override;
	ProjectileEffect* getCopy() override { return new ProjEffectChangingAngle(*this); }

	ProjEffectChangingAngle(double angle);
	~ProjEffectChangingAngle() = default;
};


class ProjEffectRandAngleChange : public ProjectileEffect {
	int distance;
	float angleMax;
	int lastChange = 0;
public:
	void update(Projectile* projectile) override;
	ProjectileEffect* getCopy() override { return new ProjEffectRandAngleChange(*this); }

	ProjEffectRandAngleChange(int distance, float angleMax);
	~ProjEffectRandAngleChange() = default;
};


class ProjEffectSinusPath : public ProjectileEffect {
	int dist;
	double maxAngle;
	double prevAngle = 0;
public:
	void update(Projectile* projectile) override;
	ProjectileEffect* getCopy() override { return new ProjEffectSinusPath(*this); }

	ProjEffectSinusPath(int distance, double maxAngle);
	~ProjEffectSinusPath() = default;
};


class ProjEffectRightAngle : public ProjectileEffect { // |_|-|_
	int distance;
	int lastChange = 0;
	bool turnRight;

public:
	void update(Projectile* projectile) override;
	ProjectileEffect* getCopy() override { return new ProjEffectRightAngle(*this); }

	ProjEffectRightAngle(int distance, bool turnRight = true);
	~ProjEffectRightAngle() = default;
};


class ProjEffectSlowToFast : public ProjectileEffect {
	int distance;
	float startSpeedMult;
	float endSpeedMult;

	float currSpeedMult;

public:
	void update(Projectile* projectile) override;
	ProjectileEffect* getCopy() override { return new ProjEffectSlowToFast(*this); }

	ProjEffectSlowToFast(int distance, float startSpeedMult, float endSpeedMult);
	~ProjEffectSlowToFast() = default;
};


class ProjEffectStop : public ProjectileEffect {
	int duration;
	int distance;
	int lastStopCounter = 0;
	int currentDuration = -1;

public:
	void update(Projectile* projectile) override;
	ProjectileEffect* getCopy() override { return new ProjEffectStop(*this); }

	ProjEffectStop(int duration, int distance);
	~ProjEffectStop() = default;
};



