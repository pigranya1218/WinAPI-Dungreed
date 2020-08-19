#pragma once
#include "Player.h"
#include "ProjectileManager.h"
#include "AttackInfo.h"

enum class ITEM_TYPE : int
{
	WEAPON_ONE_HAND = 0x01000, // �Ѽ� ����
	WEAPON_TWO_HAND = 0x02000, // ��� ����
	ACC = 0x03000, // �Ǽ��縮
	WEAPON_SUB = 0x04000, // ���� ����
};

enum class ITEM_RANK : int
{
	NORMAL = 0x00100, // �Ϲ�
	HIGH = 0x00200, // ���
	RARE = 0x00300, // ���
	LEGEND = 0x00400 // ����
};
//�Ѽ� ���� - 0x014xx;
//�ٰŸ� 0x0xx00~
//���Ÿ� 0x0xx60~


class Item
{
protected:
	int _itemCode; // ������ �ڵ�
	
	wstring _itemName; // ������ �̸�
	vector<wstring> _displayInfos; // ������ �ɷ¿� ���� ����
	wstring _displayText; // ������ ���

	// ITEM_TYPE _type; // ������ Ÿ��
	// ITEM_RANK _rank; // ������ ���
	Image* _iconImg; // ������ �̹���

	
	int _price; // ����
	PlayerStat _addStat; // ������ ���� �ɼ� (�÷��̾��� ���ȿ� �������� ����)
	PlayerStat _adjustStat; // �÷��̾��� ������ �ݿ��� ���� ���� (����� attackSpeed, reloadSpeed�� �Ű澸)

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(Player* player, float const elapsedTime) = 0;
	virtual void backRender(Player* player) = 0;
	virtual void frontRender(Player* player) = 0;
	virtual void displayInfo() = 0; // �κ��丮���� ������ ������

	virtual void attack(Player* player) = 0; // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	virtual void attack(FloatRect* rect, AttackInfo* info) = 0; // ���� ��Ʈ�� �����Ű�� �Լ� 
	virtual void attack(FloatCircle* circle, AttackInfo* info) = 0; // ���� ��Ŭ�� �����Ű�� �Լ�
	virtual void attack(Projectile* projectile, AttackInfo* info) = 0; // źȯ�� �����Ű�� �Լ�

	virtual void dash(Player* player) {}; // �÷��̾ �뽬���� ��
	virtual void reload(Player* player) {}; // �÷��̾ ��������ư�� ������ ��

	virtual void getHit(Vector2 const position) = 0; // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player* player) {}; // �������� �������� �� ȣ��� �Լ�(�÷��̾� ���ȿ� ����Ͽ� ��� ���� ��ȭ, ��� ��ġ ��ȭ ��)
	
	virtual wstring getBulletUI() { return L""; }
	virtual float getBulletRatio() { return 0.f; }

	int getItemCode() const noexcept { return _itemCode; }
	ITEM_TYPE getItemType() const noexcept;
	ITEM_RANK getItemRank() const noexcept;
	int getPrice() const noexcept { return _price; }
	wstring getItemName() const noexcept { return _itemName; }
	vector<wstring> getDisplayInfos() const noexcept { return _displayInfos; }
	wstring getDisplayText() const noexcept { return _displayText; }
	Image* getIconImg() const noexcept { return _iconImg; }
	PlayerStat getAddStat() const noexcept { return _addStat; }
	float getAttackSpeed() { return _adjustStat.attackSpeed; }
	float getReloadSpeed() { return _adjustStat.reloadSpeed; }
	float getMinDamage() { return _addStat.minDamage; }
	float getMaxDamage() { return _addStat.maxDamage; }

};