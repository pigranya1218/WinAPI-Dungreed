#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "PlayerStat.h"

class Item;
class GameScene;
class Projectile;
class Ability;

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
	//�ִϸ��̼� ����� (�������� �ƴ�)
	enum class PLAYER_ANIMATION
	{
		DEFAULT,		//������ ����� ���� �ִϷ����� ������� �ʴ� ���.
		IDLE,
		MOVE		//���� ���� �ƴ� ��쿡��
	};

private:
	GameScene* _gameScene;
	Animation* _ani;	
	Image* _img;	
	PLAYER_ANIMATION _aniState;

	// ���� ����
	int		_level;					// ���� ����
	int		_currHp;				// ���� ü��
	int		_currJumpCount;			// ���� ���� ���� ī��Ʈ
	int		_currDashCount;			// ���� ���� �뽬 ī��Ʈ
	float	_currDashCoolTime;		// ���� �뽬 ��Ÿ��
	int		_currSatiety;			// ���� ������
	int		_currGold;				// ���� ���
	
	Vector2 _force;				// ���� ĳ���Ϳ� �������� ��

	PlayerStat _baseStat; // �⺻ ����, ���������� ������ �ʴ� ����
	PlayerStat _adjustStat; // ���������� ��ȭ�� ����

	vector<Item*> _inventory;				// �κ��丮
	vector<Item*> _equippedWeapon;			// ������ ����
	int			  _currWeaponIndex;			// ���� ����ϴ� ���� �ε���, 0 or 1
	float		  _currWeaponChangeCoolTime;// ���� ��ü ������ ��Ÿ��
	vector<Item*> _equippedAcc;				// ������ �Ǽ��縮

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

	// GETTER & SETTER
	int getLevel() const noexcept { return _level; }
	int getMaxHp() const noexcept { return _adjustStat.maxHp; }
	int getCurrHp() const noexcept { return _currHp; }

	int getGold() const noexcept { return _currGold; }
	int getMaxSatiety() const noexcept { return _adjustStat.maxSatiety; }
	int getSatiety() const noexcept { return _currSatiety; }

	int getMaxDash() const noexcept { return _adjustStat.maxDashCount; }
};

