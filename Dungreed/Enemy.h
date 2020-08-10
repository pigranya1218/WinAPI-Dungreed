#pragma once
#include "GameObject.h"

enum class ENEMY_STATE : unsigned int
{
	IDLE,
	MOVE,
	ATTACK,
	SKILL,
	DIE
};

class Enemy : public GameObject
{
protected:
	bool		_isDetect;				// �÷��̾� ���� ���� >> �����ϸ� ���� ����
	Image*		_img;
	ENEMY_STATE _state;
	Animation*	_ani;

	float _moveAngle;
	float _moveSpeed;
	
	float _scale;

	class EnemyManager* _em;

	struct tagAttackInfo	// ���� ���� ������
	{
		FloatRect rect;	// ���� ���� �� ��Ʈ
		float delay;	// ���� �ֱ�
		float count;	// ���� �ֱ� ����
		float angle;	// ź�� ���� ����

		bool update(float elapseTime)
		{
			count += elapseTime;

			if (count >= delay)
			{
				count -= delay;
				return true;
			}
			return false;
		}
	};

	Synthesize(float, _currentHp, currentHp);
	Synthesize(float, _maxHp, maxHp);

public:
	Enemy() {}
	~Enemy() {}

	virtual void init(const Vector2& pos, DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setState(ENEMY_STATE state) {}

	void setEnemyManager(class EnemyManager* em) { _em = em; }
};

