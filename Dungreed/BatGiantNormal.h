#pragma once
#include "Enemy.h"

class BatGiantNormal : public Enemy
{
private:
	tagShootingInfo _shooting;	// ź�� ����
	tagAttackInfo	_attack;	// ���� ����

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};
