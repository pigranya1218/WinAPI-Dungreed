#pragma once
#include "Enemy.h"

class Banshee : public Enemy
{
private:	
	AttackInfo	_shooting;	// ���� ����

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

