#include "stdafx.h"
#include "EnemyManager.h"
#include "BatBomb.h"

void BatBomb::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 800;

	// 사이즈 설정
	_size = Vector2(_img->getFrameSize().x - 10, _img->getFrameSize().y);
	_size = _size * _scale;

	// 충돌 렉트 설정
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);	

	// 이동 관련 변수 초기화
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 0.2;
	_moving.force = Vector2(500, 0);
	_moving.angle = 0;

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.hitDelay = 0.3;

	_isDetect = 0;
	_active = true;

	_curHp = _maxHp = 100;
}

void BatBomb::release()
{
	_ani->release();
	delete _ani;
}

void BatBomb::update(float const timeElapsed)
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
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				setState(ENEMY_STATE::MOVE);
			}
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			// 이동			
			if (_moving.update(timeElapsed))
			{
				_moving.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
			}

			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.force.x);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.force.x);				

			if (getDistance(_position.x, _position.y, playerPos.x, playerPos.y) < 50)
			{
				setState(ENEMY_STATE::ATTACK);
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{				
			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::DIE);				
			}
		}
		break;
		case ENEMY_STATE::DIE:
		{
			//EFFECT_MANAGER->play("Bat_Explosion", _position, Vector2(250, 250));
		}
		break;
	}
	hitReaction(playerPos, moveDir, timeElapsed);

	_enemyManager->moveEnemy(this, moveDir, true, false);

	_ani->frameUpdate(timeElapsed);
}

void BatBomb::render()
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

void BatBomb::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		case ENEMY_STATE::MOVE:
		{
			_imageName = "Bat/Bomb/Move";

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
			_imageName = "Bat/Bomb/Attack_Begin";

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

void BatBomb::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.hitUpdate(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				case ENEMY_STATE::MOVE:
				{
					_imageName = "Bat/Bomb/Move";					
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					//_imageName = "Bat/Bomb/Attack_Begin";
				}
				break;
			}
			_img = IMAGE_MANAGER->findImage(_imageName);
			_hit.isHit = false;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));
	}
}

bool BatBomb::hitEffect(FloatCircle * circle, AttackInfo * info)
{
	_isDetect = true;
	_hit.isHit = true;
	_hit.hitCount = 0;
	//_hit.knockCount = 0;
	_moving.gravity.x = info->knockBack;

	if (_state == ENEMY_STATE::IDLE || _state == ENEMY_STATE::MOVE)
	{
		_imageName += "_Shot";
	}	
	_img = IMAGE_MANAGER->findImage(_imageName);

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));

	return true;
}
