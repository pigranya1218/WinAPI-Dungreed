#include "Wingboots.h"

void Wingboots::init()
{
	//厩技辑府 鸥涝
	_itemCode = 0x03211;
	_iconImg = IMAGE_MANAGER->findImage("Wingboots");

	//厩技辑府 可记

	_itemName = L"喇 何明";
	_displayInfos.push_back(L"个捞 啊涵况咙");
	_displayText = L"\"惯吧澜捞 酒林 啊涵况笼聪促.\"";

	
	_addStat.jumpPower = 500;
	_addStat.dashYPower = 300;
	_addStat.dashXPower = 300;
	



	//厩技辑府 啊拜
	_price = 1200;
}

void Wingboots::release()
{
}

void Wingboots::update(Player * player, float const elapsedTime)
{
}

void Wingboots::backRender(Player * player)
{
}

void Wingboots::frontRender(Player * player)
{
}

void Wingboots::displayInfo()
{
}

void Wingboots::attack(Player * player)
{
}

void Wingboots::attack(FloatRect * rect, AttackInfo * info)
{
}

void Wingboots::attack(FloatCircle * circle, AttackInfo * info)
{
}

void Wingboots::attack(Projectile * projectile, AttackInfo * info)
{
}

void Wingboots::getHit(Vector2 const position)
{
}

void Wingboots::equip(Player * player)
{
}
