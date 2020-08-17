#include "stdafx.h"
#include "NormalProjectile.h"
#include "ProjectileManager.h"

void NormalProjectile::init(string imgKey, float angleRadian, float speed, bool useAni, bool isAniLoop, int aniFps, bool checkCollision, string collisionEffect, Vector2 effectSize, float range, bool useRotate)
{
	_angleRadian = angleRadian;
	_speed = speed;
	_range = range;

	_startPos = _position;

	_img = IMAGE_MANAGER->findImage(imgKey);
	_useAni = useAni;
	if (_useAni)
	{
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(aniFps);
		_ani->setDefPlayFrame(false, isAniLoop);
		_ani->start();
	}

	_checkCollision = checkCollision;
	_collisionEffect = collisionEffect;
	_effectSize = effectSize;

	_useRotate = useRotate;

	_active = true;
}

void NormalProjectile::release()
{
	if (_useAni)
	{
		_ani->release();
		delete _ani;
	}

	EFFECT_MANAGER->play(_collisionEffect, _position, _effectSize, ((_useRotate) ? (_angleRadian) : (0.0f)));
}

void NormalProjectile::update(float elapsedTime)
{
	Vector2 moveDir = Vector2(0, 0);
	moveDir.x += cosf(_angleRadian) * _speed * elapsedTime;
	moveDir.y += -sinf(_angleRadian) * _speed * elapsedTime;

	if (_checkCollision) // 스테이지와 충돌 검사함
	{
		Vector2 lastDir = _position;
		_projectileMgr->moveTo(this, moveDir);
		Vector2 currDir = _position;

		if (lastDir.x == currDir.x || lastDir.y == currDir.y)
		{
			_active = false;
		}
	}
	else // 스테이지와 충돌 검사 안함
	{
		_position += moveDir;
	}

	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}

	// 사정거리를 넘어가면
	if (getDistance(_startPos.x, _startPos.y, _position.x, _position.y) > _range)
	{
		_active = false;		
	}
}

void NormalProjectile::render()
{
	if (_useRotate)
	{
		_img->setAngle(_angleRadian * (180 / PI));
	}
	if (_useAni)
	{
		_img->aniRender(CAMERA->getRelativeV2(_position), _size, _ani);
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_position), _size);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}
}

void NormalProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}

