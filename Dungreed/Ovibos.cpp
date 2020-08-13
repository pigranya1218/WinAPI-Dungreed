#include "stdafx.h"
#include "EnemyManager.h"
#include "Ovibos.h"

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
	_moving.speed = 0;
	_moving.gravity = 4000;
	_moving.jumpPower = 3;


	_force = Vector2(0,0);

}

void Ovibos::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Ovibos::update(float const timeElapsed)
{
	const Vector2 playerpos = _enemyManager->getPlayerPos();
	Vector2 _moveDir(0,0);

	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}


	switch (_state)
	{
	case(ENEMY_STATE::IDLE):
	{
		_moveDir.x = (_moving.speed) * timeElapsed * (_direction == DIRECTION::RIGHT ? (1) : (-1));
		if (_moving.speed > 0)
		{
			_force.x = 50;
			_moving.speed -= _force.x;
		}
		else if (_moving.speed <= 0)
		{
			_force.x = 0;
			_moving.speed = 0;

			if (_moving.speed <= 0)
			{

				if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					setState(ENEMY_STATE::ATTACK);
					_direction = (playerpos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
				}
				}
	
		}


		break;
	}


	case(ENEMY_STATE::ATTACK):
	{
		_moving.speed = 1200;
		_moveDir.x = (_moving.speed) * timeElapsed * (_direction == DIRECTION::RIGHT ? (1) : (-1));

		if (playerCollision(playerpos))
		{
			setState(ENEMY_STATE::IDLE);
		}
	}
	break;
	}
	
	_ani->frameUpdate(timeElapsed);

	_moving.jumpPower += _moving.gravity * timeElapsed;
	_moveDir.y += _moving.jumpPower * timeElapsed;

	_enemyManager->moveEnemy(this, _moveDir);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void Ovibos::render()
{
	_img->setScale(_scale);
	_img->aniRender(_position,_ani, !(unsigned)_direction);
	
	D2D_RENDERER->drawRectangle(_rect);
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
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("Ovibos/Attack");
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, true);
		_ani->setFPS(10);
		_ani->start();

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
