#include "stdafx.h"
#include "EnemyManager.h"
#include "BatBomb.h"

void BatBomb::init(const Vector2 & pos, DIRECTION direction, bool spawnEffect)
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

	if (spawnEffect)
	{
		setState(ENEMY_STATE::ENTER);
	}

	// 이동 관련 변수 초기화
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 0.2;
	_moving.force = Vector2(500, 0);
	_moving.angle = 0;

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.attackInit(4, 8, 0);

	_isDetect = 0;
	_active = true;

	_curHp = _maxHp = 25;

	_myEnemyType = static_cast<int>(ENEMY_TYPE::BAT_BOMB);
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
				setState(ENEMY_STATE::SKILL);
			}
		}
		break;
		case ENEMY_STATE::SKILL:
		{
			// 공격 판정 프레임
			if (_ani->getPlayIndex() >= 2 && _ani->getPlayIndex() <= 4)
			{
				Vector2 rightPos = _position;
				rightPos.x += cosf(PI / 4 * 7) * 150;
				rightPos.y -= sinf(PI / 4 * 7) * 150;

				Vector2 leftPos = _position;
				leftPos.x += cosf(PI / 4 * 3) * 150;
				leftPos.y -= sinf(PI / 4 * 3) * 150;

				FloatRect rightRc(rightPos, _img->getFrameSize() * _scale, PIVOT::CENTER);
				FloatRect leftRc(leftPos, _img->getFrameSize() * _scale, PIVOT::CENTER);

				FloatRect atkRect(Vector2(leftRc.left, leftRc.top), Vector2(rightRc.right - leftRc.left, rightRc.bottom - leftRc.top), PIVOT::LEFT_TOP);

				_attack.attackRect(_myEnemyType, _enemyManager, atkRect);
			}
			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::DIE);
				//SOUND_MANAGER->stop("BoomBat/Explod");				
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

void BatBomb::render()
{
	_img->setScale(_scale);

	Vector2 drawPos = _position;

	_img->aniRender(CAMERA->getRelativeV2(drawPos), _ani, (_direction == DIRECTION::LEFT));
	if (_state == ENEMY_STATE::SKILL)
	{
		for (int i = 0; i < 4; i++)
		{
			drawPos.x += cosf(PI / 4 * (1 + i * 2)) * 150;
			drawPos.y -= sinf(PI / 4 * (1 + i * 2)) * 150;

			_img->setScale(_scale);
			_img->aniRender(CAMERA->getRelativeV2(drawPos), _ani);

			drawPos = _position;
		}
	}	

	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}
}

void BatBomb::setState(ENEMY_STATE state)
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

			SOUND_MANAGER->stop("BoomBat/Ready");
			SOUND_MANAGER->play("BoomBat/Ready", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
		}		
		break;
		case ENEMY_STATE::SKILL:
		{
			_imageName = "Bat_Explosion";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();

			SOUND_MANAGER->stop("BoomBat/Explod");
			SOUND_MANAGER->play("BoomBat/Explod", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
		}
		break;
		case ENEMY_STATE::DIE:
		{
			_active = false;
		}
		break;
	}

	_state = state;
}

void BatBomb::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
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
	_hit.count = 0;
	//_hit.knockCount = 0;
	_moving.gravity.x = info->knockBack;

	if (_state == ENEMY_STATE::IDLE || _state == ENEMY_STATE::MOVE)
	{
		_img = IMAGE_MANAGER->findImage(_imageName + "_Shot");
	}	

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));

	return true;
}

bool BatBomb::hitEffect(Projectile * projectile)
{
	AttackInfo* info = projectile->getAttackInfo();
	_isDetect = true;
	_hit.isHit = true;
	_hit.count = 0;
	//_hit.knockCount = 0;
	_moving.gravity.x = info->knockBack;

	if (_state == ENEMY_STATE::IDLE || _state == ENEMY_STATE::MOVE)
	{
		_img = IMAGE_MANAGER->findImage(_imageName + "_Shot");
	}

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));

	return true;
}
