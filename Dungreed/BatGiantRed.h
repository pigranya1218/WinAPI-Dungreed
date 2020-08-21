#pragma once
#include "Enemy.h"

class BatGiantRed : public Enemy
{
private:
	tagShootingInfo _shooting;	// ź�� ����
	tagAttackInfo	_attack;	// ���� ����

	int				_renderNum;	// �Ѿ� ������
	int				_countPlay;


public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};

