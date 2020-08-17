#include "stdafx.h"
#include "EnemyManager.h"
#include "Ovibos.h"

#define RUSHSPEED 1200.0f

void Ovibos::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;
	_position = pos;
	_direction = direction;
	setState(ENEMY_STATE::IDLE);

	_detectRange = 50;

	_scale = 4;
	_size = _img->getFrameSize()*_scale;
	_rect = rectMakePivot(_position,_size,PIVOT::CENTER);

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(RUSHSPEED, 0.0f);
	_moving.gravity = Vector2(50, 4000);

}

void Ovibos::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Ovibos::update(float const timeElapsed)
{
	const Vector2 playerpos = _enemyManager->getPlayerPos();

	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{

		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			switch (_direction)
			{
				case DIRECTION::LEFT:
				{
					if (_position.x < playerpos.x)
					{
						if (_ani->getPlayIndex() == _img->getMaxFrameX() - 1)
						{
							if (_ani->isPlay()) _ani->pause();

							_moving.force.x -= _moving.gravity.x;
						}
					}
				}
				break;
				case DIRECTION::RIGHT:
				{
					if (_position.x > playerpos.x)
					{
						if (_ani->getPlayIndex() == _img->getMaxFrameX() - 1)
						{
							if (_ani->isPlay()) _ani->pause();

							_moving.force.x -= _moving.gravity.x;
						}
					}
				}
				break;
			}

			moveDir.x += timeElapsed * _moving.force.x * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

			if (_moving.force.x < 0)
			{
				_moving.force.x = 0;
				setState(ENEMY_STATE::IDLE);
			}
		}
		break;
	}

	if (_isStand && _moving.force.y == 0)
	{
		_position.y -= 15;
		moveDir.y += 25;
	}
	_moving.force.y += _moving.gravity.y * timeElapsed;
	moveDir.y += _moving.force.y * timeElapsed;

	_enemyManager->moveEnemy(this, moveDir);

	if (_isStand)
	{
		_moving.force.y = 0;
	}

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void Ovibos::render()
{
	_img->setScale(_scale);
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));

	_img->aniRender(CAMERA->getRelativeV2(_position),_ani, (_direction == DIRECTION::LEFT));
}

void Ovibos::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Ovibos/Idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Ovibos/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
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

bool Ovibos::playerCollision(const Vector2 & playerPos)
{
	if (_rect.left <= playerPos.x && playerPos.x <= _rect.right)
	{
		return true;
	}

	return false;
}
