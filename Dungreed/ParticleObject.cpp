#include "stdafx.h"
#include "ParticleObject.h"
#include "ObjectManager.h"

void ParticleObject::init(Image* img, Vector2 pos, float power, float radian)
{
	_objectCode = 0x0010;
	_img = img;
	_position = pos;
	_size = Vector2(10, 10);
	_power = power;
	_radian = radian;
	_degree = 0;
	
	_active = true;
}

void ParticleObject::update(float elapsedTime)
{
	Vector2 moveDir(0, 0);
	_force.y += 80 * elapsedTime;
	moveDir.x += cosf(_radian) * _power * elapsedTime;
	moveDir.y += -sinf(_radian) * _power * elapsedTime + _force.y;
	if (moveDir.x > 0)
	{
		_degree -= elapsedTime * _power;
	}
	else
	{
		_degree += elapsedTime * _power;
	}
	
	_objectMgr->moveTo(this, moveDir);
	if (_isStand)
	{
		_force.y = 0;
		_power = 0;
	}
}

void ParticleObject::render()
{
	_img->setScale(4);
	_img->setAngle(_degree);
	_img->render(CAMERA->getRelativeV2(_position));
}
