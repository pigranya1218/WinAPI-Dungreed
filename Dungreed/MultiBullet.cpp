#include "MultiBullet.h"
#include "NormalProjectile.h"
#include "GuidedProjectile.h"
#include "BoomerangProjectile.h"
#include "stdafx.h"

void MultiBullet::init()
{
	//�Ǽ����� Ÿ��
	_itemCode = 0x0330E;
	_iconImg = IMAGE_MANAGER->findImage("MultiBullet");	

	//�Ǽ����� �ɼ�	
	_addStat.minDamage = _addStat.minDamage/2;
	_itemName = L"������ź";
	_displayInfos.push_back(L"�Ѿ��� 3������ �߻������, ������� ����");
	_displayText = L"\"ź�� �� ������ ������ �ѷ��ش�. ���ݷµ� �������� �ȴ�.\"";
	_addStat.power = -10;
	//�Ǽ����� ����
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
					copyProjectile->setAngleRadian(originProjectile->getAngleRadian() + ((i == 0) ? (-0.025 * PI) : (0.025 * PI))); // ������ ��¦ ���� �ڿ�
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
					copyGuideProjectile->setAngleRadian(guideProjectile->getAngleRadian() + ((i == 0) ? (-0.3 * PI) : (0.3 * PI))); // ������ ��¦ ���� �ڿ�
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
		//		copyBoomerangProjectile->setAngleRadian(boomerangProjectile->getAngleRadian() + ((i == 0) ? (-0.025 * PI) : (0.025 * PI))); // ������ ��¦ ���� �ڿ�
		//		AttackInfo* copyInfo = new AttackInfo(*info);
		//		player->attack(copyBoomerangProjectile, copyInfo);
		//	}
		//}
	}
}

