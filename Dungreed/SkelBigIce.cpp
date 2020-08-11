#include "SkelBigIce.h"

void SkelBigIce::init(const Vector2 & pos, DIRECTION direction)
{
	_img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Idle");

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(1);
	_ani->start();

	_position = pos;
	_direction = direction;
	_size = Vector2();

	_rect = rectMakePivot(_position, _img->getFrameSize(), PIVOT::CENTER);

	_state = ENEMY_STATE::IDLE;

	_active = true;
	_isDetect = false;

	_scale = 5;

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 20;
}

void SkelBigIce::release()
{
}

void SkelBigIce::update()
{
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			_position.y = WINSIZEY - _img->getFrameSize().y * _scale / 2;

			if (_attack.update(TIME_MANAGER->getElapsedTime() * 10))
			{
				setState(ENEMY_STATE::ATTACK);
			}
			break;
		}		
		case ENEMY_STATE::ATTACK:
		{
			_position.y = WINSIZEY - _img->getFrameSize().y * _scale / 2;

			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::IDLE);
			}
			break;
		}		
		case ENEMY_STATE::SKILL:
		{
			_position.y = WINSIZEY - _img->getFrameSize().y * _scale / 2;

			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::IDLE);
			}
			break;
		}		
	case ENEMY_STATE::DIE:
		break;
	default:
		break;
	}


	_ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	_rect = rectMakePivot(_position, _img->getFrameSize() * _scale, PIVOT::CENTER);
}

void SkelBigIce::render()
{
	

	D2D_RENDERER->drawRectangle(_rect);
	_img->setScale(_scale);
	/*Vector2 drawPosition = _position;
	switch (_state)
	{
	case :
		drawPosition.x += 10;
		break;
	}

	_img->aniRender(drawPosition, _ani, !(unsigned)_direction);*/
}

void SkelBigIce::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(1);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::MOVE:
		{
			break;
		}		
		case ENEMY_STATE::ATTACK:
		{
			_img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(1);
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
		break;
	}
}
