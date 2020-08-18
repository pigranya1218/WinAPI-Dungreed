#include "stdafx.h"
#include "BoomerangProjectile.h"
#include "ProjectileManager.h"
#include "Player.h"

void BoomerangProjectile::init(string imgKey, float angleRadian, float speed, bool useAni, bool isAniLoop, int aniFps, string collisionEffect, Vector2 effectSize, float maxTime, bool useRotate)
{
	_angleRadian = angleRadian;
	_speed = speed;
	_maxTime = maxTime;
	_count = 0;
	_returnCount = 0;

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

	_collisionEffect = collisionEffect;
	_effectSize = effectSize;

	_useRotate = useRotate;

	_ProjectileReturn = false;
	_active = true;
	_radius = _img->getFrameSize().x * 1.75;
}

void BoomerangProjectile::release()
{
	if (_useAni)
	{
		_ani->release();
		delete _ani;
	}

	EFFECT_MANAGER->play(_collisionEffect, _position, _effectSize, ((_useRotate) ? (_angleRadian) : (0.0f)));
}

void BoomerangProjectile::update(float elapsedTime)
{
	Vector2 moveDir = Vector2(0, 0);

	//if (_checkCollision) // 스테이지와 충돌 검사함
	//{
	//	Vector2 lastDir = _position;
	//	_projectileMgr->moveTo(this, moveDir);
	//	Vector2 currDir = _position;

	//	if (lastDir.x == currDir.x || lastDir.y == currDir.y)
	//	{
	//		_active = false;
	//	}
	//}
	//else // 스테이지와 충돌 검사 안함
	//{
	//	_position += moveDir;
	//}

	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}

	//Vector2 returnPos;
	/*if (getDistance(_startPos.x, _startPos.y, _position.x, _position.y) > _range)
	{
		_ProjectileReturn = true;
		if (getDistance(_startPos.x, _startPos.y, _position.x, _position.y) > _range)
		{
			returnPos = _position;
		}
	}*/

	_count += elapsedTime;
	if (_count >= _maxTime)
	{
		_count = 0;
		_ProjectileReturn = true;
	}

	if (!_ProjectileReturn)
	{
		moveDir.x += cosf(_angleRadian) * _speed * elapsedTime;
		moveDir.y += -sinf(_angleRadian) * _speed * elapsedTime;
	}

	// 사정거리를 넘어가면
	if (_ProjectileReturn)
	{
		_returnCount += elapsedTime;

		float angleValue;
		if ((_angleRadian + PI) > PI2)
		{
			angleValue = _angleRadian - PI;
		}
		else
		{
			angleValue = _angleRadian + PI;
		}
		moveDir.x += cosf(angleValue) * _speed * elapsedTime;
		moveDir.y += -sinf(angleValue) * _speed * elapsedTime;

		/*if (_returnCount >= _maxTime)
		{
			_returnCount = 0;
			_ProjectileReturn = false;
		}*/
	}
	_position += moveDir;
}

void BoomerangProjectile::render()
{
	if (_useRotate)
	{
		_img->setAngle(_angleRadian * (180 / PI));
	}
	if (_useAni)
	{
		_img->aniRender(CAMERA->getRelativeV2(_position), _size, _ani);
		//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
		D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _radius, D2D1::ColorF::Enum::Red, 5);
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_position), _size);
		//D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _img->getFrameSize().x * 2, D2D1::ColorF::Enum::Red, 5);
	}
}

void BoomerangProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}
