#pragma once
#include "Enemy.h"

class SkelMagicianIce : public Enemy
{
private:
	tagAttackInfo	_attack;	// ����

	Image*			_attackImg;	// ���� ����Ʈ �̹���
	Animation*		_attackAni;	// ���� ����Ʈ ������
	Vector2			_attackPos;	// ���� ����Ʈ ��ǥ �����

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

