#include "RaspberryCookieFood.h"

RaspberryCookieFood::RaspberryCookieFood()
{
	_foodCode = 0x0202;

	_name = "라즈베리 쿠키";
	_img = IMAGE_MANAGER->findImage("FOOD/RASPBERRY_COOKIE");
	_price = RANDOM->getFromIntTo(1000, 1300);

	_addStat.attackSpeed = RANDOM->getFromIntTo(30, 50);

	_onceStat.currSatiety = RANDOM->getFromIntTo(40, 50);
}
