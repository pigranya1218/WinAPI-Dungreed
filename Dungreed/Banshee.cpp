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

	ZeroMemory(&_shooting, sizeof(_shooting));
	_shooting.delay = 30;

	_bullet = new BulletManager;
	_bullet->init();

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

	_bullet->update();
}

void Banshee::render()
{
	_img->setScale(5.0f);

	if(_active) _img->aniRender(_rect.getCenter(), _ani, !(unsigned)_direction);

	_bullet->render();
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

			for (int i = 0; i < 8; i++)
			{
				_bullet->createBullet("Banshee/Bullet", _position, 10, _shooting.angle, 500, 5.0f);
				_shooting.angle += PI / 4;
			}

			_bullet->fireBullet();

			break;
		}		
		case ENEMY_STATE::DIE:
		{

			break;
		}
		break;
	}
}
