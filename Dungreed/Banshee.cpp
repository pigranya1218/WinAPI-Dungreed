#include "Banshee.h"

void Banshee::init(const Vector2& pos, DIRECTION direction)
{
	_img = IMAGE_MANAGER->findImage("Banshee/Idle");

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());	
	_ani->setDefPlayFrame(false, true);	
	_ani->setFPS(1);
	_ani->start();

	_position = pos;
	_direction = direction;

	_rect = rectMakePivot(_position, _img->getFrameSize(), PIVOT::CENTER);

	_state = ENEMY_STATE::IDLE;

	_active = true;
	_isDetect = false;
}

void Banshee::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Banshee::update()
{
	if (_active)
	{
		switch (_state)
		{
			case ENEMY_STATE::IDLE:
			{
				//setState(ENEMY_STATE::IDLE);
				break;
			}
			case ENEMY_STATE::ATTACK:
			{
				//setState(ENEMY_STATE::ATTACK);
				if (!_ani->isPlay())
				{
					setState(ENEMY_STATE::IDLE);
				}
				break;
			}
			case ENEMY_STATE::DIE:
			{
				//setState(ENEMY_STATE::DIE);
				break;
			}
		}

		_ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

		_rect = rectMakePivot(_position, _img->getFrameSize(), PIVOT::CENTER);
	}	
}

void Banshee::render()
{
	_img->setScale(5.0f);

	if(_active) _img->aniRender(_rect.getCenter(), _ani, !(unsigned)_direction);
}

void Banshee::setState(ENEMY_STATE state)
{
	if (_state == state) return;

	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_img = IMAGE_MANAGER->findImage("Banshee/Idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(1);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::ATTACK:
		{
			_img = IMAGE_MANAGER->findImage("Banshee/Attack");
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
		break;
	}
}
