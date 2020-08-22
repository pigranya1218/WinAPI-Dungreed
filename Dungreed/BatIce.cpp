#include "stdafx.h"
#include "EnemyManager.h"
#include "BatIce.h"

void BatIce::init(const Vector2 & pos, DIRECTION direction, bool spawnEffect)
{
	_ani = new Animation;

	setState(ENEMY_STATE::MOVE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	// 사이즈 설정
	_size = Vector2(_img->getFrameSize().x - 20, _img->getFrameSize().y - 10);
	_size = _size * _scale;

	if (spawnEffect)
	{
		setState(ENEMY_STATE::ENTER);
	}	

	// 공격 관련 변수 초기화
	_shooting.init("IceBullet", "IceBullet_FX", Vector2(600, 600), _scale, 2, 1.5, true, false, false, false, true, false);
	_shooting.attackInit(1, 1, 3);

	// 이동 관련 변수 초기화
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 3;
	_moving.force = Vector2(200, 0);
	_moving.angle = RANDOM->getFromFloatTo(0, PI2);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	_isDetect = 0;

	_active = true;

	_curHp = _maxHp = 30;
	
	_myEnemyType = static_cast<int>(ENEMY_TYPE::BAT_ICE);
}

void BatIce::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatIce::update(float const timeElapsed)
{
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	// 감지를 안했다면
	if (!_isDetect)
	{
		// 플레이어 계속 확인
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}
	else
	{
		// 플레이어 좌표따라 방햘 설정
		_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
	}

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::ENTER:
		{
			if (!_ani->isPlay())
			{
				EFFECT_MANAGER->play("Enemy_Destroy", _position, IMAGE_MANAGER->findImage("Enemy_Destroy")->getFrameSize() * _scale);
				setState(ENEMY_STATE::MOVE);
			}
		}
		break;
		case ENEMY_STATE::IDLE:
		{
			// 일정 주기로 이동
			if (_moving.update(timeElapsed))
			{
				// 방향은 랜덤
				_moving.angle = RANDOM->getFromFloatTo(0, PI2);
				setState(ENEMY_STATE::MOVE);
			}
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			// 이동
			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.force.x);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.force.x);	

			// 일정 주기로 공격
			if (_isDetect)
			{
				if (_shooting.delayUpdate(timeElapsed))
				{
					float angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
					for (int i = -1; i < 2; i++)
					{
						_shooting.createBullet(_position, angle + ((PI / 4) * i));
					}
					setState(ENEMY_STATE::ATTACK);
				}
			}
			else
			{
				if (_moving.update(timeElapsed))
				{
					// 아이들 상태로 변경
					setState(ENEMY_STATE::IDLE);
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			if (_ani->getPlayIndex() == 5 && !_shooting.bullets.empty())
			{
				SOUND_MANAGER->stop("Bat/Attack");
				SOUND_MANAGER->play("Bat/Attack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

				_shooting.fireBullet(_myEnemyType, _enemyManager);
			}
			if (!_ani->isPlay())
			{
				// 공격 완료 후 IDLE 상태로 변경
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

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{		
		setState(ENEMY_STATE::DIE);
	}
}

void BatIce::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}
}

void BatIce::setState(ENEMY_STATE state)
{
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
		case ENEMY_STATE::MOVE:
		{
			_imageName = "Bat/Ice/Move";

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
			_imageName = "Bat/Ice/Attack";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Ice/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::DIE:
		{
			SOUND_MANAGER->stop("Bat/Die");
			SOUND_MANAGER->play("Bat/Die", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

			_active = false;
		}
		break;
	}

	_state = state;
}

void BatIce::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				case ENEMY_STATE::MOVE:
				{
					_imageName = "Bat/Ice/Move";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Bat/Ice/Attack";
				}
				break;
			}
			_img = IMAGE_MANAGER->findImage(_imageName);
			_hit.isHit = false;
			_moving.force.x = 250;
			return;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));
	}	
}
