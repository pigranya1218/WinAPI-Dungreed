#include "MultiBullet.h"
#include "NormalProjectile.h"
#include "stdafx.h"

void MultiBullet::init()
{
	//�Ǽ����� Ÿ��
	_itemCode = 0x0330E;
	_iconImg = IMAGE_MANAGER->findImage("MultiBullet");	

	//�Ǽ����� �ɼ�	
	_addStat.minDamage = _addStat.minDamage/2;

	//�Ǽ����� ����
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
