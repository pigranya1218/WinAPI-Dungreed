#include "stdafx.h"
#include "EnemyManager.h"
#include "Minotaurs.h"

void Minotaurs::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	_size = Vector2(_img->getFrameSize().x - 15, _img->getFrameSize().y);
	_size = _size * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.speed = 1000;
	_moving.delay = 0.2;

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 2;
	_attack.distance = 100;

	ZeroMemory(&_skill, sizeof(_skill));
	_skill.delay = 1;
	_skill.distance = 500;

	_isDetect = _moving.jumpPower = 0;
	_moving.gravity = 1600;
}

void Minotaurs::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Minotaurs::update(float const timeElapsed)
{
	Vector2 playerPos = _enemyManager->getPlayerPos();

	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	// �̵��� ��ǥ ���� �ʱ�ȭ
	Vector2 moveDir(0, 0);

	// ���¿� ���� �ൿ ó��
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				// �÷��̾� ��ǥ ���� �¿� ����
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				// �÷��̾���� �Ÿ� ���
				float distance = getDistance(playerPos.x, playerPos.y, _position.x, _position.y);

				// �Ÿ��� �Ϲݰ��� �����Ÿ����� ª����
				if (distance < _attack.distance)
				{
					// ���� ������ ��� ��
					if (_attack.update(timeElapsed))
					{
						// ���� ���·� ��ȯ
						setState(ENEMY_STATE::ATTACK);
					}
				}
				else
				{
					// ��ų ������ ����
					if (_skill.update(timeElapsed))
					{
						// ���� ���·� ��ȯ
						setState(ENEMY_STATE::SKILL);
					}
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			// ������ ������
			if (!_ani->isPlay())
			{
				// �⺻ ���·� ��ȯ
				setState(ENEMY_STATE::IDLE);
			}
		}
		break;
		case ENEMY_STATE::SKILL:
		{
			// ���� ������
			if (_ani->getPlayIndex() == 4)
			{
				// �Ͻ� ����
				if(_ani->isPlay()) _ani->pause();

				moveDir.x += _moving.speed * timeElapsed * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

				// ���� X��� ���� X���� ������ ���� �ε��� ��
				if (_lastPos.x == _currPos.x)
				{
					_ani->resume();
				}
			}
			// ������ ������ ��
			if (!_ani->isPlay() && _ani->getPlayIndex() != 4)
			{
				// �÷��̾�� �Ÿ� ��� ��
				float distance = getDistance(playerPos.x, playerPos.y, _position.x, _position.y);

				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				// �Ϲ� ���� �����Ÿ��� ����������
				if (distance < _attack.distance)
				{
					// �ٷ� �Ϲݰ���
					setState(ENEMY_STATE::ATTACK);
				}
				else
				{
					// �⺻ ���·� ��ȯ
					setState(ENEMY_STATE::IDLE);
				}
			}
		}
		break;
		case ENEMY_STATE::DIE:
		{

		}
		break;
	}


	// �������� �߷� ����	
	_moving.jumpPower += _moving.gravity * timeElapsed;
	moveDir.y = 1.5 + _moving.jumpPower * timeElapsed;

	_lastPos = _position;
	_enemyManager->moveEnemy(this, moveDir);
	_currPos = _position;
	if (_isStand)
	{
		_moving.jumpPower = 0;
	}

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void Minotaurs::render()
{
	D2D_RENDERER->drawEllipse(_position, _detectRange);
	D2D_RENDERER->drawRectangle(_rect);

	_img->setScale(_scale);

	Vector2 drawPos = _position;
	if (_state != ENEMY_STATE::IDLE)
	{
		Image* img = IMAGE_MANAGER->findImage("Minotaurs/Idle");
		Vector2 elapsePos((_img->getFrameSize().x - img->getFrameSize().x) * _scale, (_img->getFrameSize().y - img->getFrameSize().y) * _scale);

		drawPos.x += ((_direction == DIRECTION::RIGHT) ? (elapsePos.x / 2 * 1) : (elapsePos.x / 2 * -1));
		drawPos.y -= elapsePos.y / 2;
	}
	_img->aniRender(drawPos, _ani, (_direction == DIRECTION::LEFT));
}

void Minotaurs::setState(ENEMY_STATE state)
{
	_state = state;

	// ���¿� ���� �ִϸ��̼� ����
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Minotaurs/Idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();
		}	
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Minotaurs/Attack");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(10);
			_ani->start();
		}
		break;
		case ENEMY_STATE::SKILL:
		{
			_img = IMAGE_MANAGER->findImage("Minotaurs/Skill");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(10);
			_ani->start();
		}
		break;
		case ENEMY_STATE::DIE:
		{
		}
		break;
	}
}
