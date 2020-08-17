#include "MagnifyingGlass.h"
#include "stdafx.h"

void MagnifyingGlass::init()
{

	//악세서리 타입
	_itemCode = 0x03209;
	_iconImg = IMAGE_MANAGER->findImage("MagnifyingGlass");
	_itemName = L"마법의 돋보기";
	_displayInfos.push_back(L"총알의 크기가 커지고 대미지가 증가하지만, 공격속도 30% 감소");
	_displayText = L"\"보는 대상을 실제로 더 크게 만들어 줍니다.\"";
	//악세서리 옵션
	_addStat.maxDamage = _addStat.maxDamage*1.7f;
	_addStat.minDamage = _addStat.minDamage*1.7f;
	_addStat.attackSpeed = _addStat.attackSpeed / 0.3f;

	//악세서리 가격
	_price = 2400;

}

void MagnifyingGlass::release()
{
}

void MagnifyingGlass::update(Player * player, float const elapsedTime)
{
}

void MagnifyingGlass::backRender(Player * player)
{
}

void MagnifyingGlass::frontRender(Player * player)
{
}

void MagnifyingGlass::displayInfo()
{
}

void MagnifyingGlass::attack(Player * player)
{
}

void MagnifyingGlass::attack(FloatRect * rect, AttackInfo * info)
{
}

void MagnifyingGlass::attack(FloatCircle * circle, AttackInfo * info)
{
}

void MagnifyingGlass::attack(Projectile * projectile, AttackInfo * info)
{
	
	projectile->setSize(projectile->getSize() * 3);
	
}

void MagnifyingGlass::getHit(Vector2 const position)
{
}

void MagnifyingGlass::equip(Player* player)
{
}
