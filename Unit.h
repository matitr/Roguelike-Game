#pragma once
#include "Animation.h"
#include <unordered_map>
#include "Map.h"
#include "Attacks.h"
#include "GameObject.h"
#include "Item.h"


class Projectile;
class UnitAction;
class AttackPattern;
class Movement;

enum ActionType {Stand, Walk, Roll, AttackProj};

class Unit : public GameObject {
protected:
	std::unordered_map <ActionType, UnitAction*> actions;

	std::list<ActionType> pattern;
	std::list<ActionType>::iterator currAction;


	SDL_RendererFlip flip;

	float speed;
	float hp;
	float maxHp;

	ItemPassives staticPassives;
	void setStartingAction(ActionType action, Direction::Name dir);
public:
	PointFloat velocity;
	virtual void updateActionFrame();
	virtual bool update(std::list <Projectile*>& monsterAttacks, Map* map);
	virtual void draw(SDL_Point* startRender);

	void addAction(ActionType action, Movement* move, AttackPattern* attack, int attackFrame = -1);
	void addAnimation(ActionType action, Direction::Name dir, AnimationDetails& animationD);
	void addPattern(ActionType actionType);

	void setHp(int _hp) { hp = float(hp); }
	void takeDamage(float damage) { hp -= damage; }
	ItemPassives& getPassives() { return staticPassives; }

	Unit(TextureInfo& txtInfo);
	~Unit();
	void renderCircle(int _x, int _y, int radius);
};

