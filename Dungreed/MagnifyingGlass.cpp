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


void MagnifyingGlass::attack(Player* player, Projectile * projectile, AttackInfo * info)
{
	if (info->madeByWeapon)
	{
		bool isAlreadyEffected = false;
		for (int i = 0; i < info->usedItem.size(); i++)
		{
			if (info->usedItem[i] == _itemCode)
			{
				isAlreadyEffected = true;
				break;
			}
		}
		if (isAlreadyEffected) return;
		info->usedItem.push_back(_itemCode);
		
		projectile->setSize(projectile->getSize() * 2);
		projectile->setRenderSize(projectile->getRenderSize() * 2);
		projectile->setEffectSize(projectile->getEffectSize() * 2);
		projectile->setForce(projectile->getForce() * 0.7);
		info->minDamage *= 1.3;
		info->maxDamage *= 1.3;
	}
}

