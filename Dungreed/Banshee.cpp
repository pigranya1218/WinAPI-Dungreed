#include "Banshee.h"

void Banshee::init(const Vector2& pos, DIRECTION direction)
{	
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 5;

	_size = _img->getFrameSize() * _scale;

	ZeroMemory(&_shooting, sizeof(_shooting));
	_shooting.delay = 30;

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void Banshee::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Banshee::update(float const timeElapsed)
{
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
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
				setState(ENEMY_STATE::IDLE);
			}
			break;
		}
		case ENEMY_STATE::DIE:
		{

			break;
		}
	}

	_ani->frameUpdate(timeElapsed * 10);
}

void Banshee::render()
{
	D2D_RENDERER->drawRectangle(_rect);
	_img->setScale(_scale);
	_img->aniRender(_position, _ani, !(bool)_direction);
}

void Banshee::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Banshee/Idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(1);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
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
	}
}
