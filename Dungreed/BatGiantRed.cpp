#include "stdafx.h"
#include "EnemyManager.h"
#include "BatGiantRed.h"

void BatGiantRed::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 100;	

	ZeroMemory(&_shooting, sizeof(_shooting));
	_shooting.delay = 3;

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 3;
	_moving.speed = 350;
	_moving.angle = RANDOM->getFromFloatTo(0, PI2);

	_size = Vector2(_img->getFrameSize().x - 35, _img->getFrameSize().y - 15);
	_size = _size * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	_isDetect = 0;
	_detectRange = 300;
}

void BatGiantRed::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatGiantRed::update(float const timeElapsed)
{
	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				_direction = _enemyManager->getPlayerPos().x > _position.x ? DIRECTION::RIGHT : DIRECTION::LEFT;

				if (_shooting.update(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			if (!_ani->isPlay())
			{
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
}

void BatGiantRed::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, !(bool)_direction);
}

void BatGiantRed::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Giant_Red/Idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Giant_Red/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
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
