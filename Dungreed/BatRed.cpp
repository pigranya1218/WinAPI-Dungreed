#include "stdafx.h"
#include "EnemyManager.h"
#include "BatRed.h"

void BatRed::init(const Vector2& pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::MOVE);	

	_position = pos;
	_direction = direction;
	_scale = 3;
	_detectRange = 100;

	// ���� ���� ���� �ʱ�ȭ
	ZeroMemory(&_shooting, sizeof(_shooting));
	_shooting.delay = 3;

	// �̵� ���� ���� �ʱ�ȭ
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 3;
	_moving.speed = 350;
	_moving.angle = RANDOM->getFromFloatTo(0, PI2);

	// ������ ����
	_size = Vector2(_img->getFrameSize().x - 20, _img->getFrameSize().y - 10);
	_size = _size * _scale;

	// �浹 ��Ʈ ����
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	_isDetect = 0;
}

void BatRed::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatRed::update(float const timeElapsed)
{
	// �÷��̾� ��ǥ���� ���l ����
	_direction = _enemyManager->getPlayerPos().x > _position.x ? DIRECTION::RIGHT : DIRECTION::LEFT;

	// ������ ���ߴٸ�
	if (!_isDetect)
	{
		// �÷��̾� ��� Ȯ��
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
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

			break;
		}
		case ENEMY_STATE::MOVE:
		{
			// �̵�
			Vector2 moveDir(0, 0);

			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.speed);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.speed);

			//moveDir.x += cosf(_moving.angle);
			//moveDir.y -= sinf(_moving.angle);
			//moveDir = moveDir * (timeElapsed * _moving.speed);

			_enemyManager->moveEnemy(this, moveDir);

			// ���� �ֱ�� ����
			if (_isDetect)
			{
				if (_shooting.update(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
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

			break;
		}
		case ENEMY_STATE::ATTACK:
		{
			if (!_ani->isPlay())
			{
				// ���� �Ϸ� �� IDLE ���·� ����
				setState(ENEMY_STATE::IDLE);
			}
			break;
		}
		case ENEMY_STATE::DIE:
		{
			break;
		}		
	}

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void BatRed::render()
{
	_img->setScale(_scale);

	D2D_RENDERER->drawRectangle(_rect);
	D2D_RENDERER->drawEllipse(_position, _detectRange);
	_img->aniRender(_position, _ani, !(unsigned)_direction);
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
			_ani->setFPS(10);
			_ani->start();

			break;
		}		
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Red/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(10);
			_ani->start();

			break;
		}
		case ENEMY_STATE::DIE:
		{
			break;
		}
	}
}
