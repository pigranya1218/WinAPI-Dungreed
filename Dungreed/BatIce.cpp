#include "stdafx.h"
#include "EnemyManager.h"
#include "BatIce.h"

void BatIce::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::MOVE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	// 사이즈 설정
	_size = Vector2(_img->getFrameSize().x - 20, _img->getFrameSize().y - 10);
	_size = _size * _scale;

	// 충돌 렉트 설정
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	// 공격 관련 변수 초기화
	//ZeroMemory(&_shooting, sizeof(_shooting));
	_shooting.init("IceBullet", "IceBullet_FX", _scale, 2, 1, 700, true, true, false, false);

	// 이동 관련 변수 초기화
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 3;
	_moving.force = Vector2(250, 0);
	_moving.angle = RANDOM->getFromFloatTo(0, PI2);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.hitDelay = 0.3;

	_isDetect = 0;

	_active = true;
}

void BatIce::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatIce::update(float const timeElapsed)
{
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	// 감지를 안했다면
	if (!_isDetect)
	{
		// 플레이어 계속 확인
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}
	else
	{
		// 플레이어 좌표따라 방햘 설정
		_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
	}

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			// 일정 주기로 이동
			if (_moving.update(timeElapsed))
			{
				// 방향은 랜덤
				_moving.angle = RANDOM->getFromFloatTo(0, PI2);
				setState(ENEMY_STATE::MOVE);
			}
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			// 이동
			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.force.x);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.force.x);			

			// 일정 주기로 공격
			if (_isDetect)
			{
				if (_shooting.delayUpdate(timeElapsed))
				{
					float angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
					for (int i = -1; i < 2; i++)
					{
						_shooting.createBullet(_position, angle + ((PI / 4) * i));
					}
					setState(ENEMY_STATE::ATTACK);
				}
			}
			else
			{
				if (_moving.update(timeElapsed))
				{
					// 아이들 상태로 변경
					setState(ENEMY_STATE::IDLE);
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			if (_ani->getPlayIndex() == 5)
			{
				_shooting.fireBullet(_enemyManager);
			}
			if (!_ani->isPlay())
			{
				// 공격 완료 후 IDLE 상태로 변경
				setState(ENEMY_STATE::IDLE);
			}
		}
		break;
		case ENEMY_STATE::DIE:
		{
		}
		break;
	}
	hitReaction(playerPos, moveDir, timeElapsed);

	_enemyManager->moveEnemy(this, moveDir);

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void BatIce::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));
}

void BatIce::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Ice/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Ice/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::DIE:
		{
			_active = false;
		}
		break;
	}
}

void BatIce::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.hitUpdate(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				case ENEMY_STATE::MOVE:
				{
					_img = IMAGE_MANAGER->findImage("Bat/Ice/Move");
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_img = IMAGE_MANAGER->findImage("Bat/Ice/Attack");
				}
				break;
			}
			_hit.isHit = false;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));

		return;
	}
	_moving.force.x = 250;
}

bool BatIce::hitEffect(FloatRect * rc, AttackInfo * info)
{
	return false;
}

bool BatIce::hitEffect(FloatCircle * circle, AttackInfo * info)
{
	_hit.isHit = true;
	_hit.hitCount = 0;
	//_hit.knockCount = 0;
	_moving.gravity.x = info->knockBack;

	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			_img = IMAGE_MANAGER->findImage("Bat/Ice/Move_Shot");
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_img = IMAGE_MANAGER->findImage("Bat/Ice/Attack_Shot");
		}
		break;
	}

	return false;
}

bool BatIce::hitEffect(Projectile * projectile, AttackInfo * info)
{
	return false;
}
