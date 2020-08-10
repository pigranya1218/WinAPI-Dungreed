#include "stdafx.h"
#include "EnemyManager.h"
#include "BatRed.h"

void BatRed::init(const Vector2& pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::MOVE);	

	_position = pos;
	_direction = direction;
	_scale = 5;

	ZeroMemory(&_shooting, sizeof(_shooting));
	_shooting.delay = 30;

	_size = _img->getFrameSize() * _scale;

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void BatRed::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatRed::update(float const timeElapsed)
{
	_direction = _enemyManager->getPlayerPos().x > _position.x ? DIRECTION::RIGHT : DIRECTION::LEFT;

	switch (_state)
	{
		case ENEMY_STATE::MOVE:
		{
			if (_shooting.update(timeElapsed * 10))
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
		case ENEMY_STATE::DIE:
		{
			break;
		}		
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void BatRed::render()
{
	_img->setScale(_scale);

	D2D_RENDERER->drawRectangle(_rect);
	_img->aniRender(_position, _ani, !(unsigned)_direction);
}

void BatRed::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::MOVE:
		{
			_img = IMAGE_MANAGER->findImage("Bat/Red/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(1);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::ATTACK:
		{
			_img = IMAGE_MANAGER->findImage("Bat/Red/Attack");
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
