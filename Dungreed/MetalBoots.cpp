#include "MetalBoots.h"

void MetalBoots::init()
{
	//악세서리 타입
	_itemCode = 0x03210;
	_iconImg = IMAGE_MANAGER->findImage("MetalBoots");
	

	//악세서리 옵션	
	_itemName = L"강철장화";
	_displayInfos.push_back(L"가시형 피해를 무시함");
	_displayText = L"\"바닥 부분에 강철을 덧댓습니다.\"";

	_addStat.defense = 3;
	//악세서리 가격
	_price = 1800;

}

void MetalBoots::release()
{
}

void MetalBoots::update(Player * player, float const elapsedTime)
{
}

void MetalBoots::backRender(Player * player)
{
}

void MetalBoots::frontRender(Player * player)
{
}

void MetalBoots::displayInfo()
{
}

void MetalBoots::attack(Player * player)
{
}

void MetalBoots::attack(FloatRect * rect, AttackInfo * info)
{
}

void MetalBoots::attack(FloatCircle * circle, AttackInfo * info)
{
}

void MetalBoots::attack(Projectile * projectile, AttackInfo * info)
{
}

void MetalBoots::getHit(Vector2 const position)
{
}

void MetalBoots::equip(Player * player)
{
}
