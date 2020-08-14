#include "stdafx.h"
#include "EnemyManager.h"
#include "BatRed.h"

void BatRed::init(const Vector2& pos, DIRECTION direction)
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
	

	// 이동 관련 변수 초기화
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 3;
	_moving.speed = 250;
	_moving.angle = RANDOM->getFromFloatTo(0, PI2);

	// 총알 초기화
	_shooting.init("SmallBullet", "SmallBullet_FX", _scale, 3, 500, 1000, false, false, true, true);

	_isDetect = 0;
}

void BatRed::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatRed::update(float const timeElapsed)
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
		// 플레이어 좌표따라 방향 설정
		_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
	}

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
			Vector2 moveDir(0, 0);

			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.speed);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.speed);

			_enemyManager->moveEnemy(this, moveDir);

			// 일정 주기로 공격
			if (_isDetect)
			{
				if (_shooting.delayUpdate(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
					_shooting.bulletNum = 1;
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
			// 공격 모션일 때 투사체 생성 및 발사
			if (_ani->getPlayIndex() == 5 && _shooting.bulletNum > 0)
			{
				float angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
				_shooting.createBullet(_position, angle);
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

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void BatRed::render()
{
	_img->setScale(_scale);

	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, !(unsigned)_direction);
}

void BatRed::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Red/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}		
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Red/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::DIE:
		{
		}
		break;
	}
}
