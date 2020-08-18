#include "stdafx.h"
#include "EnemyManager.h"
#include "BatGiantNormal.h"

void BatGiantNormal::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 100;

	_size = Vector2(_img->getFrameSize().x - 35, _img->getFrameSize().y - 15);
	_size = _size * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 3.f;

	ZeroMemory(&_moving, sizeof(_moving));
	
	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3f;

	_shooting.init("GiantBullet", "GiantBullet_FX", _scale, 0.3f, 500.f, 500.f, false, true, true, true);

	_isDetect = 0;
	_detectRange = 300.f;

	_active = true;

	_curHp = _maxHp = 100.f;
}

void BatGiantNormal::release()
{
	_ani->release();
	delete _ani;
}

void BatGiantNormal::update(float const timeElapsed)
{
	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
				
				if (_shooting.bulletNum > 0)
				{
					for (int i = 0; i < 3; i++)
					{
						for (int j = -1; j < 2; j++)
						{
							_shooting.createBullet(_position, _attack.angle + (PI / 6) * j);
						}
					}
					if (_shooting.bulletNum <= 0)
					{
						setState(ENEMY_STATE::ATTACK);
					}
				}
				else
				{
					if (!_shooting.bullets.empty() && _shooting.bulletNum == 0)
					{
						if (_shooting.delayUpdate(timeElapsed))
						{
							_shooting.fireBullet(_enemyManager, 3);
						}
					}
					if (_attack.update(timeElapsed))
					{
						if (_shooting.bullets.empty())
						{
							_shooting.bulletNum = 9;
						}
						_attack.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
					}
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			if (_ani->getPlayIndex() >= 4)
			{
				if (_shooting.delayUpdate(timeElapsed))
				{
					_shooting.fireBullet(_enemyManager, 3);
				}				
			}
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
	hitReaction(playerPos, moveDir, timeElapsed);

	_enemyManager->moveEnemy(this, moveDir, true, false);

	_ani->frameUpdate(timeElapsed);
	_shooting.aniUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void BatGiantNormal::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));
	_shooting.render();

	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}
}

void BatGiantNormal::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_imageName = "Bat/Giant_Normal/Idle";

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
			_imageName = "Bat/Giant_Normal/Attack";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
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

void BatGiantNormal::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				{
					_imageName = "Bat/Giant_Normal/Idle";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Bat/Giant_Normal/Attack";
				}
				break;
			}
			_img = IMAGE_MANAGER->findImage(_imageName);
			_hit.isHit = false;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (1) : (-1));
	}
}
