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

	
	_addStat.yGravity = -1800;
	_addStat.xGravity = -1000;

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

