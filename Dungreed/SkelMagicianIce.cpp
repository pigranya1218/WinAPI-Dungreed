#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelMagicianIce.h"

void SkelMagicianIce::init(const Vector2 & pos, DIRECTION direction)
{
	_attackImg = IMAGE_MANAGER->findImage("Skel/Magician_Ice/Effect");

	_ani = new Animation;
	// 공격 이펙트 애니메이션 초기화
	_attackAni = new Animation;
	_attackAni->init(_attackImg->getWidth(), _attackImg->getHeight(), _attackImg->getMaxFrameX(), _attackImg->getMaxFrameY());
	_attackAni->setDefPlayFrame(false, false);
	_attackAni->setFPS(15);

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	_size = Vector2(_img->getFrameSize().x, _img->getFrameSize().y);
	_size = _size * _scale;	
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 0.5;	

	ZeroMemory(&_moving, sizeof(_moving));
	
	ZeroMemory(&_hit, sizeof(_hit));
	_hit.hitDelay = 0.3;

	_shooting.init("IceBullet", "IceBullet_FX", _scale, 0.2, 1.3, 850, true, true, false, false);

	_isDetect = _attacking = 0;
	_active = true;

	_curHp = _maxHp = 100;
}

void SkelMagicianIce::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SkelMagicianIce::update(float const timeElapsed)
{
	const Vector2 playerPos = _enemyManager->getPlayerPos();

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
			if (_isDetect && !_attacking)
			{
				if (_attack.update(timeElapsed))
				{
					_attackPos = playerPos;
					_shooting.bulletNum = 6;
					float angle = 0;
					for (int i = 0; i < 6; i++)
					{
						_shooting.createBullet(playerPos, angle += PI / 4);
						if (i == 2)angle += PI / 4;
					}
					setState(ENEMY_STATE::ATTACK);
					_attacking = true;
				}
			}
		}		
		break;
		case ENEMY_STATE::ATTACK:
		{
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

	if (_attacking)
	{
		if (_attackAni->getPlayIndex() == 15)
		{
			if (_attackAni->isPlay()) _attackAni->pause();

			if (_shooting.delayUpdate(timeElapsed))
			{
				_shooting.fireBullet(_enemyManager);
				_attackAni->resume();
			}
			if (!_attackAni->isPlay() && _shooting.bullets.empty())
			{
				_attacking = false;
			}
		}
	}

	_enemyManager->moveEnemy(this, moveDir);
	
	_ani->frameUpdate(timeElapsed);
	_attackAni->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void SkelMagicianIce::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_attackPos, Vector2(10, 10), PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 1, 5);
	_img->setScale(_scale);
	_attackImg->setScale(_scale);

	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	if (_attacking)
	{
		_attackImg->aniRender(CAMERA->getRelativeV2(_attackPos), _attackAni);
	}

	if (_curHp != _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += 50;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
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
			_imageName = "Skel/Magician_Ice/Idle";

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
			_imageName = "Skel/Magician_Ice/Attack";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();

			_attackAni->stop();
			_attackAni->start();
		}	
		break;
		case ENEMY_STATE::DIE:
		{
			_active = false;
		}
		break;
	}
}

void SkelMagicianIce::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.hitUpdate(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				{
					_imageName = "Skel/Magician_Ice/Idle";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Skel/Magician_Ice/Attack";
				}
				break;
			}
			_img = IMAGE_MANAGER->findImage(_imageName);
			_hit.isHit = false;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));

		return;
	}
}
