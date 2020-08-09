#include "stdafx.h"
#include "BatRed.h"

void BatRed::init(const Vector2& pos, DIRECTION direction)
{
	_img = IMAGE_MANAGER->findImage("Bat/Red/Move");

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(1);
	_ani->start();

	_position = pos;
	_direction = direction;

	_rect = rectMakePivot(_position, _img->getFrameSize(), PIVOT::CENTER);

	_state = ENEMY_STATE::MOVE;

	ZeroMemory(&_shooting, sizeof(_shooting));
	_shooting._delay = 30;

	_bm = new BulletManager;
	_bm->init();
}

void BatRed::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatRed::update()
{
	switch (_state)
	{
		case ENEMY_STATE::MOVE:
		{
			if (_shooting.update(TIME_MANAGER->getElapsedTime() * 10))
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

				_bm->fireBullet();
			}
			break;
		}
		case ENEMY_STATE::DIE:
		break;
	}

	_bm->update();

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	_rect = rectMakePivot(_position, _img->getFrameSize(), PIVOT::CENTER);
}

void BatRed::render()
{
	_img->setScale(5.0f);
	_img->aniRender(_rect.getCenter(), _ani, !(unsigned)_direction);

	_bm->render();
}

void BatRed::setState(ENEMY_STATE state)
{
	if (_state == state) return;

	_state = state;

	switch (state)
	{
		case ENEMY_STATE::MOVE:
		{
			_img = IMAGE_MANAGER->findImage("Bat/Red/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::ATTACK:
		{
			_img = IMAGE_MANAGER->findImage("Bat/Red/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->start();

			_bm->createBullet("Bat/Bullet/Small", _position, 100, PI, 30);

			break;
		}
	case ENEMY_STATE::DIE:
		break;
	}
}
