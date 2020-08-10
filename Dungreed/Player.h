#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "PlayerStat.h"

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

class Player : public GameObject
{
Synthesize(DIRECTION, _direction, Direction)

private:
	GameScene* _gameScene;
	Animation* _ani;
	Image* _img;
	Image* _weapon;
	PLAYER_ANIMATION _aniState;

	// ���� ����
	int		_currHp;				// ���� ü��
	int		_currJumpCount;			// ���� ���� ���� ī��Ʈ
	int		_currSatiety;			// ���� ������
	
	Vector2 _force;				// ���� ĳ���Ϳ� �������� ��

	PlayerStat _baseStat; // �⺻ ����, ���������� ������ �ʴ� ����
	PlayerStat _adjustStat; // ���������� ��ȭ�� ����

	vector<Item*> _inventory; // �κ��丮
	vector<Item*> _equippedWeapon; // ������ ����
	int _currWeaponIndex; // ���� ����ϴ� ���� �ε���, 0 or 1
	vector<Item*> _equippedAcc; // ������ �Ǽ��縮

private:
	void setBaseStat();
	void updateAdjustStat();

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

