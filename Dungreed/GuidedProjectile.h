#pragma once
#include "Projectile.h"

struct tagShadow
{
	Vector2 pos;
	float	angleRadian;
	float	alpha;
	int		frameX;
	Image*  img;
};

class GuidedProjectile : public Projectile
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

	string		_collisionEffect;	// �ε����� ������ �� ����Ʈ
	Vector2		_drawSize;			// �ε����� ������ �� ����Ʈ ������

	bool		_useGravity;		// �߷� ��� ����
	Vector2		_gravity;			// �߷°�

	bool		_useRotate;			// ����ü�� ���� ���ΰ�

	Vector2		_enemyPos;			// ���� ��ġ��
	float		_length;			// ����Ʈ ���� ������ �̹��� ����
	float		_timeCount;			// ����ü ���� ������ ī��Ʈ
	bool		_afterimage;		// �ܻ� ȿ�� ��뿩��
	float		_mirageCount;
	int			_afterCount;
	float		_collisionCount;
	Vector2		_miragePos;
	tagShadow	_shodow;
	vector<tagShadow> _vShadow;
public:
	GuidedProjectile() {}
	GuidedProjectile(const GuidedProjectile& source);

	//				�ҷ��̹��� Ű �̸�,	����Ʈ �̸�,	���� ������,	�浹 ������,	����Ʈ ������, ����ü ���ư� ��, ����ü ���ӽð�, ����, ������ ��뿩��, ������ ��������, �����Ӽӵ�, �ҷ� ȸ������,	�߷� ���뿩��, ���� �� �浹����, Ǫ�� �� �浹����, ���ʹ� ���� ����
	void init(const string imgKey, const string collisionEffect, const Vector2& drawSize, const Vector2& collsionRectSize, const Vector2& effectSize, const Vector2& force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate = 1, bool useGravity = 0, bool collsionGround = 1, bool collsionPlatForm = 1, bool collsionEnemy = 1, bool afterimage = false);

	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();

	// �ִϸ��̼� ������Ʈ �Ϸ��� ���� 
	virtual void aniUpdate(float const elapsedTime);
};