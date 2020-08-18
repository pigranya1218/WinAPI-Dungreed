#include "stdafx.h"
#include "EnemyManager.h"
#include "Banshee.h"

void Banshee::init(const Vector2& pos, DIRECTION direction)
{	
	// 애니메이션 할당
	_ani = new Animation;

	// 초기 상태는 기본 상태
	setState(ENEMY_STATE::IDLE);

	// 변수 초기화
	_position = pos;
	_direction = direction;
	_scale = 4;
	_isDetect = 0;
	_detectRange = 300;

	// 피격 렉트 및 사이즈 초기화
	_size = _img->getFrameSize() * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	// 탄막 초기화
	_shooting.init("Banshee/Bullet", "Banshee/Bullet_FX", _scale, 3, 2.2, 500, false, false, true, true);

	_active = true;
}

void Banshee::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Banshee::update(float const timeElapsed)
{
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
				if (_shooting.delayUpdate(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);

					for (int i = 0; i < 12; i++)
					{
						_shooting.angle += PI / 6;
						_shooting.createBullet(_position, _shooting.angle);
					}
					_shooting.fireBullet(_enemyManager);
				}
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
	_enemyManager->moveEnemy(this, moveDir);

	_ani->frameUpdate(timeElapsed);
}

void Banshee::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, !(bool)_direction);
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
			_ani->setFPS(15);
			_ani->start();
		}	
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Banshee/Attack");
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
