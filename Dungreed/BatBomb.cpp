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

	// ������ ����
	_size = Vector2(_img->getFrameSize().x - 10, _img->getFrameSize().y);
	_size = _size * _scale;

	// �浹 ��Ʈ ����
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);	

	// �̵� ���� ���� �ʱ�ȭ
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 0.2;
	_moving.force = Vector2(500, 0);
	_moving.angle = 0;

	_isDetect = 0;
	_active = true;
}

void BatBomb::release()
{
	_ani->release();
	delete _ani;
}

void BatBomb::update(float const timeElapsed)
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
		// �÷��̾� ��ǥ���� ���l ����
		_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
	}

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
			// �̵�
			Vector2 moveDir(0, 0);
			if (_moving.update(timeElapsed))
			{
				_moving.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
			}

			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.force.x);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.force.x);	

			_enemyManager->moveEnemy(this, moveDir);

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
			EFFECT_MANAGER->play("Bat_Explosion", _position, Vector2(250, 250));
		}
		break;
	}

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void BatBomb::render()
{
	_img->setScale(_scale);

	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));
}

void BatBomb::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Bomb/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Bat/Bomb/Attack_Begin");
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
