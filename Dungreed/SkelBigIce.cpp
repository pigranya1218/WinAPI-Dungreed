#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelBigIce.h"

#define DEFSPEED 200.0f

void SkelBigIce::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	_size = Vector2(_img->getFrameSize().x - 15, _img->getFrameSize().y);
	_size = _size * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(DEFSPEED, 0.f);
	_moving.gravity = Vector2(0, 4000);
	_moving.delay = 0.2;

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 1;
	_attack.distance = 100;
	_attack.circleSize = 200;
	_attack.attackInit(10, 15, 3);
	
	ZeroMemory(&_skill, sizeof(_skill));
	_skill.delay = 2;
	_skill.distance = 300;

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3f;

	//_shooting.init("IceBullet", "IceBullet_FX", _scale, 0.05, 1, 700, true, true, false, false);
	_shooting.init("IceBullet", "IceBullet_FX", Vector2(700, 700), _scale, 0.05f, 1, true, false, false, false, true, false);

	_isDetect = 0;
	_active = true;

	_curHp = _maxHp = 100;
}

void SkelBigIce::release()
{
}

void SkelBigIce::update(float const timeElapsed)
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
			if (_isDetect)
			{
				setState(ENEMY_STATE::MOVE);
			}
			break;
		}		
		case ENEMY_STATE::MOVE:
		{
			if (_moving.update(timeElapsed))
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
			}

			moveDir.x += timeElapsed * _moving.force.x * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

			float distance = getDistance(playerPos.x, playerPos.y, _position.x, _position.y);

			if (fabsf(_position.x - playerPos.x) < _size.x)
			{
				if (_isStand)
				{
					if (playerPos.y < (_position.y - _size.y * 1.3f))
					{
						_moving.force.y = -1400;
					}
					else if (playerPos.y > (_position.y + _size.y * 0.5f))
					{
						_position.y += 1.5f;
						_moving.force.y = 0.1f;
					}
				}				
			}
			if (distance < _attack.distance)
			{
				if (_attack.update(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
				}
			}
			else if (distance > _skill.distance)
			{
				if (_skill.update(timeElapsed))
				{
					_shooting.bulletNum = RANDOM->getFromIntTo(4, 7);
					setState(ENEMY_STATE::SKILL);
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			if (_ani->getPlayIndex() == 2)
			{
				Vector2 attackPos = _position;
				attackPos.x += (_direction == DIRECTION::LEFT) ? (_size.x * -0.5f) : (_size.x * 0.5f);
				attackPos.y += _size.y * 0.5f;

				float startRad = (_direction == DIRECTION::LEFT) ? (PI / 2) : (0);
				float endRad = startRad + PI / 2;

				_attack.attackCircle(_myEnemyType, _enemyManager, Vector2(attackPos), startRad, endRad);
			}
			else
			{
				_attack.id.clear();
			}
			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::MOVE);
			}
		}		
		break;
		case ENEMY_STATE::SKILL:
		{			
			if (_shooting.bulletNum > 0 && _ani->getPlayIndex() >= 6)
			{
				if (_shooting.delayUpdate(timeElapsed))
				{
					float angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);

					angle += RANDOM->getFromFloatTo(PI / 10 * -1, PI / 10);

					_shooting.createBullet(_position, angle);
					_shooting.fireBullet(_enemyManager);
				}
			}
			else if (!_ani->isPlay() && _shooting.bulletNum <= 0)
			{
				setState(ENEMY_STATE::MOVE);
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

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		setState(ENEMY_STATE::DIE);
	}
}

void SkelBigIce::render()
{
	_img->setScale(_scale);

	Vector2 drawPos = _position;	
	if (_state == ENEMY_STATE::ATTACK || _state == ENEMY_STATE::SKILL)
	{
		// 이동 이미지 기준으로
		Image* img = IMAGE_MANAGER->findImage("Skel/Big_Ice/Move");

		// 이미지 간의 사이즈 차이 구하고
		Vector2 elapsePos((_img->getFrameSize().x - img->getFrameSize().x) * _scale, (_img->getFrameSize().y - img->getFrameSize().y) * _scale);
		// 최종 출력 포지션 설정
		if (_state == ENEMY_STATE::ATTACK)
		{
			drawPos.x += (_direction == DIRECTION::RIGHT) ? +(elapsePos.x / 2) : -(elapsePos.x / 2);
		}
		drawPos.y -= elapsePos.y / 2;
	}	
	_img->aniRender(CAMERA->getRelativeV2(drawPos), _ani, (_direction == DIRECTION::LEFT));

	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}

	_attack.circleDebug.render(true);
}

void SkelBigIce::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_imageName = "Skel/Big_Ice/Idle";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}		
		break;
		case ENEMY_STATE::MOVE:
		{
			_imageName = "Skel/Big_Ice/Move";

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
			_imageName = "Skel/Big_Ice/Attack";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();
		}		
		break;
		case ENEMY_STATE::SKILL:
		{
			_imageName = "Skel/Big_Ice/Skill";

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

void SkelBigIce::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				{
					_imageName = "Skel/Big_Ice/Idle";
				}
				break;
				case ENEMY_STATE::MOVE:
				{
					_imageName = "Skel/Big_Ice/Move";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Skel/Big_Ice/Attack";
				}
				break;
				case ENEMY_STATE::SKILL:
				{
					_imageName = "Skel/Big_Ice/Skill";
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
