#include "stdafx.h"
#include "EnemyManager.h"
#include "Ghost.h"

void Ghost::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;
	setState(ENEMY_STATE::IDLE);

	ZeroMemory(&_attacking, sizeof(_attacking));
	_attacking.delay = 2;

	ZeroMemory(&_moving, sizeof(_moving));
	//움직이는 각도
	_moving.angle = RANDOM->getFromFloatTo(0, PI2);
	//나아가는 방향(이동속도)     랜덤으로 -> 0~ 360 까지의 값을 float 값으로 가져온다
	_moving.speed = 50;
	_moving.delay = 1.5;

	_scale = 4;
	_position = pos;
	_direction = direction;
	_detectRange = 2000;



	_size = _img->getFrameSize()*_scale;
	_rect = rectMakePivot(_position,_size,PIVOT::CENTER);
	_isDetect = false;
}

void Ghost::release()
{
}

void Ghost::update(float const timeElapsed)
{
	// 플레이어 포지션 항상 가져옴
	const Vector2 playerPos = _enemyManager->getPlayerPos();
	Vector2 moveDir(0, 0);

	// 플레이어 포지션과 비교하여 좌우 설정



	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{

			// 플레이어 감지를 했으면
			if (_isDetect)
			{
				// 계속 움직임
				setState(ENEMY_STATE::MOVE);
				_moving.angle = RANDOM->getFromFloatTo(0, PI2);
			}
		}
			break;
		case ENEMY_STATE::MOVE:
		{
			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.speed);
			moveDir.y -= sinf(_moving.angle)* (timeElapsed * _moving.speed);
			setPosition(_position + moveDir);

			_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

			if (_attacking.update(timeElapsed))
			{
				_moving.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
				_moving.speed = 350;
				setState(ENEMY_STATE::ATTACK);
			}
		}
			break;
		case ENEMY_STATE::ATTACK:
		{
			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.speed);
			moveDir.y -= sinf(_moving.angle)* (timeElapsed * _moving.speed);

			setPosition(_position + moveDir);
			//_enemyManager->moveEnemy(this, moveDir);
			if (_moving.update(timeElapsed))
			{
				_moving.speed = 120;
				_moving.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
				//_moving.angle = RANDOM->getFromFloatTo(0, PI2);
				setState(ENEMY_STATE::MOVE);
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

void Ghost::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position),_ani,!(unsigned)_direction);
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);
}

// 이미지 및 프레임 설정
void Ghost::setState(ENEMY_STATE state)
{
	_state = state;

	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();

			_img = IMAGE_MANAGER->findImage("Ghost/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();

		}
		break;

		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();

			_img = IMAGE_MANAGER->findImage("Ghost/Attack");
			
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();

		}

		break;
		case ENEMY_STATE::DIE:
		{
		}
			break;
	}
}
