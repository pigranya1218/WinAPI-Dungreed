#include "daisyRing.h"
#include "stdafx.h"


void daisyRing::init()
{
	
	
	numbers = RANDOM->getFromIntTo(0, 1);			
	
	for (int i = 0; i < OPTIONMAX; i++)
	{
		potion[i] = i;
		calculation[OPTIONMAX] = 0;
	}
	if(numbers == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			calculation[i] = RANDOM->getFromIntTo(10, 50);
		}
		int i = RANDOM->getFromIntTo(0, OPTIONMAX);
		_addStat.attackSpeed = calculation[i];
		_addStat.block = calculation[i];	

		if (calculation[i] != 0)
		{
			//Çª½¬¹é
		}
	}
	else if (numbers == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			calculation[i] = RANDOM->getFromIntTo(10, 50);
		}
		int i = RANDOM->getFromIntTo(0, OPTIONMAX);
		_addStat.attackSpeed = calculation[i];
		_addStat.block = calculation[i];
	}
	

	
}

void daisyRing::release()
{
}

void daisyRing::update(Player * player, float const elapsedTime)
{
	
		
	
}

void daisyRing::backRender(Player * player)
{
}

void daisyRing::frontRender(Player * player)
{
}

void daisyRing::displayInfo()
{
}

void daisyRing::attack(Player * player)
{
}

void daisyRing::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void daisyRing::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void daisyRing::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void daisyRing::getHit(Vector2 const position)
{
}

PlayerStat daisyRing::equip()
{
	return PlayerStat();
}
