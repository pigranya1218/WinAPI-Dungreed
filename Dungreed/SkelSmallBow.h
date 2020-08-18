#pragma once
#include "Enemy.h"

class SkelSmallBow : public Enemy
{
private:
	tagAttackInfo	_attack;		// ����
	tagShootingInfo _shooting;		// ȭ��
	Animation*		_weaponAni;		// ���� �ִϸ��̼�
	Image*			_weaponImg;		// ���� �̹���

	Image*			_handImg;		// �� �̹���

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};

