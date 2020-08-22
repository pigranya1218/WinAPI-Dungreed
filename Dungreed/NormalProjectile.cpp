#include "stdafx.h"
#include "NormalProjectile.h"
#include "ProjectileManager.h"

NormalProjectile::NormalProjectile(const NormalProjectile & source)
{
	_position = source._position;
	_size = source._size;
	_active = source._active;
	_team = source._team;

	_info = nullptr;
	_projectileMgr = nullptr;
	_renderSize = source._renderSize;
	_force = source._force;
	_angleRadian = source._angleRadian;
	_useCollsionEnemy = source._useCollsionEnemy;
	
	_maxTime = source._maxTime;
	_count = source._count;

	_img = source._img;
	_effectImg = source._effectImg;
	_effectSize = source._effectSize;

	_useAni = source._useAni;
	if (source._ani != nullptr)
	{
		_ani = new Animation(*(source._ani));
	}
	if (source._ani == nullptr && _useAni)
	{
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	}

	_collsionGround = source._collsionGround;
	_collisionPlatForm = source._collisionPlatForm;

	_collisionEffect = source._collisionEffect;
	_renderSize = source._renderSize;

	_useGravity = source._useGravity;
	_gravity = source._gravity;
	
	_useRotate = source._useRotate;
	_length = source._length;
}

void NormalProjectile::init(const string imgKey, const string collisionEffect, const Vector2& drawSize, const Vector2& collsionRectSize, const Vector2& effectSize, const Vector2& force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate, bool useGravity, bool collsionGround, bool collsionPlatForm, bool collsionEnemy)
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
	_useCollsionEnemy = collsionEnemy;

	_renderSize = drawSize;
	_size = collsionRectSize;
	_effectSize = effectSize;

	_gravity = Vector2(0, 4000);

	_active = true;

	_length = _img->getFrameSize().x * 1.0f;
}

void NormalProjectile::release()
{
	Projectile::release();

	if (_useAni)
	{
		_ani->release();
		SAFE_DELETE(_ani);
	}
	/*float angleDegree = _angleRadian * (180.0f / PI);
	EFFECT_MANAGER->play(_collisionEffect, _position, _effectSize, ((_useRotate) ? (angleDegree) : (0.0f)));*/
}

void NormalProjectile::update(float elapsedTime)
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

	Vector2 effectPos = _position;
	effectPos.x += cosf(_angleRadian) * _length;
	effectPos.y += -sinf(_angleRadian) * _length;

	if (lastDir + moveDir != currDir)
	{
		float angleDegree = _angleRadian * (180.0f / PI);
		EFFECT_MANAGER->play(_collisionEffect, effectPos, _effectSize, ((_useRotate) ? (angleDegree) : (0.0f)));
		_active = false;
		return;
	}

	// 타입에 따른 충돌 검사
	if (_info->team == OBJECT_TEAM::PLAYER)
	{
		// ENEMY와의 충돌 검사
		if (_projectileMgr->checkEnemyCollision(this, _useCollsionEnemy)) // 적과 충돌했다면
		{
			float angleDegree = _angleRadian * (180.0f / PI);
			EFFECT_MANAGER->play(_collisionEffect, effectPos, _effectSize, ((_useRotate) ? (angleDegree) : (0.0f)));
			
			if (_useCollsionEnemy)
			{
				_active = false;
			}
			return;
		}
	}
	else
	{
		// TODO: PLAYER와의 충돌 검사
		if (_projectileMgr->checkPlayerCollision(this, true))
		{
			float angleDegree = _angleRadian * (180.0f / PI);
			EFFECT_MANAGER->play(_collisionEffect, effectPos, _effectSize, ((_useRotate) ? (angleDegree) : (0.0f)));

			_active = false;
			return;
		}

	}	

	// 지속시간을 넘어가면
	_count += elapsedTime;
	if (_count >= _maxTime)
	{
		if (_info->team == OBJECT_TEAM::ENEMY)
		{
			float angleDegree = _angleRadian * (180.0f / PI);
			EFFECT_MANAGER->play(_collisionEffect, effectPos, _effectSize, ((_useRotate) ? (angleDegree) : (0.0f)));
		}

		_active = false;
	}

	// 애니메이션 사용 시 프레임 재생
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
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
		_img->aniRender(CAMERA->getRelativeV2(_position), _renderSize, _ani);		
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_position), _renderSize);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
		//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, resize, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}
}

void NormalProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}

