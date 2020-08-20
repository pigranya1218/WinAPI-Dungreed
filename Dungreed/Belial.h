#pragma once
#include "Enemy.h"

#define HANDSPEED 600
#define PARTICLEMAX 30
#define SIZEMAX 5

enum class BELIAL_PHASE : unsigned
{
	SHOOTING_READY,	// ź�� �غ�
	SHOOTING,		// ź�� ����
	SHOOTING_FINAL,	// ź�� ������
	SWORD_READY,	// �� �غ�
	SWORD,			// �� ����
	SWORD_FINAL,	// �� ������
	LASER_READY,	// ������ �غ�
	LASER,			// ������ �߻�
	LASER_FINAL		// ������ ������
};

class Belial : public Enemy
{
private:	
	struct tagHandInfo
	{

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

	struct tagSwordPosAngle
	{		
		Vector2 pos;	// ������
		float angle;	// �ޱ�
	};

	tagMoveInfo		_moving;		// �̵�
	tagShootingInfo _shooting;		// ź����
	tagShootingInfo _swordBullet;	// �� ������ ����

	Image*						_swordImg;		// �� �̹���
	vector<tagSwordPosAngle>	_swordPosAngle;	// �� ��¿�

	Image*		_backImg;		// �ı��� �̹���
	Animation*	_backAni;		// �ı��� �ִϸ��̼�

	tagHandInfo _handR;			// ������
	tagHandInfo _handL;			// �޼�

	tagTimeInfo _attackCycle;	// ���� �ֱ� �����

	BELIAL_PHASE _phase;		// ���� ����

public:
	void init(const Vector2& pos);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
	void setPhase(BELIAL_PHASE phase);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};


