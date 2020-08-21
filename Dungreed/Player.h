#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "PlayerStat.h"
#include "AttackInfo.h"

class Item;
class Food;
class GameScene;
class Projectile;
class Ability;
class Costume;

class Player : public GameObject
{
Synthesize(DIRECTION, _direction, Direction)

private:
	GameScene* _gameScene;

	// ���� ����
	Costume* _costume;				// ���� ������ �ڽ�Ƭ
	vector<size_t>		_attackedId; // �ֱ� ���ݹ޾Ҵ� ���ݵ��� ���̵� ������ �����ϴ� ����, �ִ� 10ĭ ���� �����ϸ� ������ ��

	int		_level;					// ���� ����
	int		_currHp;				// ���� ü��
	int		_currJumpCount;			// ���� ���� ���� ī��Ʈ
	int		_currDashCount;			// ���� ���� �뽬 ī��Ʈ
	float	_currDashCoolTime;		// ���� �뽬 ��Ÿ��
	float	_currDashTime;			// ���� �뽬 ���� �����ð�
	int		_currSatiety;			// ���� ������
	int		_currGold;				// ���� ���
	
	float	_currHitTime;			// �ǰ� Ÿ��
	
	
	Vector2 _force;				// ���� ĳ���Ϳ� �������� ��

	PlayerStat _adjustStat; // ���� �������� ��ȭ�� ���� ����

	Item*		_hand; // �ָ���
	vector<Item*> _inventory;				// �κ��丮
	vector<Item*> _equippedWeapon;			// ������ ����
	int			  _currWeaponIndex;			// ���� ����ϴ� ���� �ε���, 0 or 1
	float		  _currWeaponChangeCoolTime;// ���� ��ü ������ ��Ÿ��
	vector<Item*> _equippedAcc;				// ������ �Ǽ��縮
	vector<Food*> _ateFood;					// ���� ���ĵ�

private:
	void updateAdjustStat();
	void swap(Item* &a, Item* &b);

public:
	Player() {};
	~Player() {};

	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; };

	// �����۵��� ȣ���� �Լ���
	bool attack(FloatRect* rect, AttackInfo* info);
	bool attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	virtual void init() override;
	virtual void release() override;
	virtual void update(float const elapsedTime) override;
	virtual void render() override;

	// �ǰ� üũ�� ���� ȣ��
	bool isHit(FloatRect* rc, AttackInfo* info);
	bool isHit(FloatCircle* circle, AttackInfo* info);
	bool isHit(Projectile* projectile, bool isOnceCollision);

	// ���� �ǰݵǾ��ٸ� ȣ��� �����Լ�
	bool hitEffect(FloatRect* rc, AttackInfo* info);
	bool hitEffect(FloatCircle* circle, AttackInfo* info);
	bool hitEffect(Projectile* projectile);

	// GETTER & SETTER
	int getLevel() const noexcept { return _level; }
	int getMaxHp() const noexcept { return _adjustStat.maxHp; }
	int getCurrHp() const noexcept { return _currHp; }
	void setCurrHp(int hp) { _currHp = min(_adjustStat.maxHp, hp); }

	int getGold() const noexcept { return _currGold; }
	void setGold(int gold) { _currGold = max(0, gold); }
	int getMaxSatiety() const noexcept { return _adjustStat.maxSatiety; }
	int getSatiety() const noexcept { return _currSatiety; }

	int getMaxDash() const noexcept { return _adjustStat.maxDashCount; }
	int getCurrDash() const noexcept { return _currDashCount; }

	int getWeaponIndex() const noexcept { return _currWeaponIndex; }
	Item* getWeapon(int index) const { return _equippedWeapon[index]; };
	Item* getAcc(int index) const { return _equippedAcc[index]; }
	Item* getInvenItem(int index) const { return _inventory[index]; }
	Image* getWeaponImg(int index) const;

	void equipItem(int index);		// �κ��丮�� �ִ� �������� ������
	void unequipWeapon(int index);	// ���� �������̴� �������� ������
	void unequipAcc(int index);		// �Ǽ��縮 �������̴� �������� ������
	void swapItem(int indexA, int indexB);

	bool ateFood(Food* food); // true�� �Ծ���, false�� ���� ������

	PlayerStat getCurrStat() { return _adjustStat; };
	
	Costume* getCurrCostume() { return _costume; }
	void setCurrCostume(Costume* costume) { _costume = costume; }
	float getAttackSpeed();
	float getReloadSpeed();
	float getMinDamage();
	float getMaxDamage();

	// �������� ���� �Լ�
	Vector2 getEnemyPos(Vector2 pos);
	void moveRoom(Vector2 dir);
};

