#include "stdafx.h"
#include "EnemyManager.h"
#include "BatNormal.h"

void BatNormal::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::MOVE);

	_position = pos;
	_direction = direction;
	_scale = 4;

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

void BatNormal::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatNormal::update(float const timeElapsed)
{
	// �÷��̾� ��ǥ���� ���l ����
	_direction = _enemyManager->getPlayerPos().x > _position.x ? DIRECTION::RIGHT : DIRECTION::LEFT;
	
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
			
			if (_moving.update(timeElapsed))
			{
				// ���̵� ���·� ����
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

void BatNormal::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, !(bool)_direction);
}

void BatNormal::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Normal/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
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
