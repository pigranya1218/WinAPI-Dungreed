#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelDog.h"

#define DEFSPEED 400.0f
#define MAXJUMP -1000.0f
#define DEFJUMP -5.0f;

void SkelDog::init(const Vector2& pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_detectRange = 100;
	_scale = 4;

	_size = Vector2(_img->getFrameSize().x - 4, _img->getFrameSize().y);
	_size = _size * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	_isDetect = 0;

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 0.2;
	_moving.force = Vector2(DEFSPEED, 0.f);
	_moving.gravity = Vector2(0, 4000);

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 3;
	_attack.attackInit(1, 0, 2);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3f;

	_active = true;

	_curHp = _maxHp = 40;

	_myEnemyType = static_cast<int>(ENEMY_TYPE::SKEL_DOG);
}

void SkelDog::release()
{
	_ani->release();
	delete _ani;
}

void SkelDog::update(float const timeElapsed)
{
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				if (_attack.update(timeElapsed))
				{
					setState(ENEMY_STATE::MOVE);
				}
			}
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			if (_moving.update(timeElapsed))
			{
				_direction = (_position.x > playerPos.x) ? (DIRECTION::LEFT) : (DIRECTION::RIGHT);
			}

			moveDir.x += timeElapsed * _moving.force.x * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

			if (_attack.update(timeElapsed))
			{
				setState(ENEMY_STATE::ATTACK);
				_direction = (_position.x > playerPos.x) ? (DIRECTION::LEFT) : (DIRECTION::RIGHT);
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			moveDir.x += timeElapsed * _moving.force.x * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

			if (_ani->getPlayIndex() == _img->getMaxFrameX() - 1)
			{
				if (_ani->isPlay())
				{
					_ani->pause();

					if (playerPos.y < _position.y)
					{
						float elapseY = fabsf(_position.y - playerPos.y);

						_moving.force.y = elapseY * DEFJUMP;
						if (_moving.force.y < MAXJUMP) _moving.force.y = MAXJUMP;
					}
				}
				_attack.attackRect(_myEnemyType, _enemyManager, rectMakePivot(_position, _size, PIVOT::CENTER));
			}			
		}
		break;
	}
	hitReaction(playerPos, moveDir, timeElapsed);

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
		if (_state == ENEMY_STATE::ATTACK && !_ani->isPlay())
		{
			setState(ENEMY_STATE::IDLE);
		}
	}

	_ani->frameUpdate(timeElapsed);

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		setState(ENEMY_STATE::DIE);
	}
}

void SkelDog::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}	

	D2D_RENDERER->drawRectangle(rectMakePivot(CAMERA->getRelativeV2(_position), _size, PIVOT::CENTER));
}

void SkelDog::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_imageName = "Skel/Dog/Idle";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();

			_attack.id.clear();
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			_imageName = "Skel/Dog/Move";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();			
		}
		break;
		case ENEMY_STATE::DIE:
		{
			_active = false;
		}
		break;
	}
}

void SkelDog::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				{
					_imageName = "Skel/Dog/Idle";
				}
				break;
				case ENEMY_STATE::MOVE:
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Skel/Dog/Move";
				}
				break;			
			}
			_img = IMAGE_MANAGER->findImage(_imageName);
			_moving.force.x = DEFSPEED;
			_hit.isHit = false;
			return;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));
	}	
}
