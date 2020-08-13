#include "MagnifyingGlass.h"
#include "stdafx.h"

void MagnifyingGlass::init()
{
	_addStat.damage = 30;
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

void MagnifyingGlass::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void MagnifyingGlass::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void MagnifyingGlass::attack(Projectile * projectile, tagAttackInfo * info)
{
	projectile->setSize(projectile->getSize() * 3);
}

void MagnifyingGlass::getHit(Vector2 const position)
{
}

PlayerStat MagnifyingGlass::equip()
{
	return PlayerStat();
}
