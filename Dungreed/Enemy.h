#pragma once
#include "GameObject.h"

class EnemyManager;

enum class ENEMY_STATE
{
	IDLE,        // �⺻
	MOVE,        // �̵�
	ATTACK,        // ����
	SKILL,        // Ư��
	DIE            // ����
};

class Enemy : public GameObject
{
protected:
	EnemyManager*    _enemyManager;    // ���ʹ� �Ŵ���

	ENEMY_STATE        _state;        // ���� ����

	DIRECTION        _direction;        // �ൿ

	Image*            _img;            // �̹���
	Animation*        _ani;            // �ִϸ��̼�
	string            _imageName;        // �̹��� �̸�

	struct tagAttackInfo
	{
		float delay;    // ������
		float count;    // ī��Ʈ��
		float angle;    // ����
		float distance;    // �Ÿ�

		bool update(float const timeElapsed)
		{
			count += timeElapsed;

			if (count >= delay)
			{
				count = 0;
				return true;
			}
			return false;
		}
	};

	struct tagMoveInfo
	{
		float speed;
		float angle;
		float gravity;
		float jumpPower;

		float delay;
		float count;

		bool update(float const timeElapsed)
		{
			count += timeElapsed;

			if (count >= delay)
			{
				count = 0;
				return true;
			}
			return false;
		}
	};

	bool    _isDetect;        // �÷��̾ �����Ͽ��°�
	float    _scale;            // ��Ʈ�� ��¿� ����� ������
	float    _detectRange;    // �÷��̾� ���� �Ÿ�

public:
	void init() {}
	virtual void init(const Vector2& pos, DIRECTION direction) = 0;
	virtual void release() = 0;
	virtual void update(float const timeElapsed) = 0;
	virtual void render() = 0;

	virtual void setState(ENEMY_STATE state) = 0;

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
};