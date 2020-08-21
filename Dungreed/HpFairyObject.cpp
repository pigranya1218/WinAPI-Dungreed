#include "stdafx.h"
#include "HpFairyObject.h"
#include "ObjectManager.h"
#include "Player.h"

void HpFairyObject::getFairyImage()
{
	_img = IMAGE_MANAGER->findImage("OBJECT/HP_FAIRY/MID");

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(20);
	_ani->setDefPlayFrame(false, true);
	_ani->start();
}

void HpFairyObject::init(float value, Vector2 pos)
{
	_value = value;
	_position = pos;
	_size = Vector2(30, 30);
	_player = _objectMgr->getPlayer();
	_active = true;
	getFairyImage();
}

void HpFairyObject::release()
{
	_ani->release();
	delete _ani;
}

void HpFairyObject::update(float elapsedTime)
{
	_ani->frameUpdate(elapsedTime);

	// 플레이어와 충돌 처리
	FloatRect playerRc = FloatRect(_player->getPosition(), _player->getSize(), PIVOT::CENTER);
	FloatRect goldRc = FloatRect(_position, _size, PIVOT::CENTER);
	if (FloatRect::intersect(playerRc, goldRc))
	{
		_active = false;
		_player->setCurrHp(_player->getCurrHp() + _value);
	}
}

void HpFairyObject::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani);
}
