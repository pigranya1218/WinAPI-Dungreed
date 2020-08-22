#pragma once
#include "Enemy.h"

#define HANDSPEED 600
#define PARTICLEMAX 30
#define SIZEMAX 5

enum class BELIAL_PHASE : unsigned
{
	SHOOTING_READY,	// ź�� �غ�
	SHOOTING_START,	// ź�� ����
	SHOOTING_FINAL,	// ź�� ������
	SWORD_READY,	// �� �غ�
	SWORD_START,	// �� ����
	SWORD_FINAL,	// �� ������
	LASER_R,		// ������ ����
	LASER_L,		// ������ ����
};

enum class HAND_STATE : unsigned
{
	IDLE,
	MOVE,
	ATTACK_READY,
	ATTACK_START,
	ATTACK_FINAL
};

class Belial : public Enemy
{
private:	
	struct tagHandInfo
	{
		Image*		img;		// �� �̹���
		Animation*	ani;		// �� �ִϸ��̼�
		Vector2		position;	// �� ��ǥ
		Vector2		movePos;	// �̵��ؾ��� ��ǥ

		Image*		laserHeadImg;	// ������ �Ӹ�
		Image*		laserBodyImg;	// ������ �߰�
		Animation*	laserHeadAni;	// ������ �Ӹ� �ִϸ��̼�
		Animation*	laserBodyAni;	// ������ �߰� �ִϸ��̼�

		tagMoveInfo moving;	// �̵�
		tagAttackInfo	laserAtk;		// ������ ����

		HAND_STATE	state;	// ���� �� ����

		vector<FloatRect> laserRect;	// ������ ��� ����

		FloatRect			atkRect;	// ������ ���ݷ�Ʈ

		// �ʱ�ȭ
		void init(const Vector2& pos);
		// �޸� ����
		void release()
		{
			ani->release();
			laserHeadAni->release();
			laserBodyAni->release();

			SAFE_DELETE(ani);
			SAFE_DELETE(laserHeadAni);
			SAFE_DELETE(laserBodyAni);
		}
		// �� ������Ʈ
		void update(const float timeElapsed, int enemyType, EnemyManager* enemyManager);
		// ���
		void render(const float scale, bool bisymmetry = 0);

		void setState(HAND_STATE state, const Vector2& movePos = Vector2(0, 0));
	};

	// �ܼ��� �ð� ����
	struct tagTimeInfo
	{
		float delay;
		float count;

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

	// ���� ���� ����
	class tagSwordInfo : public GameObject
	{		
	public:
		Image*	img;	// ����� �̹���
		float	angle;	// �ޱ�	

		tagTimeInfo chargeEffect;
	};

	struct tagParticleInfo
	{
		Image*		img;
		Animation*	ani[5];
		Vector2		pos[5];
	};

	struct tagDeadParticleInfo : public GameObject
	{
		Image* img;
	};

	tagDeadParticleInfo _deadParticle[6];

	tagParticleInfo _particle;

	Vector2			_playerPos;

	tagMoveInfo		_moving;	// �̵�
	tagShootingInfo _shooting;	// ź����

	vector<tagSwordInfo*>	_sword;		// ���� ���� ����
	unsigned int			_swordNum;	// ���� �� �ѹ�
	tagAttackInfo			_swordAtk;	// �� ���� ������

	Image*		_backImg;	// �ı��� �̹���
	Animation*	_backAni;	// �ı��� �ִϸ��̼�
	bool	_backMove;		// �ı��� ��ǥ �̵� �÷���

	tagHandInfo _handR;		// ������
	tagHandInfo _handL;		// �޼�
	int			_laserNum;	// ������ �߻� Ƚ�� ����

	tagTimeInfo _attackCycle;	// ���� �ֱ� �����

	tagTimeInfo _dieEffect;
	int			_effectNum;

	BELIAL_PHASE _phase;	// ���� ����

	bool		_realDead;	// �׾��� ��� ������ �������� ����
	float		_deadAngle;	// �Ӹ��� ���� �����ϸ� �ణ ��鸮�� ��
	bool		_angleWay;	// �Ӹ��� ȸ���Ǵ� ����

public:
	void init(const Vector2& pos);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
	void setPhase(BELIAL_PHASE phase);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);

	void headMove(const float timeElapsed);
};


