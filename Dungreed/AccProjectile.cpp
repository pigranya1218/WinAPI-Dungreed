#include "AccProjectile.h"
#include "ProjectileManager.h"
#include "stdafx.h"

void AccProjectile::init(const string imgKey, const string collisionEffect, const Vector2 & collisionSize, const Vector2 & drawSize, const Vector2 & force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate, bool useGravity, bool collsionGround, bool collsionPlatForm)
{
	float elapseXY;

	_angleRadian = angleRadian;
	_force = force;

	_maxTime = maxTime;
	_count = 0;

	_img = IMAGE_MANAGER->findImage(imgKey);
	if (useAni)
	{
		elapseXY = fabsf(_img->getFrameSize().x - _img->getFrameSize().y);

		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(aniFps);
		_ani->setDefPlayFrame(false, isAniLoop);
		_ani->start();
	}

	_useAni = useAni;
	_useRotate = useRotate;
	_useGravity = useGravity;

	_collsionGround = collsionGround;
	_collisionPlatForm = collsionPlatForm;

	_collisionEffect = collisionEffect;
	_drawSize = drawSize;
	_size = collisionSize;

	if (_collisionEffect != "")
	{
		_effectImg = IMAGE_MANAGER->findImage(_collisionEffect);
		_effectSize = Vector2(_effectImg->getFrameSize().x * 4, _effectImg->getFrameSize().y * 4);
	}

	_gravity = Vector2(0, 4000);

	_active = true;
}

void AccProjectile::release()
{
	
	Projectile::release();
	

	if (_useAni)
	{
		_ani->release();
		SAFE_DELETE(_ani);
	}

	EFFECT_MANAGER->play(_collisionEffect, _position, _effectSize, ((_useRotate) ? (_angleRadian) : (0.0f)));
}

void AccProjectile::update(float elapsedTime)
{
	Vector2 moveDir(0, 0);

	// 중력 적용
	if (_useGravity)
	{
		_force.y += _gravity.y * elapsedTime * ((_angleRadian > PI) ? (1) : (-1));
	}

	// 이동
	moveDir.x += cosf(_angleRadian) * _force.x * elapsedTime;
	moveDir.y -= sinf(_angleRadian) * _force.y * elapsedTime;

	Vector2 lastDir = _position;
	_projectileMgr->moveTo(this, moveDir, _collsionGround, _collisionPlatForm);
	Vector2 currDir = _position;

	if (lastDir + moveDir != currDir)
	{
		_active = false;
	}

	if (_ani->isPlay()) {
		// 타입에 따른 충돌 검사
		if (_info->team == OBJECT_TEAM::PLAYER)
		{
			// ENEMY와의 충돌 검사
			if (_projectileMgr->checkEnemyCollision(this, true)) // 적과 충돌했다면
			{
				_active = true;
				return;
			}
		}
		else
		{
			// TODO: PLAYER와의 충돌 검사
			if (_projectileMgr->checkPlayerCollision(this, true))
			{
				_active = false;
				return;
			}

		}
	}

	// 지속시간을 넘어가면
	_count += elapsedTime;
	if (_count >= _maxTime)
	{
		_active = false;
	}

	// 애니메이션 사용 시 프레임 재생
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}


	
}

void AccProjectile::render()
{

	if (_useRotate)
	{
		_img->setAngle(_angleRadian * (180 / PI));
	}
	if (_useAni)
	{
		if (_ani->isPlay()) {
			_img->aniRender(CAMERA->getRelativeV2(_position), _drawSize, _ani);
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
		}
	}
	else
	{
		if (_ani->isPlay()) {
			_img->render(CAMERA->getRelativeV2(_position), _drawSize);
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
			//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, resize, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
		}

	}
	
}

void AccProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}
