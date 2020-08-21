#pragma once
#include "Projectile.h"
class SeeriProjectile : public Projectile
{
private:

	float		_maxTime;			// ����ü ���ӽð�
	float		_count;				// �ð� ����

	Image*		_img;				// ����ü �̹���
	Image*		_effectImg;			// ����Ʈ �̹���
	Vector2		_effectSize;        // ����Ʈ ������

	bool		_useAni;			// �ִϸ��̼� ����ϴ°�
	Animation*	_ani;				// ����ü �ִϸ��̼�

	bool		_collsionGround;	// ���� �� �浹 ����
	bool		_collisionPlatForm;	// Ǫ�� �� �浹 ����

	bool        _bulletMove;
	Vector2     _playerPos;
	int         _y;
	int y;
	float chaseRadian;
	bool isLeft;
	float       _Delay;
	string		_collisionEffect;	// �ε����� ������ �� ����Ʈ
	Vector2		_drawSize;			// �ε����� ������ �� ����Ʈ ������

	bool		_useGravity;		// �߷� ��� ����
	Vector2		_gravity;			// �߷°�

	bool		_useRotate;			// ����ü�� ���� ���ΰ�

	Vector2		_enemyPos;			// ���� ��ġ��
	float		_length;			// ����Ʈ ���� ������ �̹��� ����
	float		_timeCount;

public:
	//				�ҷ��̹��� Ű �̸�,	����Ʈ �̸�,	���� ������,	�浹 ������,	����Ʈ ������, ����ü ���ư� ��, ����ü ���ӽð�, ����, ������ ��뿩��, ������ ��������, �����Ӽӵ�, �ҷ� ȸ������,	�߷� ���뿩��, ���� �� �浹����, Ǫ�� �� �浹����, ���ʹ� ���� ����
	void init(const string imgKey,  const string collisionEffect, const Vector2 _player, const Vector2& drawSize, const Vector2& collsionRectSize, const Vector2& effectSize, const Vector2& force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate = 1, bool useGravity = 0, bool collsionGround = 1, bool collsionPlatForm = 1, bool collsionEnemy = 1);

	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();

	// �ִϸ��̼� ������Ʈ �Ϸ��� ���� 
	virtual void aniUpdate(float const elapsedTime);
};

