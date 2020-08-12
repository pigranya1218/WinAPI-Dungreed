#include "IceBall.h"
#include "stdafx.h"

void IceBall::init()
{
	//�Ǽ����� Ÿ��
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("IceBall");

	//�Ǽ����� �ɼ�
	_addStat.criticalChance = 1;
	_addStat.defense = 1;

	x = y = 0;


	//�Ǽ����� ����
	_price = 600;
}

void IceBall::release()
{
}

void IceBall::update(Player * player, float const elapsedTime)
{
	_angle -= 0.038f;
}

void IceBall::backRender(Player * player)
{
	x = cosf(_angle) * 65;
	y = -sinf(_angle) * 65;

	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + x;
	renderPos.y = renderPos.y + y;
	_img->setScale(4);
	_img->render(renderPos, false);
}

void IceBall::frontRender(Player * player)
{
}

void IceBall::displayInfo()
{
}

void IceBall::attack(Player * player)
{
}

void IceBall::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void IceBall::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void IceBall::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void IceBall::getHit(Vector2 const position)
{
}

PlayerStat IceBall::equip()
{
	return PlayerStat();
}