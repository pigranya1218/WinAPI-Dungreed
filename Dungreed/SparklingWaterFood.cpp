#include "stdafx.h"
#include "SparklingWaterFood.h"

SparklingWaterFood::SparklingWaterFood()
{
	_foodCode = 0x0200;

	_name = "Åº»ê¼ö";
	_img = IMAGE_MANAGER->findImage("FOOD/SPARKLING_WATER");
	_price = RANDOM->getFromIntTo(1000, 1300);

	_onceStat.currSatiety = -RANDOM->getFromIntTo(40, 50);
}
