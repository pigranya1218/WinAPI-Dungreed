#include "DaisyRing.h"
#include "stdafx.h"


void DaisyRing::init()
{
	
	_iconImg = IMAGE_MANAGER->findImage("DaisyRing");
	_itemCode = 0x0340F;	
	_itemName = L"데이지 반지";	
	_displayText = L"\"희망을 드리겠어요.\"";
	_count = 0;
	
	

	for (int i = 0; i < 12; i++)
	{
		_DaisyRingStat[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		int k = RANDOM->getFromIntTo(0, 9);
		_DaisyRingStat[k] = RANDOM->getFromIntTo(10, 30);
				
	}

	for (int i = 0; i < 10; i++)
	{
		if (_DaisyRingStat[i] != 0)
		{
			_count += 1;
		}		
	}	
	if (_count < 4)
	{
		return init();
	}
	

	_addStat.attackSpeed = _DaisyRingStat[0];
	_addStat.block = _DaisyRingStat[1];
	_addStat.criticalChance = _DaisyRingStat[2];
	_addStat.criticalDamage = _DaisyRingStat[3];
	_addStat.dashDamage = _DaisyRingStat[4];
	_addStat.defense = _DaisyRingStat[5];
	_addStat.evasion = _DaisyRingStat[6];			
	_addStat.power = _DaisyRingStat[7];	
	_addStat.reloadSpeed = _DaisyRingStat[8];
	_addStat.trueDamage = _DaisyRingStat[9];
	
	
	

	_price = 4300;


}

void DaisyRing::release()
{
}

void DaisyRing::update(Player * player, float const elapsedTime)
{
	
	
	
}

void DaisyRing::backRender(Player * player)
{
}

void DaisyRing::frontRender(Player * player)
{
}

