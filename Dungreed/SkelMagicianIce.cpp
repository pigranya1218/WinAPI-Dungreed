#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelMagicianIce.h"

void SkelMagicianIce::init(const Vector2 & pos, DIRECTION direction)
{
	_attackImg = IMAGE_MANAGER->findImage("Skel/Magician_Ice/Effect");

	_ani = new Animation;

	_attackAni = new Animation;
	_attackAni->init(_attackImg->getWidth(), _attackImg->getHeight(), _attackImg->getMaxFrameX(), _attackImg->getMaxFrameY());
	_attackAni->setDefPlayFrame(false, false);
	_attackAni->setFPS(10);

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	_size = Vector2(_img->getFrameSize().x, _img->getFrameSize().y);
	_size = _size * _scale;	

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 0.5;	

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	_isDetect = 0;
}

void SkelMagicianIce::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SkelMagicianIce::update(float const timeElapsed)
{
	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	Vector2 moveDir(0, 0);
	// 상태에 따른 행동처리
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect && _attack.update(timeElapsed))
			{
				_attackPos = _enemyManager->getPlayerPos();
				setState(ENEMY_STATE::ATTACK);
			}
			break;
		}		
		case ENEMY_STATE::ATTACK:
		{
			if (!_attackAni->isPlay())
			{
				setState(ENEMY_STATE::IDLE);
			}

			_attackAni->frameUpdate(timeElapsed);
			break;
		}	
		case ENEMY_STATE::DIE:
		{
			break;
		}
	}
	
	_ani->frameUpdate(timeElapsed);
	

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void SkelMagicianIce::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);

	_img->setScale(_scale);
	_attackImg->setScale(_scale);

	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, !(bool)_direction);

	if (_attackAni->isPlay())
	{
		_attackImg->aniRender(CAMERA->getRelativeV2(_attackPos), _attackAni);
	}
}

void SkelMagicianIce::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Magician_Ice/Idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();

			break;
		}	
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Magician_Ice/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(10);
			_ani->start();

			_attackAni->stop();
			_attackAni->start();

			break;
		}	
		case ENEMY_STATE::DIE:
		{
			break;
		}
	}
}
