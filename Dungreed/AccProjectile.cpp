#include "AccProjectile.h"
#include "ProjectileManager.h"
#include "stdafx.h"

void AccProjectile::init(string imgKey, Vector2 pos, float speed, bool useAni, bool isAniLoop, int aniFps, bool isCollision, string collisionEffect, Vector2 effectSize, float maxTime, bool useRotate, bool collsionGround, bool collsionPlatForm, bool useGravity)
{
	_pos = pos;
	_speed = speed;
	_maxTime = maxTime;
	_useGravity = useGravity;
	_count = 0;



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

	_checkCollision = isCollision;
	_collisionEffect = collisionEffect;
	_collisionPlatForm = collsionPlatForm;
	_effectSize = effectSize;
	_collsionGround = collsionGround;
	_useRotate = useRotate;
	_gravity = Vector2(0, 4000);
	_active = true;
}

void AccProjectile::release()
{
	Projectile::release();
	if (_useAni)
	{
		_ani->release();
		delete _ani;
	}

	EFFECT_MANAGER->play(_collisionEffect, _position, _effectSize, ((_useRotate) ? ( (PI)) : (0.0f)));
}

void AccProjectile::update(float elapsedTime)
{
	Vector2 moveDir = Vector2(0, 0);
	//moveDir.x += _speed * elapsedTime;
	moveDir.y += _speed * elapsedTime;

	// 중력 적용
	if (_useGravity)
	{
		moveDir.y += _gravity.y *_speed* elapsedTime ;
	}

	
	Vector2 lastDir = _position;
	_projectileMgr->moveTo(this, moveDir, _collsionGround, _collisionPlatForm);
	Vector2 currDir = _position;

	if (lastDir + moveDir != currDir)
	{
		_active = false;
	}	
	else // 스테이지와 충돌 검사 안함
	{
		_position += moveDir;
	}

	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}


	
		if (_info->team == OBJECT_TEAM::PLAYER)
		{
			// ENEMY와의 충돌 검사
			if (_projectileMgr->checkEnemyCollision(this, true)) // 적과 충돌했다면
			{
				return;
			}
		}
	

	
	// 지속시간을 넘어가면
	_count += elapsedTime;
	if (_count >= _maxTime ||! _ani->isPlay())
	{
		_active = false;
	}	
	
}

void AccProjectile::render()
{
	if (_useRotate)
	{
		_img->setAngle(-PI*30);
	}
	if (_useAni)
	{
		_img->aniRender(CAMERA->getRelativeV2(_position), _size, _ani);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_position), _size);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);

	}


}

void AccProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}
