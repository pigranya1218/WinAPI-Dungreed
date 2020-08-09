#pragma once
#include "Enemy.h"
#include "BulletManager.h"

class BatRed : public Enemy
{
private:
	tagAttackInfo _shooting;

	BulletManager* _bm;

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update();
	void render();

	void setState(ENEMY_STATE state);
};

