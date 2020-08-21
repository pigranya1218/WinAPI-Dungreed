#include "stdafx.h"
#include "EnemyManager.h"
#include "Ghost.h"

void Ghost::init(const Vector2 & pos, DIRECTION direction)
{
	// �ִϸ��̼� �Ҵ�
	_ani = new Animation;

	// ó�� ���´� �⺻
	setState(ENEMY_STATE::IDLE);

	// ���� �ʱ�ȭ
	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	// Ÿ�� ������ �ʱ�ȭ
	_size = _img->getFrameSize() * _scale;

	// ���� ���� ���� �ʱ�ȭ
	ZeroMemory(&_attacking, sizeof(_attacking));
	_attacking.delay = 3;
	_attacking.attackInit(3, 5, 1);

	// �̵� ���� ���� �ʱ�ȭ
	ZeroMemory(&_moving, sizeof(_moving));	
	_moving.force = Vector2(100, 0);
	_moving.delay = 0.5;

	// �ǰ� ���� ���� �ʱ�ȭ
	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3f;

	// ���� �ʱ�ȭ
	_isDetect = 0;
	_active = true;

	// ü�� �ʱ�ȭ
	_curHp = _maxHp = MAXHP;

	// ���ʹ� Ÿ�Ժ��� �ʱ�ȭ
	_myEnemyType = static_cast<int>(ENEMY_TYPE::GHOST);
}

void Ghost::release()
{
	// �޸� ����
	_ani->release();
	SAFE_DELETE(_ani);
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
			// ���� �ֱ⸶�� �÷��̾� ��ǥ Ȯ�� �� ���� ����
			if (_moving.update(timeElapsed))
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				_moving.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
			}
			// �̵���ǥ
			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.force.x);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.force.x);

			// ���� ��Ÿ�� �Ϸ�
			if (_attacking.update(timeElapsed))
			{				
				// ���� ����
				setState(ENEMY_STATE::ATTACK);
			}
		}
			break;
		case ENEMY_STATE::ATTACK:
		{
			// ���� �߿��� �� ���� ������
			moveDir.x += cosf(_moving.angle) * (timeElapsed * (_moving.force.x * 2.5f));
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * (_moving.force.x * 2.5f));			

			// ���� �߿� ���� ��Ʈ ����
			_attacking.attackRect(_myEnemyType, _enemyManager, rectMakePivot(_position, _size, PIVOT::CENTER));

			// ���� ��Ÿ�� ����
			if (_attacking.update(timeElapsed * 3))
			{
				// �⺻ ���·� ����
				setState(ENEMY_STATE::IDLE);
			}
		}
		break;
		case ENEMY_STATE::DIE:
		{
		
		}
		break;
	}
	// �ǰ� ���׼�
	hitReaction(playerPos, moveDir, timeElapsed);

	// ���ʹ� ��ǥ �̵�
	_enemyManager->moveEnemy(this, moveDir, false, false);

	// ������ ������Ʈ
	_ani->frameUpdate(timeElapsed);

	// �������� ü�� Ȯ��
	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		setState(ENEMY_STATE::DIE);
	}
}

void Ghost::render()
{
	// �̹��� ������ ���� �� ���
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));	

	// �� ��� ������ ü�����
	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}
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
			_imageName = "Ghost/Move";

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
			_imageName = "Ghost/Attack";

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
			_active = false;
		}
		break;
	}
}

void Ghost::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	// �ǰ� ������ �Ǿ��ٸ�
	if (_hit.isHit)
	{
		// �ǰ� ��Ÿ���� ������
		if (_hit.update(timeElapsed))
		{
			// ���¿� ����
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				case ENEMY_STATE::MOVE:
				{
					_imageName = "Ghost/Move";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Ghost/Attack";
				}
				break;
			}
			// �̹��� �ʱ�ȭ
			_img = IMAGE_MANAGER->findImage(_imageName);
			// �ǰ� ���� ���� �ʱ�ȭ
			_hit.isHit = false;
			_moving.force.x = 100;
			return;
		}
		// �˹��̱� �ѵ� ���� �̻���
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));
	}	
}
