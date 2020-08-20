#include "stdafx.h"
#include "GoldObject.h"
#include "ObjectManager.h"
#include "Player.h"

void GoldObject::getGoldImage()
{
	if (_value < 100)
	{
		_img = IMAGE_MANAGER->findImage("OBJECT/GOLD/COIN");
	}
	else
	{
		_img = IMAGE_MANAGER->findImage("OBJECT/GOLD/BULLION");
	}
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(20);
	_ani->setDefPlayFrame(false, true);
	_ani->start();
}

void GoldObject::init(float value, Vector2 pos, float power, float radian)
{
	_objectCode = 0x0020;
	_value = value;
	_position = pos;
	_size = Vector2(20, 20);
	_power = power;
	_radian = radian;
	_force = Vector2(0, 0);
	_player = _objectMgr->getPlayer();
	_active = true;
	getGoldImage();
}

void GoldObject::release()
{
	_ani->release();
	delete _ani;
}

void GoldObject::update(float elapsedTime)
{
	Vector2 moveDir(0, 0);
	_force.y += 80 * elapsedTime;
	moveDir.x += cosf(_radian) * _power * elapsedTime;
	moveDir.y += -sinf(_radian) * _power * elapsedTime + _force.y;
	_objectMgr->moveTo(this, moveDir);
	if (_isStand)
	{
		_force.y = 0;
		_power = 0;
	}
	_ani->frameUpdate(elapsedTime);

	// 플레이어와 충돌 처리
	FloatRect playerRc = FloatRect(_player->getPosition(), _player->getSize(), PIVOT::CENTER);
	FloatRect goldRc = FloatRect(_position, _size, PIVOT::CENTER);
	if (FloatRect::intersect(playerRc, goldRc))
	{
		_active = false;
		_player->setGold(_player->getGold() + _value);
	}
}

void GoldObject::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani);
}
