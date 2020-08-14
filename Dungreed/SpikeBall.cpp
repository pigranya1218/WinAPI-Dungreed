#include "SpikeBall.h"
#include "stdafx.h"

void SpikeBall::init()
{
	//厩技辑府 鸥涝
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;	
	_img = IMAGE_MANAGER->findImage("SpikeBall");
	_iconImg = IMAGE_MANAGER->findImage("SpikeBall");
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
	x = cosf(_angle) * 110;
	y = -sinf(_angle) * 110;

	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + x;
	renderPos.y = renderPos.y + y;
	_img->setScale(4);
	_img->render(CAMERA->getRelativeV2(renderPos), false);
	Vector2 size = Vector2(_img->getFrameSize().x * 4, _img->getFrameSize().y * 4);
	_crash = rectMakePivot(Vector2(renderPos), size, PIVOT::CENTER);
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_crash));
}



void SpikeBall::displayInfo()
{
}

void SpikeBall::attack(Player* player)
{
}

void SpikeBall::attack(FloatRect * rect, AttackInfo * info)
{
}

void SpikeBall::attack(FloatCircle * circle, AttackInfo * info)
{
}

void SpikeBall::attack(Projectile * projectile, AttackInfo * info)
{
}

void SpikeBall::getHit(Vector2 const position)
{
}

void SpikeBall::equip(Player* player)
{
}
