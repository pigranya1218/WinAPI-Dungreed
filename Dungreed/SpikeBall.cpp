#include "SpikeBall.h"
#include "stdafx.h"

void SpikeBall::init()
{
	//�Ǽ����� Ÿ��
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("SpikeBall");
	
	//�Ǽ����� �ɼ�
	_addStat.criticalChance = 1;
	_addStat.defense = 1;
	x = y = 0;

	
	//�Ǽ����� ����
	_price = 600;

}

void SpikeBall::release()
{
}

void SpikeBall::update(float const elapsedTime)
{
	_angle += 0.033f;
}

void SpikeBall::render(Vector2 pos, float angle)
{
	
	
	x = cosf(_angle) * 70;
	y = -sinf(_angle) * 70;
	
	Vector2 renderPos = pos;
	renderPos.x = renderPos.x + x;
	renderPos.y = renderPos.y + y;
	_img->setScale(4);
	_img->render(renderPos, false);
	
}

void SpikeBall::displayInfo()
{
}

void SpikeBall::attack(Vector2 const position, float const angle)
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
