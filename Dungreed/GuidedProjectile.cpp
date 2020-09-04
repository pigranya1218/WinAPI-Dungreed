#include "GuidedProjectile.h"
#include "ProjectileManager.h"

GuidedProjectile::GuidedProjectile(const GuidedProjectile & source)
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

	_useGravity = source._useGravity;
	_gravity = source._gravity;

	_useRotate = source._useRotate;
	_length = source._length;
	_afterimage = source._afterimage;
}

void GuidedProjectile::init(const string imgKey, const string collisionEffect, const Vector2 & drawSize, const Vector2 & collsionRectSize, const Vector2 & effectSize, const Vector2 & force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate, bool useGravity, bool collsionGround, bool collsionPlatForm, bool collsionEnemy, bool afterimage)
{
	_img = IMAGE_MANAGER->findImage(imgKey);

	float elapseXY;

	_angleRadian = angleRadian;
	_force = force;

	_maxTime = maxTime;
	_count = 0;

	if (useAni)
	{
		elapseXY = fabsf(_img->getFrameSize().x - _img->getFrameSize().y);

		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(aniFps);
		_ani->setDefPlayFrame(false, isAniLoop);
		_ani->start();
	}

	_afterimage = afterimage;
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

	_timeCount = 0;
	_afterCount = 0;
	_mirageCount = 1;
	_frameIndex = 0;

	if (_afterimage)
	{
		_alphaValue = 1.0f;
		_alphaCount = 0;
	}
}

void GuidedProjectile::release()
{
	Projectile::release();

	if (_useAni)
	{
		_ani->release();
		SAFE_DELETE(_ani);
	}
}

void GuidedProjectile::update(float elapsedTime)
{
	_enemyPos = _projectileMgr->getEnemyPos(_position);

	Vector2 moveDir(0, 0);

	// 중력 적용
	if (_useGravity)
	{
		_force.y += _gravity.y * elapsedTime * ((_angleRadian > PI) ? (1) : (-1));
	}

	// 투사체부터 에너미까지의 각도
	float guidedAngleRadian = atan2f(-(_enemyPos.y - _position.y), (_enemyPos.x) - _position.x) + PI2;
	if (guidedAngleRadian > PI2)
	{
		guidedAngleRadian -= PI2;
	}

	_timeCount += elapsedTime;

	if (_timeCount <= 0.3f)
	{
		moveDir.x += cosf(_angleRadian) * _force.x * elapsedTime;
		moveDir.y -= sinf(_angleRadian) * _force.y * elapsedTime;
	}

	if (_timeCount > 0.3f)
	{
		if (_angleRadian <= guidedAngleRadian)
		{
			if ((guidedAngleRadian - _angleRadian) > (_angleRadian + (PI2 - guidedAngleRadian)))
			{
				if (_angleRadian < 0.f)
				{
					_angleRadian = PI2;
				}
				_angleRadian -= 3.f * elapsedTime;
			}
			else
			{
				_angleRadian += 3.f * elapsedTime;
			}
		}
		else
		{
			if ((_angleRadian - guidedAngleRadian) < ((PI2 - _angleRadian) + guidedAngleRadian))
			{
				_angleRadian -= 3.f * elapsedTime;
			}
			else
			{
				if (_angleRadian >= PI2)
				{
					_angleRadian = 0;
				}
				_angleRadian += 3.f * elapsedTime;
			}
		}

		// 이동
		moveDir.x += cosf(_angleRadian) * _force.x * elapsedTime;
		moveDir.y -= sinf(_angleRadian) * _force.y * elapsedTime;
	}

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
			_collisionCount += elapsedTime;
			if (_collisionCount >= 0.2f)
			{
				_collisionCount = 0;
				_info->attackID = TTYONE_UTIL::getHash(to_string(0x09999) + to_string(TIME_MANAGER->getWorldTime()));
			}
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

	// 지속시간을 넘어가면
	_count += elapsedTime;
	if (_count >= _maxTime)
	{
		float angleDegree = _angleRadian * (180.0f / PI);
		EFFECT_MANAGER->play(_collisionEffect, effectPos, _effectSize, ((_useRotate) ? (angleDegree) : (0.0f)));

		_active = false;
	}

	// 애니메이션 사용 시 프레임 재생
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}

	// 잔상 사용시
	if (_afterimage)
	{
		_alphaCount += elapsedTime;
		_shodow.img = IMAGE_MANAGER->findImage(_img->getLoadInfo().key);

		_alphaValue =-_alphaCount;

		_mirageCount += elapsedTime;
		if (_mirageCount > 0.15)
		{
			_alphaCount = 0;
			_mirageCount -= 0.15;
			generateAfterImage(elapsedTime);
			if (_useAni)
			{
				_shodow.frameX = _frameIndex;
				
			}
		}
		for (int i = 0; i < _vShadow.size();)
		{
			if (_vShadow[i].remainTime <= 0)
			{
				_vShadow.erase(_vShadow.begin() + i);
			}
			else
			{
				_vShadow[i].remainTime = max(0, _vShadow[i].remainTime - elapsedTime);
				i++;
			}
		}
	}
}

void GuidedProjectile::render()
{
	if (_useRotate)
	{
		_img->setAngle(_angleRadian * (180 / PI));
	}
	if (_useAni)
	{
		_img->aniRender(CAMERA->getRelativeV2(_position), _renderSize, _ani);
		//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_position), _renderSize);
		//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}

	if (_afterimage)
	{
		for (int i = 0; i < _vShadow.size(); i++)
		{
			//_shodow.img->setScale(4);
			_shodow.img->setAlpha(_vShadow[i].remainTime / 0.5);

			if (_useAni)
			{
				_shodow.img->frameRender(CAMERA->getRelativeV2(_vShadow[i].pos), _renderSize, 0, 0);
			}
			if (!_useAni)
			{
				_shodow.img->render(CAMERA->getRelativeV2(_vShadow[i].pos), _renderSize);
			}
		}
	}
}

void GuidedProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}

void GuidedProjectile::generateAfterImage(float elapsedTime)
{
	float distance = 2.0f;
	tagShadow shadow;

	shadow.angleRadian = PI - _angleRadian;
	shadow.pos.x = _position.x + cosf(shadow.angleRadian) * distance;
	shadow.pos.y = _position.y + -sinf(shadow.angleRadian) * distance;
	shadow.remainTime = 0.5;
	
	_frameIndex++;
	if (_frameIndex > 3)
	{
		_frameIndex = 0;
	}
	_vShadow.push_back(shadow);
}
