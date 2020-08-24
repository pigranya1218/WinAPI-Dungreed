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
	bool        _isTrun;
	bool        _bulletMove;
	Vector2     _playerPos;
	int         _y;
	int y;
	float       chaseRadian;
	bool        isLeft;
	float       _Delay;
	float       _angele;
	string		_collisionEffect;	// �ε����� ������ �� ����Ʈ
	Vector2		_drawSize;			// �ε����� ������ �� ����Ʈ ������

	bool		_useGravity;		// �߷� ��� ����
	Vector2		_gravity;			// �߷°�
	Vector2     _effectpos;
	bool		_useRotate;			// ����ü�� ���� ���ΰ�

	Vector2		_enemyPos;			// ���� ��ġ��
	float		_length;			// ����Ʈ ���� ������ �̹��� ����
	float		_timeCount;


public:
	//				�ҷ��̹��� Ű �̸�,	����Ʈ �̸�,	���� ������,	�浹 ������,	����Ʈ ������, ����ü ���ư� ��, ����ü ���ӽð�, ����, ������ ��뿩��, ������ ��������, �����Ӽӵ�, �ҷ� ȸ������,	�߷� ���뿩��, ���� �� �浹����, Ǫ�� �� �浹����, ���ʹ� ���� ����
	void init(const string imgKey, const string collisionEffect, const Vector2 & drawSize, const Vector2 & collsionRectSize, const Vector2 & effectSize, const Vector2 & force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate, bool useGravity, bool collsionGround, bool collsionPlatForm, bool collsionEnemy);

	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();
	// �ִϸ��̼� ������Ʈ �Ϸ��� ���� 
	virtual void aniUpdate(float const elapsedTime);
};

