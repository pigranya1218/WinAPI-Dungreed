#include "stdafx.h"
#include "TomatoSoupFood.h"

TomatoSoupFood::TomatoSoupFood()
{
	_foodCode = 0x0104;

	_name = "토마토수프";
	_img = IMAGE_MANAGER->findImage("FOOD/TOMATO_SOUP");
	_price = RANDOM->getFromIntTo(450, 550);

	_addStat.power = RANDOM->getFromIntTo(15, 25);
	_addStat.criticalChance = RANDOM->getFromIntTo(10, 20);

	_onceStat.currHp = RANDOM->getFromIntTo(10, 20);
	_onceStat.currSatiety = RANDOM->getFromIntTo(40, 50);
}
