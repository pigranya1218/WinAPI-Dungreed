#include "MagnifyingGlass.h"
#include "stdafx.h"

void MagnifyingGlass::init()
{

	//�Ǽ����� Ÿ��
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::RARE;
	_iconImg = IMAGE_MANAGER->findImage("MagnifyingGlass");

	//�Ǽ����� �ɼ�
	_addStat.damage = 30;

	//�Ǽ����� ����
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
