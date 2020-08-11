#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelBigIce.h"

void SkelBigIce::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 3;
	_detectRange = 100;

	_size = Vector2(_img->getFrameSize().x - 15, _img->getFrameSize().y);
	_size = _size * _scale;

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.speed = 200;
	_moving.delay = 0.2;

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 1;
	
	ZeroMemory(&_skill, sizeof(_skill));
	_skill.delay = 3;

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
			if (_moving.update(timeElapsed))
			{
				_direction = _enemyManager->getPlayerPos().x > _position.x ? DIRECTION::RIGHT : DIRECTION::LEFT;
			}

			moveDir.x += timeElapsed * _moving.speed * ((bool)(_direction) ? 1 : -1);

			if (_attack.update(timeElapsed))
			{
				setState(ENEMY_STATE::ATTACK);
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


	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void SkelBigIce::render()
{
	D2D_RENDERER->drawRectangle(_rect);
	D2D_RENDERER->drawEllipse(_position, _detectRange);
	_img->setScale(_scale);
	/*Vector2 drawPosition = _position;
	switch (_state)
	{
	case :
		drawPosition.x += 10;
		break;
	}

	_img->aniRender(drawPosition, _ani, !(unsigned)_direction);*/
	_img->aniRender(_position, _ani, !(unsigned)_direction);
}

void SkelBigIce::setState(ENEMY_STATE state)
{
	_state = state;

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
			_ani->setFPS(1);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::DIE:
		{
			break;
		}
	}
}
