#include "stdafx.h"
#include "BoomerangProjectile.h"
#include "ProjectileManager.h"
#include "Player.h"

void BoomerangProjectile::init(string imgKey, float angleRadian, float speed, bool useAni, bool isAniLoop, int aniFps, bool checkCollision, string collisionEffect, Vector2 effectSize, float maxTime, bool useRotate)
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

	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}

	// 타입에 따른 충돌 검사
	if (_info->team == OBJECT_TEAM::PLAYER)
	{
		// ENEMY와의 충돌 검사
		if (_projectileMgr->checkEnemyCollision(this, true)) // 적과 충돌했다면
		{
			//_active = false;
			return;
		}
	}
	else
	{
		// TODO: PLAYER와의 충돌 검사
	}

	_count += elapsedTime;
	if (_count >= _maxTime)
	{
		_count = 0;
		_info->attackID = TTYONE_UTIL::getHash(to_string(0x02262) + to_string(TIME_MANAGER->getWorldTime()));
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
		D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _radius, D2D1::ColorF::Enum::Red, 5);
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_position), _size);
	}
}

void BoomerangProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}
