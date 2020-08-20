#include "stdafx.h"
#include "EnemyManager.h"
#include "Belial.h"

void Belial::init(const Vector2 & pos)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = DIRECTION::DOWN;
	_scale = 4;
	_size = _img->getFrameSize() * _scale;

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(0, 150);
	_moving.delay = 0.4;

	_active = true;

	_curHp = _maxHp = 100;

	_myEnemyType = static_cast<int>(ENEMY_TYPE::BELIAL);
}

void Belial::release()
{
}

void Belial::update(float const timeElapsed)
{
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			switch (_direction)
			{
				case DIRECTION::UP:
				{
					_position.y -= _moving.force.y * timeElapsed;
					if (_moving.update(timeElapsed))
					{
						_direction = DIRECTION::DOWN;
					}
				}
				break;
				case DIRECTION::DOWN:
				{
					_position.y += _moving.force.y * timeElapsed;
					if (_moving.update(timeElapsed))
					{
						_direction = DIRECTION::UP;
					}
				}
				break;
			}
		}
		break;
		case ENEMY_STATE::MOVE:
		break;
	case ENEMY_STATE::ATTACK:
		break;
	case ENEMY_STATE::SKILL:
		break;
	case ENEMY_STATE::DIE:
		break;
	default:
		break;
	}

	_ani->frameUpdate(timeElapsed);
}

void Belial::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani);
}

void Belial::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_imageName = "Belial/Head/Idle";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::ATTACK:
		{

		}
		break;
		case ENEMY_STATE::DIE:
		{

		}
		break;
	}
}
