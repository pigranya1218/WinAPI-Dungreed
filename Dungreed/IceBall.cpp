#include "IceBall.h"
#include "stdafx.h"

void IceBall::init()
{
	//악세서리 타입
	_itemCode = 0x03108;
	_iconImg = IMAGE_MANAGER->findImage("IceBall");
	_itemName = L"얼음 덩어리";
	_displayInfos.push_back(L"모험가 주위를 돌며 적을 공격한다");
	_displayText = L"\"싸늘함이 주변을 맴돈다";
	//악세서리 옵션
	_addStat.criticalChance = 1;
	_addStat.defense = 1;
	
	//악세서리 가격
	_price = 600;

	_radius = 0;
	_fspeed = 0;
	_x = _y = 0;
	_img = IMAGE_MANAGER->findImage("IceBall");
	_ani = new Animation;
	_ani->start();
	_setitem = false;
}

void IceBall::release()
{
}

void IceBall::update(Player * player, float const elapsedTime)
{
	if (KEY_MANAGER->isOnceKeyDown('6'))
	{
		_setitem = false;

	}
	if (KEY_MANAGER->isOnceKeyDown('7'))
	{
		_setitem = true;

	}

	if (!_setitem)
	{
		_radius = 65;
		_img = IMAGE_MANAGER->findImage("IceBall");
		_angle -= 1.843f*elapsedTime;
		_fspeed = 5;
	}
	else
	{
		_radius = 85;
		_img = IMAGE_MANAGER->findImage("IceBall0");
		_angle -= 2.562f*elapsedTime;
		_fspeed = 10;
		_ani->frameUpdate(elapsedTime);
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(_fspeed);
		_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
	}

	

	
}

void IceBall::backRender(Player * player)
{
	

	_x = cosf(_angle) * _radius;
	_y = -sinf(_angle) * _radius;

	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + _x ;
	renderPos.y = renderPos.y + _y ;
	_img->setScale(4);
	if (!_setitem)
	{
		_img->render(CAMERA->getRelativeV2(renderPos), false);
		Vector2 size = Vector2(_img->getFrameSize().x * 4, _img->getFrameSize().y * 4);
		_crash = rectMakePivot(Vector2(renderPos.x, renderPos.y ), size, PIVOT::CENTER);
	}
	else
	{
		_img->aniRender(CAMERA->getRelativeV2(renderPos), _ani, false);
		Vector2 size = Vector2(_img->getFrameSize().x * 2, _img->getFrameSize().y * 2);
		_crash = rectMakePivot(Vector2(renderPos.x-1, renderPos.y + 19), size, PIVOT::CENTER);
	}
	
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_crash));
	

	

}

void IceBall::frontRender(Player * player)
{
}


