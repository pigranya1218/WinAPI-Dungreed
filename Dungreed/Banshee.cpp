#include "stdafx.h"
#include "EnemyManager.h"
#include "Banshee.h"

void Banshee::init(const Vector2& pos, DIRECTION direction)
{	
	// 애니메이션 할당
	_ani = new Animation;

	// 초기 상태는 기본 상태
	setState(ENEMY_STATE::IDLE);

	// 변수 초기화
	_position = pos;
	_direction = direction;
	_scale = 4;
	_isDetect = 0;
	_detectRange = 300;

	// 피격 렉트 및 사이즈 초기화
	_size = _img->getFrameSize() * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	// 탄막 초기화
	_shooting.init("Banshee/Bullet", "Banshee/Bullet_FX", Vector2(500, 500), _scale, 3, 2.2, false, true, true, false, false, false);
	_shooting.attackInit(5, 10, 3);

	ZeroMemory(&_moving, sizeof(_moving));

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	_active = true;

	_curHp = _maxHp = 100;

	_myEnemyType = static_cast<int>(ENEMY_TYPE::BANSHEE);
}

void Banshee::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Banshee::update(float const timeElapsed)
{
	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				if (_shooting.delayUpdate(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);

					for (int i = 0; i < 12; i++)
					{
						_shooting.angle += PI / 6;
						_shooting.createBullet(_position, _shooting.angle);
					}
					_shooting.fireBullet(_myEnemyType, _enemyManager);
				}
			}
			break;
		}
		case ENEMY_STATE::ATTACK:
		{
			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::IDLE);
			}
			break;
		}
		case ENEMY_STATE::DIE:
		{

			break;
		}
	}
	hitReaction(_enemyManager->getPlayerPos(), moveDir, timeElapsed);

	_enemyManager->moveEnemy(this, moveDir, true, false);

	_ani->frameUpdate(timeElapsed);

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		setState(ENEMY_STATE::DIE);
	}
}

void Banshee::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 1);

	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}
}

void Banshee::setState(ENEMY_STATE state)
{
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_imageName = "Banshee/Idle";

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
			_imageName = "Banshee/Attack";

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

void Banshee::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				{
					_imageName = "Banshee/Idle";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Banshee/Attack";
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
