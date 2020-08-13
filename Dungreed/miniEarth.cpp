#include "miniEarth.h"
#include "stdafx.h"

void miniEarth::init()
{
	//厩技辑府 鸥涝
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("MiniEarth");

	//厩技辑府 可记
	_addStat.criticalChance = 1;
	_addStat.defense = 1;

	x = y = 0;


	//厩技辑府 啊拜
	_price = 600;
}

void miniEarth::release()
{
}

void miniEarth::update(Player * player, float const elapsedTime)
{
	_angle += 0.023f;
}

void miniEarth::backRender(Player * player)
{
	x = cosf(_angle) * 50;
	y = -sinf(_angle) * 50;

	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + x;
	renderPos.y = renderPos.y + y;
	_img->setScale(4);
	_img->render(renderPos, false);
}

void miniEarth::frontRender(Player * player)
{
}

void miniEarth::displayInfo()
{
}

void miniEarth::attack(Player * player)
{
}

void miniEarth::attack(FloatRect * rect, AttackInfo * info)
{
}

void miniEarth::attack(FloatCircle * circle, AttackInfo * info)
{
}

void miniEarth::attack(Projectile * projectile, AttackInfo * info)
{
}

void miniEarth::getHit(Vector2 const position)
{
}

PlayerStat miniEarth::equip()
{
	return PlayerStat();
}
