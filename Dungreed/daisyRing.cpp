#include "daisyRing.h"
#include "stdafx.h"


void daisyRing::init()
{
	
	_iconImg = IMAGE_MANAGER->findImage("DaisyRing");
		
}

void daisyRing::release()
{
}

void daisyRing::update(Player * player, float const elapsedTime)
{
	
		
	
}

void daisyRing::backRender(Player * player)
{
}

void daisyRing::frontRender(Player * player)
{
}

void daisyRing::displayInfo()
{
}

void daisyRing::attack(Player * player)
{
}

void daisyRing::attack(FloatRect * rect, AttackInfo * info)
{
}

void daisyRing::attack(FloatCircle * circle, AttackInfo * info)
{
}

void daisyRing::attack(Projectile * projectile, AttackInfo * info)
{
}

void daisyRing::getHit(Vector2 const position)
{
}

PlayerStat daisyRing::equip()
{
	return PlayerStat();
}
