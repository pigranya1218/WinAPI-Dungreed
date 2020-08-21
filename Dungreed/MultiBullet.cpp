#include "MultiBullet.h"
#include "NormalProjectile.h"
#include "GuidedProjectile.h"
#include "BoomerangProjectile.h"
#include "stdafx.h"

void MultiBullet::init()
{
	//악세서리 타입
	_itemCode = 0x0330E;
	_iconImg = IMAGE_MANAGER->findImage("MultiBullet");	

	//악세서리 옵션	
	_addStat.minDamage = _addStat.minDamage/2;
	_itemName = L"갈래총탄";
	_displayInfos.push_back(L"총알이 3갈래로 발사되지만, 대미지가 감소");
	_displayText = L"\"탄을 세 갈래로 나누어 뿌려준다. 공격력도 세갈래가 된다.\"";
	_addStat.power = -10;
	//악세서리 가격
	_price = 3200;
}

void MultiBullet::attack(Player* player, Projectile * projectile, AttackInfo * info)
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
		info->minDamage *= 0.5;
		info->maxDamage *= 0.5;

		if (dynamic_cast<NormalProjectile*>(projectile))
		{
			NormalProjectile* originProjectile = dynamic_cast<NormalProjectile*>(projectile);
			for (int i = 0; i < 2; i++)
			{
				if (originProjectile != nullptr)
				{
					NormalProjectile* copyProjectile = new NormalProjectile(*originProjectile);
					copyProjectile->setAngleRadian(originProjectile->getAngleRadian() + ((i == 0) ? (-0.025 * PI) : (0.025 * PI))); // 각도를 살짝 꺾은 뒤에
					AttackInfo* copyInfo = new AttackInfo(*info);
					string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime() + i);
					copyInfo->attackID = TTYONE_UTIL::getHash(attackCode);
					player->attack(copyProjectile, copyInfo);
				}
			}
		}
		else if (dynamic_cast<GuidedProjectile*>(projectile))
		{
			GuidedProjectile* guideProjectile = dynamic_cast<GuidedProjectile*>(projectile);
			for (int i = 0; i < 2; i++)
			{
				if (guideProjectile != nullptr)
				{
					GuidedProjectile* copyGuideProjectile = new GuidedProjectile(*guideProjectile);
					copyGuideProjectile->setAngleRadian(guideProjectile->getAngleRadian() + ((i == 0) ? (-0.3 * PI) : (0.3 * PI))); // 각도를 살짝 꺾은 뒤에
					AttackInfo* copyInfo = new AttackInfo(*info);
					string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime() + i);
					copyInfo->attackID = TTYONE_UTIL::getHash(attackCode);
					player->attack(copyGuideProjectile, copyInfo);
				}
			}
		}

		//BoomerangProjectile* boomerangProjectile = dynamic_cast<BoomerangProjectile*>(projectile);
		//for (int i = 0; i < 2; i++)
		//{
		//	if (boomerangProjectile != nullptr)
		//	{
		//		BoomerangProjectile* copyBoomerangProjectile = new BoomerangProjectile(*boomerangProjectile);
		//		copyBoomerangProjectile->setAngleRadian(boomerangProjectile->getAngleRadian() + ((i == 0) ? (-0.025 * PI) : (0.025 * PI))); // 각도를 살짝 꺾은 뒤에
		//		AttackInfo* copyInfo = new AttackInfo(*info);
		//		player->attack(copyBoomerangProjectile, copyInfo);
		//	}
		//}
	}
}

