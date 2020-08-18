#include "MagnifyingGlass.h"
#include "stdafx.h"

void MagnifyingGlass::init()
{

	//�Ǽ����� Ÿ��
	_itemCode = 0x03209;
	_iconImg = IMAGE_MANAGER->findImage("MagnifyingGlass");
	_itemName = L"������ ������";
	_displayInfos.push_back(L"�Ѿ��� ũ�Ⱑ Ŀ���� ������� ����������, ���ݼӵ� 30% ����");
	_displayText = L"\"���� ����� ������ �� ũ�� ����� �ݴϴ�.\"";
	//�Ǽ����� �ɼ�
	_addStat.maxDamage = _addStat.maxDamage*1.7f;
	_addStat.minDamage = _addStat.minDamage*1.7f;
	_addStat.attackSpeed = _addStat.attackSpeed / 0.3f;

	//�Ǽ����� ����
	_price = 2400;

}

void MagnifyingGlass::release()
{
}

void MagnifyingGlass::update(Player * player, float const elapsedTime)
{
}

void MagnifyingGlass::backRender(Player * player)
{
}

void MagnifyingGlass::frontRender(Player * player)
{
}

void MagnifyingGlass::displayInfo()
{
}

void MagnifyingGlass::attack(Player * player)
{
}

void MagnifyingGlass::attack(FloatRect * rect, AttackInfo * info)
{
}

void MagnifyingGlass::attack(FloatCircle * circle, AttackInfo * info)
{
}

void MagnifyingGlass::attack(Projectile * projectile, AttackInfo * info)
{
	
	projectile->setSize(projectile->getSize() * 3);
	
}

void MagnifyingGlass::getHit(Vector2 const position)
{
}

void MagnifyingGlass::equip(Player* player)
{
}
