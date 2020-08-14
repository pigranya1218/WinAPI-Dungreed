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

	_size = Vector2(_img->getFrameSize().x - 35, _img->getFrameSize().y - 15);
	_size = _size * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 3;

	_shooting.init("GiantBullet", "GiantBullet_FX", _scale, 0.02, 500, 1000, false, false, true, true);

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
	const Vector2 playerPos = _enemyManager->getPlayerPos();
	
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				
				if (_shooting.bulletNum > 0)
				{
					if (_shooting.delayUpdate(timeElapsed))
					{
						Vector2 bulletPos = _position;
						bulletPos.x += cosf(PI2 / 20 * _shooting.bulletNum) * (_size.x + 10);
						bulletPos.y -= sinf(PI2 / 20 * _shooting.bulletNum) * (_size.x + 10);

						_shooting.createBullet(bulletPos, _shooting.angle);						
					}
					if (_shooting.bulletNum <= 0)
					{
						setState(ENEMY_STATE::ATTACK);
					}
				}
				else
				{
					if (_attack.update(timeElapsed))
					{
						if (_shooting.bullets.empty())
						{
							_shooting.bulletNum = 20;
						}
						_shooting.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
					}
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{			
			if (_ani->getPlayIndex() == 4)
			{
				_shooting.fireBullet(_enemyManager);
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

	_ani->frameUpdate(timeElapsed);
	_shooting.aniUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void BatGiantRed::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));
	_shooting.render();
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
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Giant_Red/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::DIE:
		{
		}
		break;
	}
}
