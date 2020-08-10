#pragma once
#include "Enemy.h"
#include "BulletManager.h"

class Banshee : public Enemy
{
private:
	BulletManager*	_bullet;	// �ҷ�
	tagAttackInfo	_shooting;	// ���� ����

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update();
	void render();

	void setState(ENEMY_STATE state);
};

