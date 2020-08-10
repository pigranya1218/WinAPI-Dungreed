#pragma once
#include "GameObject.h"

class TestScene;

//�ִϸ��̼� ����� (�������� �ƴ�)
enum class PLAYER_ANIMATION
{
	DEFAULT,		//������ ����� ���� �ִϷ����� ������� �ʴ� ���.
	IDLE,		
	MOVE		//���� ���� �ƴ� ��쿡��
	// JUMP		//���� ���� ���� �� �� �̵��� ���������� ���� ���´� �״��
	// DIE		//���
};

struct tagStat
{
	// ���� ����
	int		_maxJumpCount;		// �ִ� ���� Ƚ��
	int		_maxHp;				// �ִ� ü��
	int		_maxDashCount;		// �ִ� �뽬 Ƚ��
	float	_satiety;			// ������
	float	_power;				// ���� (���� ��ġ 1�� ���ط� 1% ���)
	float	_damage;			// ���� ���ݷ� // ���Ϳ��� ���� ������ = (������ݷ� * (1+����/100))
	float	_trueDamage;		// ���� ������
	float	_criticalChance;	// ũ��Ƽ�� Ȯ��
	float	_criticalDamage;	// ũ��Ƽ�� ������
	float	_dashDamage;		// �뽬 ���ݷ�
	float	_toughness;			// ������
	float	_defense;			// ����
	float	_block;				// ����
	float	_evasion;			// ȸ��
	float	_attackSpeed;		// ���ݼӵ�
	float	_moveSpeed;			// �̵��ӵ�
};

class Player : public GameObject
{
Synthesize(DIRECTION, _direction, Direction)

private:
	TestScene* _testScene;
	Animation* _ani;
	Image* _img;
	Image* _weapon;
	PLAYER_ANIMATION _aniState;

	// ���� ����
	int		_currHp;			// ���� ü��
	int		_jumpCount;			// ���� ���� ���� ī��Ʈ
	
	Vector2 _force;				// ���� ĳ���Ϳ� �������� ��

	const float	_dashPower = 20;	// �뽬�Ŀ�
	const float	_jumpPower = 20;	// �����Ŀ�
	float	_xGravity;				// �뽬 ����
	float	_yGravity;				// ���� ����
	
	bool	_isJump;				// ���� ó�� (����� ������ ����)
	bool	_isAttack;				// ���콺 ��Ŭ���� ����
	tagStat _stat; // ����
	FloatRect _leftHand; // �޼� 
	FloatRect _rightHand; // ������

public:
	Player() {};
	~Player() {};

	void move(Vector2 force);
	void setAni(PLAYER_ANIMATION setAni);

	void init();
	void release();
	void update();
	void render();
	void attack();

	void setTestScene(TestScene* testScene) { _testScene = testScene; }
};

