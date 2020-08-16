#pragma once
#include "GameObject.h"
#include "AttackInfo.h"
#include "Shooting.h"
#include "NormalProjectile.h"

class EnemyManager;

enum class ENEMY_STATE
{
	IDLE,		// �⺻
	MOVE,		// �̵�
	ATTACK,		// ����
	SKILL,		// Ư��
	DIE			// ����
};

// ź�� ���� ��


class Enemy : public GameObject
{
protected:
	EnemyManager*		_enemyManager;	// ���ʹ� �Ŵ���
	ENEMY_STATE			_state;			// ���� ����
	DIRECTION			_direction;		// �ൿ
	Image*				_img;			// �̹���
	Animation*			_ani;			// �ִϸ��̼�
	string				_imageName;		// �̹��� �̸�
	bool				_isDetect;		// �÷��̾ �����Ͽ��°�
	float				_scale;			// ��Ʈ�� ��¿� ����� ������
	float				_detectRange;	// �÷��̾� ���� �Ÿ�	

	//Synthesize(float, _curHp, Hp);
	//Synthesize(float, _maxHp, Hp);

	// ź�� ��� ��
	struct tagShootingInfo
	{
		vector<NormalProjectile*> bullets;	// �� ���� ������ ����� ���� ��� ����

		string				bulletName;	// �ҷ� �̹��� �̸�
		string				effectName;	// �ҷ� ����Ʈ �̸�
		Vector2				effectSize;	// �ҷ� ����Ʈ ������

		float				delay;		// ������
		float				count;		// ī��Ʈ
		float				angle;		// ����
		float				range;		// �����Ÿ�
		float				speed;		// ���ǵ�

		bool				isAni;		// �ִϸ��̼� ��뿩��
		bool				aniLoop;	// �ִϸ��̼� ��������
		bool				isCollision;// �浹 ����
		bool				isRotate;	// �̹��� ȸ�� ����
		int					bulletNum;	// ������ �Ѿ� ����

		void init(string bulletName, string effectName, float scale, float delay, float range, float speed, bool isRotate, bool isCollision, bool isAni, bool aniLoop)
		{
			this->bulletName = bulletName;
			this->effectName = effectName;	

			if (isAni)
			{
				this->effectSize = IMAGE_MANAGER->findImage(bulletName)->getFrameSize() * scale;
			}
			else
			{
				Vector2 size = IMAGE_MANAGER->findImage(bulletName)->getSize();
				this->effectSize = Vector2(size.x * scale, size.y * scale);
			}

			this->delay = delay;
			this->range = range;
			this->speed = speed;

			this->isAni = isAni;
			this->aniLoop = aniLoop;
			this->isCollision = isCollision;
			this->isRotate = isRotate;
		}
		// ������ ������Ʈ
		bool delayUpdate(float const timeElapsed)
		{
			count += timeElapsed;

			if (count >= delay)
			{
				count = 0;
				return true;
			}
			return false;
		}
		// �Ѿ� ����
		void createBullet(const Vector2& pos, float angle)
		{
			this->angle = angle;

			NormalProjectile* bullet = new NormalProjectile;

			bullet->setPosition(pos);
			bullet->setSize(effectSize);
			bullet->setTeam(OBJECT_TEAM::ENEMY);

			bullet->init(bulletName, angle, speed, isAni, aniLoop, 15, isCollision, effectName, effectSize, range, isRotate);

			if (bulletNum > 0) --bulletNum;
			bullets.push_back(bullet);
		}
		void aniUpdate(const float timeElapsed)
		{
			for (int i = 0; i < bullets.size(); i++)
			{
				bullets[i]->aniUpdate(timeElapsed);
			}
		}
		// �Ѿ� ���
		void render(int maxNum = -1)
		{
			int loopSize = (maxNum == -1) ? (bullets.size()) : (maxNum);

			for (int i = 0; i < loopSize; i++)
			{
				bullets[i]->render();
			}
		}

		void fireBullet(EnemyManager* enemyManager, int fireCount = 0);
	};

	// ���ݿ� ���õ� �͵�
	struct tagAttackInfo
	{
		float delay;	// ������
		float count;	// ī��Ʈ��
		float angle;	// ����
		float distance;	// �Ÿ�

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

	// �̵� ���� ����
	struct tagMoveInfo
	{
		Vector2 force;
		Vector2 gravity;

		float angle;
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

public:
	virtual void init(const Vector2& pos, DIRECTION direction) = 0;
	virtual void release() = 0;
	virtual void update(float const timeElapsed) = 0;
	virtual void render() = 0;

	virtual void setState(ENEMY_STATE state) = 0;

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }

	void setDetectRange(float const range) { _detectRange = range; }
};

