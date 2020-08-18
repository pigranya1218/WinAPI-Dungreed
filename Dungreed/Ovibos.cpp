#include "stdafx.h"
#include "EnemyManager.h"
#include "Ovibos.h"

#define RUSHSPEED 1200.0f

void Ovibos::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;	

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_size = _img->getFrameSize() * _scale;
	_rect = rectMakePivot(_position,_size,PIVOT::CENTER);

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(RUSHSPEED, 0.0f);
	_moving.gravity = Vector2(50, 4000);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3f;

	_active = true;

	_curHp = _maxHp = 100;
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
		case ENEMY_STATE::IDLE:
		{

		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			switch (_direction)
			{
				case DIRECTION::LEFT:
				{
					if (_position.x < playerpos.x)
					{
						if (_ani->getPlayIndex() == _img->getMaxFrameX() - 1)
						{
							if (_ani->isPlay()) _ani->pause();

							_moving.force.x -= _moving.gravity.x;
						}
					}
				}
				break;
				case DIRECTION::RIGHT:
				{
					if (_position.x > playerpos.x)
					{
						if (_ani->getPlayIndex() == _img->getMaxFrameX() - 1)
						{
							if (_ani->isPlay()) _ani->pause();

							_moving.force.x -= _moving.gravity.x;
						}
					}
				}
				break;
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

	if (_isStand && _moving.force.y == 0)
	{
		_position.y -= 15;
		moveDir.y += 25;
	}
	_moving.force.y += _moving.gravity.y * timeElapsed;
	moveDir.y += _moving.force.y * timeElapsed;

	_enemyManager->moveEnemy(this, moveDir);

	if (_isStand)
	{
		_moving.force.y = 0;
	}

	_ani->frameUpdate(timeElapsed);
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
		}
		break;
		case ENEMY_STATE::DIE:
		{
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
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (1) : (-1));
	}
}

bool Ovibos::hitEffect(FloatCircle* circle, AttackInfo* info)
{
	_hit.isHit = true;
	_hit.count = 0;	

	_moving.gravity.x = info->knockBack;

	_img = IMAGE_MANAGER->findImage(_imageName + "_Shot");

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));

	setState(ENEMY_STATE::ATTACK);

	_direction = (_enemyManager->getPlayerPos().x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

	return true;
}

bool Ovibos::hitEffect(Projectile* projectile)
{
	AttackInfo* info = projectile->getAttackInfo();
	_hit.isHit = true;
	_hit.count = 0;

	_moving.gravity.x = info->knockBack;

	_img = IMAGE_MANAGER->findImage(_imageName + "_Shot");

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));

	setState(ENEMY_STATE::ATTACK);

	_direction = (_enemyManager->getPlayerPos().x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

	return false;
}
