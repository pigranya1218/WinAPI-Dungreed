#pragma once

class Player;

enum class ITEM_TYPE
{
	WEAPON_ONE_HAND, // �Ѽ� ����
	WEAPON_TWO_HAND, // ��� ����
	ACC // �Ǽ��縮
};

enum class ITEM_RANK
{
	NORMAL, // �Ϲ�
	HIGH, // ���
	RARE, // ���
	LEGEND // ����
};

class Item
{
private:
	ITEM_TYPE _type; // ������ Ÿ��
	ITEM_RANK _rank; // ������ ���
	Image* _img; // ������ �̹���
	int _price; // ����

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(float const elapsedTime) = 0;
	virtual void render(Vector2 pos, float angle) = 0;
	virtual void displayInfo() = 0; // �κ��丮���� ������ ������

	virtual void attack(Vector2 const position, Vector2 const angle) = 0; // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	virtual void attack(FloatRect* rect, tagAttackInfo* info) = 0; // ���� ��Ʈ�� �����Ű�� �Լ� 
	virtual void attack(FloatCircle* circle, tagAttackInfo* info) = 0; // ���� ��Ŭ�� �����Ű�� �Լ�
	virtual void attack(Projectile* projectile, tagAttackInfo* info) = 0; // źȯ�� �����Ű�� �Լ�

	virtual void getHit(Vector2 const position) = 0; // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player& player) = 0; // �������� �������� �� ȣ��� �Լ�, �÷��̾��� ������ ����
	
	ITEM_TYPE getType() const noexcept { return _type; }

	int getPrice() const noexcept { return _price; }
};