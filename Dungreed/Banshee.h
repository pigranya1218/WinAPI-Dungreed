#pragma once
#include "Enemy.h"
#include "BulletManager.h"

class Banshee : public Enemy
{
private:
	BulletManager*	_bullet;	// 불렛
	tagAttackInfo	_shooting;	// 공격 관련

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update();
	void render();

	void setState(ENEMY_STATE state);
};

