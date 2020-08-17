#include "MultiBullet.h"
#include "NormalProjectile.h"
#include "stdafx.h"

void MultiBullet::init()
{
	//악세서리 타입
	_itemCode = 0x0330E;
	_iconImg = IMAGE_MANAGER->findImage("MultiBullet");	

	//악세서리 옵션	
	_addStat.minDamage = _addStat.minDamage/2;
	_itemName = L"갈래총탄";
	_displayInfos.push_back(L"총알이 3갈래로 발사되지만, 대미지가 감소");
	_displayText = L"\"탄을 세 갈래로 나누어 뿌려준다. 공격력도 세갈래가 된다.\"";
	//악세서리 가격
	_price = 3200;
}

void MultiBullet::release()
{
}

void MultiBullet::update(Player * player, float const elapsedTime)
{
	
}

void MultiBullet::backRender(Player * player)
{
}

void MultiBullet::frontRender(Player * player)
{
}

void MultiBullet::displayInfo()
{
}

void MultiBullet::attack(Player * player)
{
	
}

void MultiBullet::attack(FloatRect * rect, AttackInfo * info)
{
}

void MultiBullet::attack(FloatCircle * circle, AttackInfo * info)
{
}

void MultiBullet::attack(Projectile * projectile, AttackInfo * info)
{	
	

}

void MultiBullet::getHit(Vector2 const position)
{
}

void MultiBullet::dash(Player * player)
{
}

void MultiBullet::equip(Player * player)
{
}
