#include "SpikeBall.h"
#include "stdafx.h"

void SpikeBall::init()
{
	//厩技辑府 鸥涝
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("SpikeBall");
	
	//厩技辑府 可记
	_addStat.criticalChance = 1;
	_addStat.defense = 1;
	
	x = y = 0;

	
	//厩技辑府 啊拜
	_price = 600;

}

void SpikeBall::release()
{
}

void SpikeBall::update(Player* player, float const elapsedTime)
{
	_angle += 0.033f;
}

void SpikeBall::frontRender(Player* player)
{
}

void SpikeBall::backRender(Player* player)
{
	x = cosf(_angle) * 85;
	y = -sinf(_angle) * 85;

	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + x;
	renderPos.y = renderPos.y + y;
	_img->setScale(4);
	_img->render(renderPos, false);
}



void SpikeBall::displayInfo()
{
}

void SpikeBall::attack(Player* player)
{
}

void SpikeBall::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void SpikeBall::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void SpikeBall::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void SpikeBall::getHit(Vector2 const position)
{
}

PlayerStat SpikeBall::equip()
{
	return PlayerStat();
}
