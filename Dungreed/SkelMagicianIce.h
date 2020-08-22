#pragma once
#include "Enemy.h"

class SkelMagicianIce : public Enemy
{
private:
	tagShootingInfo _shooting;	// ź��
	tagAttackInfo	_attack;	// ����

	Image*			_attackImg;	// ���� ����Ʈ �̹���
	Animation*		_attackAni;	// ���� ����Ʈ ������
	Vector2			_attackPos;	// ���� ����Ʈ ��ǥ �����

	bool			_attacking;	// ���� ���� ����Ʈ ���� ��
	int				_PlayCount;

	int _enterCount;
public:
	void init(const Vector2& pos, DIRECTION direction, bool spawnEffect);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};

