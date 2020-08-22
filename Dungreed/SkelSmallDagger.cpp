#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelSmallDagger.h"

#define DEFSPEED 150.0f

void SkelSmallDagger::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;
	_weaponAni = new Animation;

	_weaponImg = IMAGE_MANAGER->findImage("Skel/Small/Dagger");
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
	_moving.delay = 0.3f;
	_moving.force = Vector2(DEFSPEED, 0.f);
	_moving.gravity = Vector2(0, 4000);

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 2.0f;
	_attack.distance = 100;
	_attack.circleSize = 85;
	_attack.attackInit(1, 0, 2);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3f;

	_isDetect = 0;
	_active = true;

	_curHp = _maxHp = 60;
	count = 0;
	_myEnemyType = static_cast<int>(ENEMY_TYPE::SKEL_SMALL_DAGGER);
}

void SkelSmallDagger::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SkelSmallDagger::update(float const timeElapsed)
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
			// 공격 프레임
			if (_weaponAni->getPlayIndex() == 7)
			{
				count++;
				if (count == 1)
				{
					SOUND_MANAGER->stop("Skell/Small/Attack");
					SOUND_MANAGER->play("Skell/Small/Attack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
				}

				Vector2 attackPos = _position;
				attackPos.x += (_direction == DIRECTION::LEFT) ? (_size.x * -0.5f) : (_size.x * 0.5f);
				attackPos.y += _size.y * 0.3f;

				float startRad = (_direction == DIRECTION::LEFT) ? (PI / 2) : (0);
				float endRad = startRad + PI / 2;

				_attack.attackCircle(_myEnemyType, _enemyManager, Vector2(attackPos), startRad, endRad);
			}
			else
			{
				_attack.id.clear();
			}
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

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		setState(ENEMY_STATE::DIE);
	}
}

void SkelSmallDagger::render()
{
	_img->setScale(_scale);
	_weaponImg->setScale(_scale);

	Vector2 weaponPos = _position;
	weaponPos.x += _weaponImg->getFrameSize().x * 0.4f * _scale * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));
	weaponPos.y -= 3 * _scale;

	_weaponImg->aniRender(CAMERA->getRelativeV2(weaponPos), _weaponAni, (_direction == DIRECTION::LEFT));

	if (_state == ENEMY_STATE::MOVE)
	{
		_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_position), (_direction == DIRECTION::LEFT));
	}

	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}

	_attack.circleDebug.render(true);
}

void SkelSmallDagger::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_imageName = "Skel/Small/Idle";

			_ani->stop();
			_weaponAni->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			_imageName = "Skel/Small/Move";

			_ani->stop();
			_weaponAni->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_imageName = "Skel/Small/Idle";

			_ani->stop();
			_weaponAni->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
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

void SkelSmallDagger::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
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
			return;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));
	}
}
