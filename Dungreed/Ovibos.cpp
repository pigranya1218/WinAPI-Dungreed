#include "stdafx.h"
#include "EnemyManager.h"
#include "Ovibos.h"

#define RUSHSPEED 500.0f
#define GRAVITYX 600.0f

void Ovibos::init(const Vector2 & pos, DIRECTION direction, bool spawnEffect)
{
	_ani = new Animation;	

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_size = _img->getFrameSize() * _scale;

	if (spawnEffect)
	{
		setState(ENEMY_STATE::ENTER);
	}

	ZeroMemory(&_attacking, sizeof(_attacking));
	_attacking.attackInit(3, 8, 1,0,0,50);

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(RUSHSPEED, 0.0f);
	_moving.gravity = Vector2(GRAVITYX, 4000.0f);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3f;

	_active = true;

	_curHp = _maxHp = 60;
	_enterCount = 0;
	_myEnemyType = static_cast<int>(ENEMY_TYPE::OVIBOS);
}

void Ovibos::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Ovibos::update(float const timeElapsed)
{
	const Vector2 playerpos = _enemyManager->getPlayerPos();	

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

		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			if (_ani->getPlayIndex() == _img->getMaxFrameX() - 1)
			{
				switch (_direction)
				{
					case DIRECTION::LEFT:
					{
						if (_position.x < playerpos.x)
						{
							if (_ani->isPlay()) _ani->pause();
							_moving.force.x -= _moving.gravity.x * timeElapsed;
						}
					}
					break;
					case DIRECTION::RIGHT:
					{
						if (_position.x > playerpos.x)
						{
							if (_ani->isPlay()) _ani->pause();
							_moving.force.x -= _moving.gravity.x * timeElapsed;
						}
					}
					break;
				}
			}
			if (_ani->isPlay())
			{
				_attacking.attackRect(_myEnemyType, _enemyManager, rectMakePivot(_position, _size, PIVOT::CENTER));
			}

			moveDir.x += timeElapsed * _moving.force.x * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

			if (_moving.force.x < 0)
			{
				_moving.force.x = 0;
				setState(ENEMY_STATE::IDLE);			
			}
		}
		break;
	}
	hitReaction(playerpos, moveDir, timeElapsed);

	if (_state != ENEMY_STATE::ENTER)
	{
		if (_isStand && _moving.force.y == 0)
		{
			_position.y -= 15;
			moveDir.y += 25;
		}
		_moving.force.y += _moving.gravity.y * timeElapsed;
		moveDir.y += _moving.force.y * timeElapsed;

		Vector2 lastDir = _position;
		_enemyManager->moveEnemy(this, moveDir);
		Vector2 currDir = _position;

		if (_isStand)
		{
			_moving.force.y = 0;
		}
		if (lastDir.x == currDir.x && _state == ENEMY_STATE::ATTACK)
		{
			setState(ENEMY_STATE::IDLE);
		}
	}

	_ani->frameUpdate(timeElapsed);

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		_enterCount = 0;
		SOUND_MANAGER->stop("Enemy/Spawn");
		setState(ENEMY_STATE::DIE);
	}
}

void Ovibos::render()
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

void Ovibos::setState(ENEMY_STATE state)
{
	_state = state;

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
			_imageName = "Ovibos/Idle";

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
			_imageName = "Ovibos/Attack";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();

			_attacking.id.clear();
		}
		break;
		case ENEMY_STATE::DIE:
		{
			SOUND_MANAGER->stop("Enemy/Spawn");
			_active = false;
		}
		break;
	}
}

void Ovibos::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				{
					_imageName = "Ovibos/Idle";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Ovibos/Attack";
				}
				break;
			}
			_img = IMAGE_MANAGER->findImage(_imageName);
			_hit.isHit = false;
		}
		/*_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (1) : (-1));*/
	}
}

bool Ovibos::hitEffect(FloatCircle* circle, AttackInfo* info)
{
	if (_state == ENEMY_STATE::IDLE || !_ani->isPlay())
	{
		setState(ENEMY_STATE::ATTACK);
		_moving.force.x = RUSHSPEED;
	}

	_hit.isHit = true;
	_hit.count = 0;	

	_moving.gravity.x = GRAVITYX + info->knockBack;

	_img = IMAGE_MANAGER->findImage(_imageName + "_Shot");

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));	

	_direction = (_enemyManager->getPlayerPos().x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

	return true;
}

bool Ovibos::hitEffect(Projectile* projectile)
{
	if (_state == ENEMY_STATE::IDLE || !_ani->isPlay())
	{
		setState(ENEMY_STATE::ATTACK);
		_moving.force.x = RUSHSPEED;
	}

	AttackInfo* info = projectile->getAttackInfo();
	_hit.isHit = true;
	_hit.count = 0;

	_moving.gravity.x = GRAVITYX + info->knockBack;

	_img = IMAGE_MANAGER->findImage(_imageName + "_Shot");

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));	

	_direction = (_enemyManager->getPlayerPos().x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

	return false;
}
