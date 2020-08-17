#include "stdafx.h"
#include "EnemyManager.h"
#include "Ghost.h"

void Ghost::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	_size = _img->getFrameSize() * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	ZeroMemory(&_attacking, sizeof(_attacking));
	_attacking.delay = 3;

	ZeroMemory(&_moving, sizeof(_moving));
	//�����̴� ����
	//_moving.angle = RANDOM->getFromFloatTo(0, PI2);
	//���ư��� ����(�̵��ӵ�)     �������� -> 0~ 360 ������ ���� float ������ �����´�
	_moving.force = Vector2(150, 0);
	_moving.delay = 0.5;

	_isDetect = 0;
}

void Ghost::release()
{
}

void Ghost::update(float const timeElapsed)
{
	// �÷��̾� ������ �׻� ������
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}
	
	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			// �÷��̾� ������ ������
			if (_isDetect)
			{
				// ��� ������
				setState(ENEMY_STATE::MOVE);				
			}
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			if (_moving.update(timeElapsed))
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				_moving.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
			}
			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.force.x);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.force.x);

			setPosition(_position + moveDir);			

			if (_attacking.update(timeElapsed))
			{
				//_moving.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
				//_moving.force.x = 350;
				setState(ENEMY_STATE::ATTACK);
			}
		}
			break;
		case ENEMY_STATE::ATTACK:
		{
			moveDir.x += cosf(_moving.angle) * (timeElapsed * (_moving.force.x * 2.5f));
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * (_moving.force.x * 2.5f));

			setPosition(_position + moveDir);
			//_enemyManager->moveEnemy(this, moveDir);

			if (_attacking.update(timeElapsed * 3))
			{
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

void Ghost::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);

	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));	
}

// �̹��� �� ������ ����
void Ghost::setState(ENEMY_STATE state)
{
	_state = state;

	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();

			_img = IMAGE_MANAGER->findImage("Ghost/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();

		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();

			_img = IMAGE_MANAGER->findImage("Ghost/Attack");			
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();

		}
		break;
		case ENEMY_STATE::DIE:
		{
		}
		break;
	}
}
