#include "stdafx.h"
#include "EnemyManager.h"
#include "BatRed.h"

#define DEFSPEED 250.0f

void BatRed::init(const Vector2& pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::MOVE);	

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	// ������ ����
	_size = Vector2(_img->getFrameSize().x - 20, _img->getFrameSize().y - 10);
	_size = _size * _scale;

	// �浹 ��Ʈ ����
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	// ���� ���� ���� �ʱ�ȭ
	

	// �̵� ���� ���� �ʱ�ȭ
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 3;
	_moving.force = Vector2(DEFSPEED, 0.0f);
	_moving.angle = RANDOM->getFromFloatTo(0, PI2);
	
	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	// �Ѿ� �ʱ�ȭ
	//_shooting.init("SmallBullet", "SmallBullet_FX", _scale, 1, 1, 500, false, true, true, true, false);

	_isDetect = 0;

	_active = true;

	_curHp = _maxHp = 100;
}

void BatRed::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatRed::update(float const timeElapsed)
{
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	// ������ ���ߴٸ�
	if (!_isDetect)
	{
		// �÷��̾� ��� Ȯ��
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}
	else
	{
		// �÷��̾� ��ǥ���� ���� ����
		_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
	}

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			// ���� �ֱ�� �̵�
			if (_moving.update(timeElapsed))
			{
				// ������ ����
				_moving.angle = RANDOM->getFromFloatTo(0, PI2);
				setState(ENEMY_STATE::MOVE);
			}
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			// �̵�
			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.force.x);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.force.x);

			// ���� �ֱ�� ����
			if (_isDetect)
			{
				if (_shooting.delayUpdate(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
					_shooting.bulletNum = 1;
				}
			}
			else
			{
				if (_moving.update(timeElapsed))
				{
					// ���̵� ���·� ����
					setState(ENEMY_STATE::IDLE);
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			// ���� ����� �� ����ü ���� �� �߻�
			if (_ani->getPlayIndex() == 5 && _shooting.bulletNum > 0)
			{
				float angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
				_shooting.createBullet(_position, angle);
				_shooting.fireBullet(_enemyManager);
			}
			if (!_ani->isPlay())
			{
				// ���� �Ϸ� �� IDLE ���·� ����
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

	_enemyManager->moveEnemy(this, moveDir);

	_ani->frameUpdate(timeElapsed);

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		setState(ENEMY_STATE::DIE);
	}
}

void BatRed::render()
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

void BatRed::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		case ENEMY_STATE::MOVE:
		{
			_imageName = "Bat/Red/Move";

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
			_imageName = "Bat/Red/Attack";

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

void BatRed::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
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
					_imageName = "Bat/Red/Move";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Bat/Red/Attack";
				}
				break;
			}
			_img = IMAGE_MANAGER->findImage(_imageName);
			_hit.isHit = false;
			_moving.force.x = DEFSPEED;
			return;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));
	}	
}
