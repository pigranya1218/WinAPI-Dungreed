#include "bombPouch.h"

void bombPouch::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::RARE;
	_iconImg = IMAGE_MANAGER->findImage("BombPouch");
	
	_addStat.defense = 2;
	
	_price = 1200;


	_isBoom = false;

}

void bombPouch::release()
{
}

void bombPouch::update(Player* player, float const elapsedTime)
{
	_renderPos;
	
	if (KEY_MANAGER->isOnceKeyDown('R') )
	{
		_x = _renderPos.x;
		_y = _renderPos.y;
		_isBoom = true;
	}
	if (_RC.bottom > WINSIZEY)
	{
		_isBoom = false;
	}
	if (_isBoom)
	{
		_RC = rectMakePivot(Vector2(_x, _y), Vector2(50, 50), PIVOT::CENTER);
		_y += 10;
	}
	else if (!_isBoom )
	{
		
		_RC = rectMakePivot(Vector2(_renderPos), Vector2(0, 0), PIVOT::CENTER);
	}
}

void bombPouch::frontRender(Player* player)
{

}

void bombPouch::backRender(Player* player)
{
	_renderPos = player->getPosition();
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_RC));
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

void bombPouch::equip(Player* player)
{
}
