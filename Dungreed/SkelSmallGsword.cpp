#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelSmallGsword.h"

void SkelSmallGsword::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;
	_weaponAni = new Animation;

	_weaponImg = IMAGE_MANAGER->findImage("Skel/Small/Gsword");
	_weaponAni->init(_weaponImg->getWidth(), _weaponImg->getHeight(), _weaponImg->getMaxFrameX(), _weaponImg->getMaxFrameY());
	_weaponAni->setDefPlayFrame(false, false);
	_weaponAni->setFPS(15);

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;

	_size = _img->getFrameSize() * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 0.3;
	_moving.force = Vector2(150, 0);
	_moving.gravity = Vector2(0, 4000);

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 3;
	_attack.distance = 100;

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.hitDelay = 0.3;

	_isDetect = 0;

	_active = true;

	_curHp = _maxHp = 100;
}

void SkelSmallGsword::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SkelSmallGsword::update(float const timeElapsed)
{
	Vector2 playerPos = _enemyManager->getPlayerPos();

	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _attack.distance);
	}

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				if (_attack.update(timeElapsed * 10))
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

				if (fabsf(_position.x - playerPos.x) < 50 && _isStand)
				{
					if (playerPos.y < (_position.y - _size.y * 2))
					{
						_moving.force.y = -1400;
					}
				}
			}

			moveDir.x += timeElapsed * _moving.force.x * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

			if (getDistance(_position.x, _position.y, playerPos.x, playerPos.y) < _attack.distance)
			{
				if (_attack.update(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			if (!_weaponAni->isPlay())
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

	if (_isStand && _moving.force.y == 0)
	{
		_position.y -= 15;
		moveDir.y += 17;
	}
	_moving.force.y += _moving.gravity.y * timeElapsed;
	moveDir.y += _moving.force.y * timeElapsed;

	// 이동할 포지션 최종
	_enemyManager->moveEnemy(this, moveDir);
	if (_isStand)
	{
		_moving.force.y = 0;
	}

	_ani->frameUpdate(timeElapsed);
	_weaponAni->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void SkelSmallGsword::render()
{
	_img->setScale(_scale);
	_weaponImg->setScale(_scale);

	Vector2 weaponPos = _position;
	weaponPos.x += _weaponImg->getFrameSize().x * 0.3f * _scale * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));
	weaponPos.y -= 2 * _scale;

	_weaponImg->aniRender(CAMERA->getRelativeV2(weaponPos), _weaponAni, (_direction == DIRECTION::LEFT));

	if (_state == ENEMY_STATE::MOVE)
	{
		_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_position), (_direction == DIRECTION::LEFT));
	}

	if (_curHp != _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += 50;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}
}

void SkelSmallGsword::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_weaponAni->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Small/Idle");
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();
			_weaponAni->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Small/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_weaponAni->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Small/Idle");
			_weaponAni->start();
		}
		break;
		case ENEMY_STATE::DIE:
		{
			_active = false;
		}
		break;
	}
}

void SkelSmallGsword::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.hitUpdate(timeElapsed))
		{
			switch (_state)
			{
			case ENEMY_STATE::IDLE:
			{
				_imageName = "Skel/Small/Idle";
			}
			break;
			case ENEMY_STATE::MOVE:
			{
				_imageName = "Skel/Small/Move";
			}
			break;
			case ENEMY_STATE::ATTACK:
			{
				_imageName = "Skel/Small/Idle";
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
