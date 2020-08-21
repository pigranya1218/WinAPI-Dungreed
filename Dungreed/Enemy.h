#pragma once
#include "GameObject.h"
#include "AttackInfo.h"
#include "Shooting.h"
#include "NormalProjectile.h"


#define MAXHP 150
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
	EnemyManager*	_enemyManager;	// ���ʹ� �Ŵ���
	ENEMY_STATE		_state;			// ���� ����
	DIRECTION		_direction;		// �ൿ
	Image*			_img;			// �̹���
	Sound*			_sound;			// ����
	Animation*		_ani;			// �ִϸ��̼�
	string			_imageName;		// �̹��� �̸�
	string			_soundName;		// ���� �̸�	

	bool			_isDetect;		// �÷��̾ �����Ͽ��°�
	float			_scale;			// ��Ʈ�� ��¿� ����� ������
	float			_detectRange;	// �÷��̾� ���� �Ÿ�	

	float			_curHp;
	float			_maxHp;

	int				_myEnemyType;	// ���ʹ� Ÿ�� ����

	vector<size_t>		_attackedId; // �ֱ� ���ݹ޾Ҵ� ���ݵ��� ���̵� ������ �����ϴ� ����, �ִ� 10ĭ ���� �����ϸ� ������ ��

	// ź�� ���� ��� ��
	struct tagShootingInfo
	{
		vector<NormalProjectile*> bullets;	// �� ���� ������ ����� ���� ��� ����

		AttackInfo info;			// ���� ���� �����

		string	bulletName;			// �ҷ� �̹��� �̸�
		string	effectName;			// �ҷ� ����Ʈ �̸�

		Vector2	effectSize;			// �ҷ� ����Ʈ ������
		Vector2 drawSize;			// �׸� ������
		Vector2 collisionSize;		// �浹 ������
		Vector2	force;				// �ҷ� ���ư��� ��

		float	delay;				// ������
		float	count;				// ī��Ʈ
		float	angle;				// ����
		float	duration;			// ���ӽð�

		bool	collisionGround;	// ���� �� �浹����
		bool	collisionPlatForm;	// Ǫ�� �� �浹����
		bool	isAni;				// �ִϸ��̼� ��뿩��
		bool	aniLoop;			// �ִϸ��̼� ��������
		bool	isRotate;			// �̹��� ȸ�� ����
		bool	isGravity;			// �߷� ��� ����

		int		bulletNum;			// ������ �Ѿ� ����

		// �Ѿ� �ʱ�ȭ >> �ҷ� �̹����̸�, ����Ʈ �̸�, ����ü ���ư��� ��, ������, ����ü �߻��ֱ�, ����ü ���ӽð�, �̹��� ȸ������, ������ ��뿩��, ������ ��������, �߷� ���뿩��, ���� �� �浹����, Ǫ�� �� �浹����
		void init(string bulletName, string effectName, Vector2 force, float scale, float delay, float duration, bool isRotate = 0, bool isAni = 1, bool aniLoop = 1, bool isGravity = 0, bool collisionGround = 1, bool collisionPlatForm = 1)
		{
			this->bulletName = bulletName;
			this->effectName = effectName;	

			if (isAni)
			{
				collisionSize = drawSize = IMAGE_MANAGER->findImage(bulletName)->getFrameSize() * scale;
			}
			else
			{
				Vector2 size = IMAGE_MANAGER->findImage(bulletName)->getSize();
				collisionSize = drawSize = Vector2(size.x * scale, size.y * scale);
			}

			this->delay = delay;
			this->duration = duration;
			this->force = force;

			this->isAni = isAni;
			this->aniLoop = aniLoop;			
			this->isRotate = isRotate;
			this->isGravity = isGravity;
			this->collisionGround = collisionGround;
			this->collisionPlatForm = collisionPlatForm;
		}		
		void attackInit(const float minDamage, const float maxDamage, const float trueDamage, const float knockBack = 15)
		{
			info.minDamage = minDamage;
			info.maxDamage = maxDamage;
			info.trueDamage = trueDamage;
			info.knockBack = knockBack;
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
			//bullet->setSize(effectSize);
			
			bullet->init(bulletName, effectName, drawSize, collisionSize, drawSize, force, duration, angle, isAni, aniLoop, 15, isRotate, isGravity, collisionGround, collisionPlatForm);

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

		void fireBullet(int enemyCode, EnemyManager* enemyManager, int fireCount = 0);
	};

	// ���� ���ݿ� ���õ� �͵�
	struct tagAttackInfo
	{
		float		delay;			// ������
		float		count;			// ī��Ʈ��
		float		angle;			// ����
		float		distance;		// �Ÿ�
		float		circleSize;		// ���� ���� ������(������)

		FloatCircle circleDebug;	// ����׿�
		FloatRect	rectDebug;		// �����?
		AttackInfo	info;			// ��������

		string id;	// ���� ID �����

		// ���� ��Ÿ�� ������Ʈ��
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
		// ���� ���� �����
		void attackInit(float minDamage, float maxDamage, float trueDamage, float critical = 0, float criDamage = 0, float knockBack = 15)
		{
			info.minDamage = minDamage;
			info.maxDamage = maxDamage;
			info.trueDamage = trueDamage;
			info.critical = critical;
			info.criticalDamage = criDamage;
			info.knockBack = knockBack;

			id.clear();
		}
		// ���� (��)
		void attackCircle(int enemyCode, EnemyManager* enemyManager, const Vector2& pos, const float startRad, const float endRad);
		// ���� (��Ʈ)
		void attackRect(int enemyCode, EnemyManager* enemyManager, FloatRect rc);
	};

	// �̵� ���� ����
	struct tagMoveInfo
	{
		Vector2 force;		// �̵��� ��
		Vector2 gravity;	// �̵� ���� ����

		float angle;		// �ﰢ�Լ��� ������ ��� ���
		float delay;		// ������
		float count;		// ī��Ʈ

		// ��Ÿ�� ������Ʈ��
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

	// �ǰ� ����
	struct tagHitInfo
	{
		bool isHit;		// �ǰ� ���������� Ȯ�ο�

		float delay;
		float count;

		// �ǰ� ���� ��Ÿ�ӿ�
		bool update(const float timeElapsed)
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

	tagHitInfo	_hit;		// �ǰ� ����ü�� ��� ���ʹ̰� �����
	tagMoveInfo	_moving;	// �̵� ����ü�� ��� ���ʹ̰� �����

public:
	
	virtual ~Enemy() {}
	virtual void init() {}
	virtual void init(const Vector2& pos) {}
	virtual void init(const Vector2& pos, DIRECTION direction) {}
	virtual void release() = 0;
	virtual void update(float const timeElapsed) = 0;
	virtual void render() = 0;

	// ���� ��ȯ
	virtual void setState(ENEMY_STATE state) {};

	// �ǰ� �� �ൿó��
	virtual void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed) {}

	virtual void dieEffect();

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }

	// ����ü�� ������ ������
	void setCurHp(float curHp) { _curHp = curHp; }
	float getCurHp() const { return _curHp; }

	// �ִ�ü�� ������ ������
	void setMaxHp(float maxHp) { _maxHp = maxHp; }
	float getMaxHp() const { return _maxHp; }

	// EnemyManager���� üũ�� ���� ȣ��
	bool isHit(FloatRect* rc, AttackInfo* info);
	bool isHit(FloatCircle* circle, AttackInfo* info);
	bool isHit(Projectile* projectile);

	// Enemy���� ���� �¾Ҵٸ� ȣ��� �����Լ�
	virtual bool hitEffect(FloatRect* rc, AttackInfo* info) { return false; }
	virtual bool hitEffect(FloatCircle* circle, AttackInfo* info);
	virtual bool hitEffect(Projectile* projectile);

	void setDetectRange(float const range) { _detectRange = range; }
};

