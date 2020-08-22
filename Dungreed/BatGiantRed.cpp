#include "stdafx.h"
#include "EnemyManager.h"
#include "BatGiantRed.h"

void BatGiantRed::init(const Vector2 & pos, DIRECTION direction, bool spawnEffect)
{
	_ani = new Animation;

	_countPlay = 0;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 100;

	_size = Vector2(_img->getFrameSize().x - 35, _img->getFrameSize().y - 15);
	_size = _size * _scale;

	if (spawnEffect)
	{
		setState(ENEMY_STATE::ENTER);
	}	

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 3;

	ZeroMemory(&_moving, sizeof(_moving));

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	// 투사체 초기화
	_shooting.init("GiantBullet", "GiantBullet_FX", Vector2(500, 500), _scale, 0.02f, 1.5f, false, true, true, false, true, false);
	_shooting.attackInit(1, 1, 8);
	
	_isDetect = 0;
	_detectRange = 300;
	_renderNum = -1;
	_active = true;

	_curHp = _maxHp =45;
	_enterCount = 0;
	_myEnemyType = static_cast<int>(ENEMY_TYPE::BAT_GIANT_RED);
}

void BatGiantRed::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatGiantRed::update(float const timeElapsed)
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
			SOUND_MANAGER->stop("GiantBat/Attack");
			if (_isDetect)
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				if (_attack.update(timeElapsed) && _shooting.bullets.empty())
				{
					_shooting.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);

					_shooting.bulletNum = 20;

					for (int i = 0; i < 20; i++)
					{
						Vector2 bulletPos = _position;
						bulletPos.x += cosf(PI2 / 20 * i) * (_size.x + 10);
						bulletPos.y -= sinf(PI2 / 20 * i) * (_size.x + 10);

						_shooting.createBullet(bulletPos, _shooting.angle);
					}
				}
				if (!_shooting.bullets.empty())
				{
					if (_shooting.delayUpdate(timeElapsed) && _renderNum < 20)
					{
						_renderNum++;
						if (_renderNum >= 20) setState(ENEMY_STATE::ATTACK);
					}
				}				
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{			
			if (_ani->getPlayIndex() == 4)
			{
				_countPlay++;
				if (_countPlay == 1)
				{
					SOUND_MANAGER->stop("GiantBat/Attack");
					SOUND_MANAGER->play("GiantBat/Attack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
				}
				_shooting.fireBullet(_myEnemyType, _enemyManager);
				_renderNum = -1;
			}
			if (!_ani->isPlay())
			{
				_countPlay = 0;
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
	_shooting.aniUpdate(timeElapsed);

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		_enterCount = 0;
		SOUND_MANAGER->stop("Enemy/Spawn");
		SOUND_MANAGER->stop("GiantBat/Attack");
		setState(ENEMY_STATE::DIE);
	}
}

void BatGiantRed::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	if (_renderNum >= 0)
	{
		_shooting.render(_renderNum);
	}	

	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}
}

void BatGiantRed::setState(ENEMY_STATE state)
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
		{
			_imageName = "Bat/Giant_Red/Idle";

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
			_imageName = "Bat/Giant_Red/Attack";

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

	_state = state;
}

void BatGiantRed::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				{
					_imageName = "Bat/Giant_Red/Idle";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Bat/Giant_Red/Attack";
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
