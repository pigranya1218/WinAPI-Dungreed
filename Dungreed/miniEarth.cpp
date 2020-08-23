#include "miniEarth.h"
#include "stdafx.h"

void miniEarth::init()
{
	//악세서리 타입
	_itemCode = 0x0310A;
	_iconImg = IMAGE_MANAGER->findImage("MiniEarth");
	_img = IMAGE_MANAGER->findImage("MiniEarth0");

	//악세서리 옵션	
	_itemName = L"초소형 행성";	
	_displayText = L"\"엄청난 과학력을 지닌 행성. 하지만 3개의 위성을 잃어 과학력을 잃었다.\"";
	//악세서리 가격
	_price = 600;

	_angle = PI / 4;
	_x = _y = 0;
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();
}

void miniEarth::release()
{
}

void miniEarth::update(Player * player, float const elapsedTime)
{
	_angle += 1.523f*elapsedTime;
	_ani->frameUpdate(elapsedTime);
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(10);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
	_x = cosf(_angle) * 40;
	_y = -sinf(_angle) * 40;

	_renderPos = player->getPosition();
	_renderPos.x = _renderPos.x + _x;
	_renderPos.y = _renderPos.y + _y - 20;
}

void miniEarth::backRender(Player * player)
{
	

}

void miniEarth::frontRender(Player * player)
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_renderPos), _ani, false);
}


