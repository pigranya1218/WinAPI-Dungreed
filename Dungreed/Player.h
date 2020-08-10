#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Item;
class GameScene;
class Projectile;

//�ִϸ��̼� ����� (�������� �ƴ�)
enum class PLAYER_ANIMATION
{
	DEFAULT,		//������ ����� ���� �ִϷ����� ������� �ʴ� ���.
	IDLE,		
	MOVE		//���� ���� �ƴ� ��쿡��
	// JUMP		//���� ���� ���� �� �� �̵��� ���������� ���� ���´� �״��
	// DIE		//���
};

// ���� ���� ����
struct tagAttackInfo
{
	OBJECT_TEAM team;
	int attackID; // ���� ���̵�, ���ݿ� ���� �ߺ��˻� �Ǻ��� ���ؼ� ���
	float damage; // �����
	float knockBack; // �˹� (�о�� ��)
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
	GameScene* _gameScene;
	Animation* _ani;
	Image* _img;
	PLAYER_ANIMATION _aniState;

	// ���� ����
	int		_currHp;			// ���� ü��
	int		_jumpCount;			// ���� ���� ���� ī��Ʈ
	
	Vector2 _force;				// ���� ĳ���Ϳ� �������� ��

	float	_dashPower = 1100;	// �뽬�Ŀ�
	float	_jumpPower = 800;	// �����Ŀ�
	float	_xGravity = 2000;	// x ����
	float	_yGravity = 1600;	// y ����
	
	bool	_isLanded;			// ���߿� ���ִ��� �Ǵ��ϴ� �� ����

	tagStat _baseStat; // �⺻ ����, ���������� ������ �ʴ� ����
	tagStat _adjustStat; // ���������� ��ȭ�� ����

	vector<Item*> _inventory; // �κ��丮
	vector<Item*> _equippedWeapon; // ������ ����
	int _currWeaponIndex; // ���� ����ϴ� ���� �ε���, 0 or 1
	vector<Item*> _equippedAcc; // ������ �Ǽ��縮

public:
	Player() {};
	~Player() {};

	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; };

	void setAni(PLAYER_ANIMATION setAni);

	// �����۵��� ȣ���� �Լ���
	void attack(FloatRect* rect, tagAttackInfo* info);
	void attack(FloatCircle* circle, tagAttackInfo* info);
	void attack(Projectile* projectile, tagAttackInfo* info);

	virtual void init() override;
	virtual void release() override;
	virtual void update(float const elapsedTime) override;
	virtual void render() override;
};

