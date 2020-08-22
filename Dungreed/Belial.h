#pragma once
#include "Enemy.h"

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
	IDLE,			// �⺻
	MOVE,			// �̵�
	ATTACK_READY,	// �غ�
	ATTACK_START,	// �߻�!
	ATTACK_FINAL	// ����
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

		tagMoveInfo		moving;		// �̵�
		tagAttackInfo	laserAtk;	// ������ ����

		HAND_STATE	state;			// ���� �� ����

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
		void render(const float scale, const float alpha, bool bisymmetry = 0);

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

	// �ܼ��� ��¸� �ϸ��
	struct tagParticleInfo
	{
		Image*		img;
		Animation*	ani[5];
		Vector2		pos[5];
	};

	// ��ƼŬ ������������ �浹 �˻��Ϸ��� ��ӹ���
	struct tagDeadParticleInfo : public GameObject
	{
		Image* img;
	};

	BELIAL_PHASE	_phase;		// ���� ����	

	Vector2			_playerPos;	// �÷��̾� �������� ������ ������ ����

	tagMoveInfo		_moving;	// �̵�

	tagShootingInfo _shooting;	// ź����

	vector<tagSwordInfo*>	_sword;		// ���� ���� ����
	unsigned int			_swordNum;	// ���� �� �ѹ�
	tagAttackInfo			_swordAtk;	// �� ���� ������

	Image*			_backImg;	// �ı��� �̹���
	Animation*		_backAni;	// �ı��� �ִϸ��̼�
	tagParticleInfo	_particle;	// �ı� ��ƼŬ
	bool			_backMove;	// �ı��� ��ǥ �̵� �÷���

	tagHandInfo _handR;			// ������
	tagHandInfo _handL;			// �޼�
	int			_laserNum;		// ������ �߻� Ƚ�� ����

	tagTimeInfo _attackCycle;	// ���� �ֱ� �����

	tagTimeInfo			_dieEffect;			// ������ ����Ʈ ���� �ð�
	tagDeadParticleInfo _deadParticle[6];	// ������ �����
	int					_effectNum;			// ������ ����Ʈ ���Ƚ��
	bool				_realDead;			// �׾��� ��� ������ �������� ����
	float				_deadAngle;			// �Ӹ��� ���� �����ϸ� �ణ ��鸮�� ��
	bool				_angleWay;			// �Ӹ��� ȸ���Ǵ� ����	

	float		_headAlpha;		// �Ӹ� ���İ�
	float		_handAlpha;		// ��� ���İ�

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


