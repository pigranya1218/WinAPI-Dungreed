#include "stdafx.h"
#include "EggFriedFood.h"

EggFriedFood::EggFriedFood()
{
	_foodCode = 0x0100;

	_name = "계란 후라이";
	_img = IMAGE_MANAGER->findImage("FOOD/EGG_FRIED");
	_price = RANDOM->getFromIntTo(450, 550);

	_addStat.power = RANDOM->getFromIntTo(15, 25);
	_addStat.maxHp = RANDOM->getFromIntTo(10, 20);

	_onceStat.currHp = RANDOM->getFromIntTo(10, 20);
	_onceStat.currSatiety = RANDOM->getFromIntTo(40, 50);
}
