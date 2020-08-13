#include "IceBall.h"
#include "stdafx.h"

void IceBall::init()
{
	//厩技辑府 鸥涝
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("IceBall");

	//厩技辑府 可记
	_addStat.criticalChance = 1;
	_addStat.defense = 1;

	

	x = y = 0;


	//厩技辑府 啊拜
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
	

	Vector2 renderPos = player->getPosition();
	x = cosf(_angle) * 65;
	y = -sinf(_angle) * 65;
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

void IceBall::attack(FloatRect * rect, AttackInfo * info)
{
}

void IceBall::attack(FloatCircle * circle, AttackInfo * info)
{
}

void IceBall::attack(Projectile * projectile, AttackInfo * info)
{
}

void IceBall::getHit(Vector2 const position)
{
}

PlayerStat IceBall::equip()
{
	return PlayerStat();
}
