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
	_renderSize = source._renderSize;

	_useGravity = source._useGravity;
	_gravity = source._gravity;

	_useRotate = source._useRotate;
	_length = source._length;
}

void GuidedProjectile::init(const string imgKey, const string collisionEffect, const Vector2 & drawSize, const Vector2 & collsionRectSize, const Vector2 & effectSize, const Vector2 & force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate, bool useGravity, bool collsionGround, bool collsionPlatForm, bool collsionEnemy, bool afterimage)
{
	_img = IMAGE_MANAGER->findImage(imgKey);

	float elapseXY;

	_angleRadian = angleRadian;
	_force = force;

	_maxTime = maxTime;
	_count = 0;
	_countI = 0;

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

	if (_afterimage)
	{
		for (int i = 0; i < 10; i++)
		{
			_afterImg[i] = IMAGE_MANAGER->findImage(imgKey);
		}
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
	float guidedAngleRadian = atan2f(-(CAMERA->getAbsoluteY(_enemyPos.y) - _position.y), (CAMERA->getAbsoluteX(_enemyPos.x) - _position.x)) + PI2;
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

	if (_afterimage)
	{
		_mirageCount += elapsedTime;

		/*while (_active)
		{
			_afterImg.push_back(IMAGE_MANAGER->findImage(_img->getKey()));
		}*/
	
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
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_position), _renderSize);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}

	if (_afterimage)
	{
		int index = _ani->getPlayIndex();
		Vector2 _pos;
		Vector2 _pos2 = _pos;
		Vector2 _pos3 = _pos;
		Vector2 _pos4 = _pos;
		Vector2 _pos5 = _pos;
		_pos = Vector2(_position.x - 5, _position.y - 5);

		if (_mirageCount / 0.2f == 0)
		{
			_pos = Vector2(_position.x - 20, _position.y - 20);
		}

		if (_mirageCount > 0.3f && _mirageCount < 3.5f)
		{
			//_mirageCount = 0;

			_pos2.x = _pos.x - 5;
			_pos2.y = _pos.y + 5;

			_pos3.x = _pos2.x - 5;
			_pos3.y = _pos2.y + 5;
			_pos4.x = _pos3.x - 5;
			_pos4.y = _pos3.y + 5;
			_pos5.x = _pos4.x - 5;
			_pos5.y = _pos4.y + 5;

			_afterImg[0]->frameRender(CAMERA->getRelativeV2(_pos), _renderSize, index, 0);

		}
		//_afterImg[1]->frameRender(_pos2, _renderSize, index, 0);
		//_afterImg[2]->frameRender(_pos3, _renderSize, index, 0);
		//_afterImg[3]->frameRender(_pos4, _renderSize, index, 0);
		//_afterImg[4]->frameRender(_pos5, _renderSize, index, 0);

		/*if (_count < 1)
		{
			_afterImg[0]->setAlpha(_afterImg[0]->getAlpha() - _count);
		}*/
	}
	
	/*if (_afterimage)
	{
		if (_afterCount%2 == 0)
		{
			_afterImg[_countI]->render(CAMERA->getRelativeV2(_position), _renderSize);
		}
	}*/
	//D2D_RENDERER->renderText(CAMERA->getRelativeX(_position.x), CAMERA->getRelativeY(_position.y - 10), to_wstring(_angleRadian), 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.f);
}

void GuidedProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}
