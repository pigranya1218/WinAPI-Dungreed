#include "stdafx.h"
#include "BreadFood.h"

BreadFood::BreadFood()
{
	_foodCode = 0x0101;

	_name = "»§";
	_img = IMAGE_MANAGER->findImage("FOOD/BREAD");
	_price = RANDOM->getFromIntTo(450, 550);

	_addStat.power = RANDOM->getFromIntTo(15, 25);
	_addStat.defense = RANDOM->getFromIntTo(15, 25);

	_onceStat.currHp = RANDOM->getFromIntTo(10, 20);
	_onceStat.currSatiety = RANDOM->getFromIntTo(40, 50);
}
