#pragma once


class Projectile;

// All effects
class ProjEffectChangingAngle;
class ProjEffectSinusPath;

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
	~ProjEffectChangingAngle();
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






