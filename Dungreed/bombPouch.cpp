#include "bombPouch.h"

void bombPouch::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::RARE;

	isBoom = false;

	_addStat.defense = 2;
	
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

void bombPouch::frontRender(Player* player)
{

}

void bombPouch::backRender(Player* player)
{
	renderPos = player->getPosition();
	D2D_RENDERER->drawRectangle(RC);
}

void bombPouch::displayInfo()
{
}

void bombPouch::attack(Player* player)
{
}

void bombPouch::attack(FloatRect * rect, AttackInfo * info)
{
}

void bombPouch::attack(FloatCircle * circle, AttackInfo * info)
{
}

void bombPouch::attack(Projectile * projectile, AttackInfo * info)
{
}

void bombPouch::getHit(Vector2 const position)
{
}

PlayerStat bombPouch::equip()
{
	return PlayerStat();
}
