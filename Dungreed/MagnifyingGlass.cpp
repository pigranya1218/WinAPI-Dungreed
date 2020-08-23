#include "MagnifyingGlass.h"
#include "stdafx.h"

void MagnifyingGlass::init()
{

	//악세서리 타입
	_itemCode = 0x03209;
	_iconImg = IMAGE_MANAGER->findImage("MagnifyingGlass");
	_itemName = L"마법의 돋보기";
	_displayInfos.push_back(L"총알의 크기가 커지고 대미지가 30% 증가");
	_displayInfos.push_back(L"하지만 총알의 속도 30% 감소");
	_displayText = L"\"보는 대상을 실제로 더 크게 만들어 줍니다.\"";
	
	
	
	//악세서리 가격
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

