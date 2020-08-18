#include "stdafx.h"
#include "EnemyManager.h"
#include "BatRed.h"

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
	_moving.force = Vector2(250, 0);
	_moving.angle = RANDOM->getFromFloatTo(0, PI2);

	// �Ѿ� �ʱ�ȭ
	_shooting.init("SmallBullet", "SmallBullet_FX", _scale, 1, 1, 500, false, true, true, true, false);

	_isDetect = 0;

	_active = true;
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
			Vector2 moveDir(0, 0);

			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.force.x);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.force.x);

			_enemyManager->moveEnemy(this, moveDir);

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

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void BatRed::render()
{
	_img->setScale(_scale);

	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));
}

void BatRed::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Red/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}		
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Red/Attack");
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
