#include "StrawberryPieFood.h"

StrawberryPieFood::StrawberryPieFood()
{
	_foodCode = 0x0203;

	_name = "µþ±â ÆÄÀÌ";
	_img = IMAGE_MANAGER->findImage("FOOD/STRAWBERRY_PIE");
	_price = RANDOM->getFromIntTo(1000, 1300);

	_addStat.power = RANDOM->getFromIntTo(10, 15);
	_addStat.trueDamage = RANDOM->getFromIntTo(1, 3);

	_onceStat.currSatiety = RANDOM->getFromIntTo(40, 50);

