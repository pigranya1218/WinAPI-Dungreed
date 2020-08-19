#include "MagnifyingGlass.h"
#include "stdafx.h"

void MagnifyingGlass::init()
{

	//�Ǽ����� Ÿ��
	_itemCode = 0x03209;
	_iconImg = IMAGE_MANAGER->findImage("MagnifyingGlass");
	_itemName = L"������ ������";
	_displayInfos.push_back(L"�Ѿ��� ũ�Ⱑ Ŀ���� ������� 30% ����");
	_displayInfos.push_back(L"������ �Ѿ��� �ӵ� 30% ����");
	_displayText = L"\"���� ����� ������ �� ũ�� ����� �ݴϴ�.\"";
	
	//�Ǽ����� �ɼ�
	// _addStat.power = 17;
	
	
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
	if (info->madeByWeapon)
	{
		projectile->setSize(projectile->getSize() * 2);
		projectile->setRenderSize(projectile->getRenderSize() * 2);
		projectile->setForce(projectile->getForce() * 0.7);
		info->minDamage *= 1.3;
		info->maxDamage *= 1.3;
	}
	
}

void MagnifyingGlass::getHit(Vector2 const position)
{
}

void MagnifyingGlass::equip(Player* player)
{
	

}
