#include "stdafx.h"
#include "GrilledMushroomFood.h"

GrilledMushroomFood::GrilledMushroomFood()
{
	_foodCode = 0x0102;

	_name = "±¸¿î ¹ö¼¸";
	_img = IMAGE_MANAGER->findImage("FOOD/GRILLED_MUSHROOM");
	_price = RANDOM->getFromIntTo(450, 550);

	_addStat.power = RANDOM->getFromIntTo(15, 25);
	_addStat.criticalChance = RANDOM->getFromIntTo(15, 25);
	_addStat.criticalDamage = RANDOM->getFromIntTo(15, 25);

	_onceStat.currHp = RANDOM->getFromIntTo(10, 20);
	_onceStat.currSatiety = RANDOM->getFromIntTo(40, 50);
}
