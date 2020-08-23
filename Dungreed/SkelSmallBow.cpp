//#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelSmallBow.h"

void SkelSmallBow::init(const Vector2 & pos, DIRECTION direction, bool spawnEffect)
{
	// 애니메이션 할당
	_ani = new Animation;
	_weaponAni = new Animation;

	// 손 이미지 
	_handImg = IMAGE_MANAGER->findImage("Skel/Small/Hand");

	// 활 공격 이미지 초기화
	_weaponImg = IMAGE_MANAGER->findImage("Skel/Small/Bow");
	_weaponAni->init(_weaponImg->getWidth(), _weaponImg->getHeight(), _weaponImg->getMaxFrameX(), _weaponImg->getMaxFrameY());
	_weaponAni->setDefPlayFrame(false, false);
	_weaponAni->setFPS(10);
	_weaponAni->stop();

	setState(ENEMY_STATE::IDLE);

	// 에너미 관련 변수 초기화
	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 700;

	// 충돌 사이즈 및 렉트 초기화
	_size = Vector2(_img->getFrameSize().x, _img->getFrameSize().y);
	_size = _size * _scale;

	if (spawnEffect)
	{
		setState(ENEMY_STATE::ENTER);
	}

	// 공격 관련 초기화
	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 3;
	_attack.angle = (_direction == DIRECTION::LEFT) ? (PI) : (0);

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.gravity = Vector2(0, 4000);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	_shooting.init("Arrow00", "ArrowHitEffect", Vector2(1300, 1300), _scale, 1.5, 2.5, true, false, false, false, true, false);
	_shooting.attackInit(3, 2, 10);

	// 플레이어 감지 변수 초기화
	_isDetect = _attackEnd = 0;

	_active = true;

	_curHp = _maxHp = 30;

	_myEnemyType = static_cast<int>(ENEMY_TYPE::SKEL_SMALL_BOW);
}

void SkelSmallBow::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SkelSmallBow::update(float const timeElapsed)
{
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::ENTER:
		{
			if (!_ani->isPlay())
			{
				SOUND_MANAGER->stop("Enemy/Spawn");
				SOUND_MANAGER->play("Enemy/Spawn", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

				EFFECT_MANAGER->play("Enemy_Destroy", _position, IMAGE_MANAGER->findImage("Enemy_Destroy")->getFrameSize() * _scale);
				setState(ENEMY_STATE::IDLE);
			}
		}
		break;
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				_attack.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
				if (_attack.angle > 360) _attack.angle -= 360;

				if (_attack.update(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
					_attackEnd = false;
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			if (_weaponAni->getPlayIndex() == 3 && !_attackEnd)
			{
				if (_weaponAni->isPlay())
				{
					_weaponAni->pause();
				}
				if (_shooting.delayUpdate(timeElapsed) && !_weaponAni->isPlay())
				{
					SOUND_MANAGER->stop("Skell/Arrow/Attack");
					SOUND_MANAGER->play("Skell/Arrow/Attack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

					_weaponAni->resume();
					_shooting.createBullet(_position, _attack.angle);
					_shooting.fireBullet(_myEnemyType, _enemyManager);

					_attackEnd = true;
				}
			}
			if (!_weaponAni->isPlay() && _attackEnd)
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

	if (_state != ENEMY_STATE::ENTER)
	{
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
	}


	_weaponAni->frameUpdate(timeElapsed);
	_ani->frameUpdate(timeElapsed);

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		setState(ENEMY_STATE::DIE);
	}
}

void SkelSmallBow::render()
{
	_img->setScale(_scale);
	_handImg->setScale(_scale);
	_handImg->setAngle(_attack.angle * (180 / PI));
	_weaponImg->setScale(_scale);
	
	if (_state != ENEMY_STATE::ENTER)
	{
		_img->render(CAMERA->getRelativeV2(_position), (_direction == DIRECTION::LEFT));

		// 활 시위 당기는 손 좌표 설정
		Vector2 handPos = _position;
		handPos.x += cosf(_attack.angle) * 15;
		handPos.y -= sinf(_attack.angle) * 20;

		// 무기 좌표 설정
		Vector2 weaponPos = handPos;
		weaponPos.x += cosf(_attack.angle) * 9;
		weaponPos.y -= sinf(_attack.angle) * 9;
		_weaponImg->setAngle(_attack.angle * (180 / PI));
		_weaponImg->aniRender(CAMERA->getRelativeV2(weaponPos), _weaponAni);

		// 활 시위 당기는 프레임에 따라 손 좌표도 수정
		if (_weaponAni->getPlayIndex() <= 3)
		{
			handPos.x += cosf(_attack.angle) * (_weaponAni->getPlayIndex() * -5);
			handPos.y -= sinf(_attack.angle) * (_weaponAni->getPlayIndex() * -5);
		}
		_handImg->render(CAMERA->getRelativeV2(handPos));	// 손 출력

		// 고정되는 손 좌표 설정
		handPos = _position;
		_handImg->setScale(_scale);
		_handImg->setAngle(_attack.angle * (180 / PI));
		handPos.x += cosf(_attack.angle) * 35;
		handPos.y -= sinf(_attack.angle) * 40;
		_handImg->render(CAMERA->getRelativeV2(handPos));	// 다른 손 출력
	}
	if(_state == ENEMY_STATE::ENTER)
	{
		_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));
	}

	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}
}

void SkelSmallBow::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
		case ENEMY_STATE::ENTER:
		{
			_img = IMAGE_MANAGER->findImage("Enemy_Create");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setPlayFrame(14, 0, false, false);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::IDLE:
		{
			_imageName = "Skel/Small/Idle";

			_ani->stop();
			_weaponAni->stop();

			_img = IMAGE_MANAGER->findImage(_imageName);
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_imageName = "Skel/Small/Idle";

			_weaponAni->stop();
			_ani->stop();

			_img = IMAGE_MANAGER->findImage(_imageName);
			_weaponAni->start();

			SOUND_MANAGER->stop("Skell/Arrow/Ready");
			SOUND_MANAGER->play("Skell/Arrow/Ready", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
		}
		break;
		case ENEMY_STATE::DIE:
		{
			SOUND_MANAGER->stop("Skell/Arrow/Ready");
			SOUND_MANAGER->stop("Skell/Arrow/Attack");

			_active = false;
		}
		break;
	}
}

void SkelSmallBow::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
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
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (1) : (-1));		
	}
}
