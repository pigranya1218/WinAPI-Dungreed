#include "SeeriProjectile.h"
#include "ProjectileManager.h"
#include "Player.h"

void SeeriProjectile::init(const string imgKey, const string collisionEffect, const Vector2 & drawSize, const Vector2 & collsionRectSize, const Vector2 & effectSize, const Vector2 & force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate, bool useGravity, bool collsionGround, bool collsionPlatForm, bool collsionEnemy)
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
	_position.x = _position.x - 100;
	_useAni = useAni;
	_useRotate = useRotate;
	_useGravity = useGravity;

	_collsionGround = collsionGround;
	_collisionPlatForm = collsionPlatForm;
	_collisionEffect = collisionEffect;
	_useCollsionEnemy = collsionEnemy;

	_drawSize = drawSize;
	_size = collsionRectSize;
	_effectSize = effectSize;

	_gravity = Vector2(0, 4000);

	_active = true;
	_Delay = 0.2f;
	_length = _img->getFrameSize().x * 1.0f;

	_timeCount = 0;
	_isTrun = false;
	
	_angele = 0;
}

void SeeriProjectile::release()
{

	Projectile::release();

	if (_useAni)
	{
		_ani->release();
		SAFE_DELETE(_ani);
	}
}

void SeeriProjectile::update(float elapsedTime)
{
	Vector2 _effectpos = _position;

	EFFECT_MANAGER->play("SeeriBullet0", _effectpos, _drawSize, 0, _isTrun);
	if (_Delay > 0)
	{
		_Delay = max(0, _Delay - elapsedTime);
		_position.y -= 100* elapsedTime;
		
	}
	_enemyPos = _projectileMgr->getEnemyPos(_position);
	_timeCount += elapsedTime;	
	Vector2 moveDir(0, 0);
	
	if (_Delay == 0)
	{
		
		// 중력 적용
		if (_useGravity)
		{
			_force.y += _gravity.y * elapsedTime * ((_angleRadian > PI) ? (1) : (-1));
		}

		// 투사체부터 에너미까지의 각도
		float guidedAngleRadian = atan2f(-(_enemyPos.y - _position.y), (_enemyPos.x - _position.x)) + PI2;
		if (guidedAngleRadian > PI2)
		{
			guidedAngleRadian -= PI2;
		}

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
}

void SeeriProjectile::render()
{	
	if (_useRotate)
	{
		_img->setAngle(_angleRadian * (180 / PI));
	}
	if (_useAni)
	{
		_img->aniRender(CAMERA->getRelativeV2(_position), _drawSize, _ani, _isTrun);
		
		
	}
	else
	{
	
		_img->render(CAMERA->getRelativeV2(_position), _drawSize, _isTrun);
		
	}
}

void SeeriProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}
