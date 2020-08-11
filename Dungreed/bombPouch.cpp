#include "bombPouch.h"

void bombPouch::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::RARE;

	isBoom = false;

	
	
	_price = 1200;
}

void bombPouch::release()
{
}

void bombPouch::update(Player* player, float const elapsedTime)
{
	renderPos;
	
	if (KEY_MANAGER->isOnceKeyDown('R') )
	{
		x = renderPos.x;
		y = renderPos.y;
		isBoom = true;	
	}
	if (RC.bottom > WINSIZEY)
	{
		isBoom = false;
	}
	if (isBoom)
	{
		RC = rectMakePivot(Vector2(x,y), Vector2(50, 50), PIVOT::CENTER);
		y += 10;
	}
	else if (!isBoom )
	{
		
		RC = rectMakePivot(Vector2(renderPos), Vector2(0, 0), PIVOT::CENTER);
	}
}

void bombPouch::frontRender(Vector2 pos, float angle)
{

}

void bombPouch::backRender(Vector2 pos, float angle)
{
	renderPos = pos;
	D2D_RENDERER->drawRectangle(RC);
}

void bombPouch::displayInfo()
{
}

void bombPouch::attack(Vector2 const position, float const angle)
{
}

void bombPouch::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void bombPouch::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void bombPouch::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void bombPouch::getHit(Vector2 const position)
{
}

PlayerStat bombPouch::equip()
{
	return PlayerStat();
}
