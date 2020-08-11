#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelBigIce.h"

void SkelBigIce::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 5;
	_detectRange = 100;

	_size = Vector2(_img->getFrameSize().x - 15, _img->getFrameSize().y);
	_size = _size * _scale;

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.speed = 200;
	_moving.delay = 0.2;

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 1;
	_attack.distance = 100;
	
	ZeroMemory(&_skill, sizeof(_skill));
	_skill.delay = 2;
	_skill.distance = 500;

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	_isDetect = _moving.jumpPower = 0;
	_moving.gravity = 1600;
}

void SkelBigIce::release()
{
}

void SkelBigIce::update(float const timeElapsed)
{
	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	Vector2 moveDir(0, 0);
	// 상태에 따른 행동처리
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{			
			if (_isDetect)
			{
				setState(ENEMY_STATE::MOVE);
			}
			break;
		}		
		case ENEMY_STATE::MOVE:
		{
			const Vector2 playerPos = _enemyManager->getPlayerPos();

			if (_moving.update(timeElapsed))
			{
				_direction = playerPos.x > _position.x ? DIRECTION::RIGHT : DIRECTION::LEFT;
			}

			moveDir.x += timeElapsed * _moving.speed * ((bool)(_direction) ? 1 : -1);

			float distance = getDistance(playerPos.x, playerPos.y, _position.x, _position.y);
			if (distance < _attack.distance)
			{
				if (_attack.update(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
				}
			}
			if (distance > _attack.distance && distance < _skill.distance)
			{
				if (_skill.update(timeElapsed))
				{
					setState(ENEMY_STATE::SKILL);
				}
			}
			break;
		}
		case ENEMY_STATE::ATTACK:
		{
			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::MOVE);
			}
			break;
		}		
		case ENEMY_STATE::SKILL:
		{			
			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::MOVE);
			}
			break;
		}		
		case ENEMY_STATE::DIE:
		{
			break;
		}		
	}

	_moving.jumpPower += _moving.gravity * timeElapsed;
	moveDir.y = _moving.jumpPower * timeElapsed;
	

	// 이동할 포지션 최종
	_enemyManager->moveEnemy(this, moveDir);
	if (_isStand)
	{
		_moving.jumpPower = 0;
	}

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void SkelBigIce::render()
{
	D2D_RENDERER->drawRectangle(_rect);
	D2D_RENDERER->drawEllipse(_position, _detectRange);
	_img->setScale(_scale);

	if (_state == ENEMY_STATE::ATTACK)
	{
		// 이동 이미지 기준으로
		Image* img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Move");
		Vector2 drawPos = _position;

		// 이미지 간의 사이즈 차이 구하고
		Vector2 elapsePos((_img->getFrameSize().x - img->getFrameSize().x) * _scale, (_img->getFrameSize().y - img->getFrameSize().y) * _scale);

		// 최종 출력 포지션 설정
		drawPos.x += ((bool)_direction) ? +(elapsePos.x / 2) : -(elapsePos.x / 2);		
		drawPos.y -= elapsePos.y / 2;

		_img->aniRender(drawPos, _ani, !(unsigned)_direction);
	}
	else if (_state == ENEMY_STATE::SKILL)
	{
		Image* img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Move");
		Vector2 drawPos = _position;

		float elapseY = (_img->getFrameSize().y - img->getFrameSize().y) * _scale;

		drawPos.y -= elapseY / 2;

		_img->aniRender(drawPos, _ani, !(unsigned)_direction);
	}
	else
	{
		_img->aniRender(_position, _ani, !(unsigned)_direction);
	}	
}

void SkelBigIce::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(10);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::SKILL:
		{
			_img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Skill");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(10);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::DIE:
		{
			break;
		}
	}
}
