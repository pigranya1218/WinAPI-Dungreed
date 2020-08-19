#include "GriffinEggOmeletteFood.h"

GriffinEggOmeletteFood::GriffinEggOmeletteFood()
{
	_foodCode = 0x0201;

	_name = "±×¸®ÇÉ ¾Ë ¿À¹É·¿";
	_img = IMAGE_MANAGER->findImage("FOOD/GRIFFIN_EGG_OMELETTE");
	_price = RANDOM->getFromIntTo(1000, 1300);

	_addStat.maxDashCount = 1;

	_onceStat.currSatiety = RANDOM->getFromIntTo(40, 50);
}
