#include "stdafx.h"
#include "EnemyManager.h"
#include "Minotaurs.h"

#define RUSHSPEED 1000.0f

void Minotaurs::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 200;		// �÷��̾� ���� �Ÿ�

	// �ǰ� ��Ʈ �� ������ 
	_size = Vector2(_img->getFrameSize().x - 15, _img->getFrameSize().y);
	_size = _size * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	// �̵� ���� ���� >> ���⼭�� ������ ���
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(RUSHSPEED, 0.0f);
	_moving.gravity = Vector2(10, 4000);

	// ���� ���� ����
	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay =	2;		// ���� ������ �ʱ�ȭ
	_attack.distance = 100;	// ���� ���� ���� �Ÿ�

	// ���� ���� ����
	ZeroMemory(&_skill, sizeof(_skill));
	_skill.delay = 1;		// ���� ������ �ʱ�ȭ
	_skill.distance = 800;	// ���� ���� �� �ִ� �Ÿ�
	
	// ���� �ʱ�ȭ
	_isDetect = 0;				// �÷��̾� ���� �÷���
	_rushPos = Vector2(0, 0);	// ���� ���� ��ġ

	_active = true;
}

void Minotaurs::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Minotaurs::update(float const timeElapsed)
{
	// �÷��̾� ��ǥ�� �׻� �޾ƿ�
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	// ���� �÷��̾� ������ ���ߴٸ�
	if (!_isDetect)
	{
		// �÷��̾� ���� ��� ����
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

				// �Ÿ��� �Ϲݰ��� �����Ÿ��ȿ� ���� ������
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
						_rushPos = _position;
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
			// ���� ���� ��� ������ ����
			if (_ani->getPlayIndex() == 4)
			{
				// �Ͻ� ����
				if(_ani->isPlay()) _ani->pause();

				// �����Ѵ�
				_moving.force.x -= _moving.gravity.x;
				moveDir.x += (_moving.force.x) * timeElapsed * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

				EFFECT_MANAGER->play("Minotaurs/Effect", Vector2(_position.x, _position.y), IMAGE_MANAGER->findImage("Minotaurs/Effect")->getFrameSize() * _scale);

				// ���� X��� ���� X���� ������ ���� �ε��� ��
				if (_lastPos.x == _currPos.x)
				{
					_ani->resume();
				}
				// ���� ���� ������ ��
				else if (_moving.force.x < 0)
				{
					_ani->resume();
				}
				// ���� �����Ÿ� �� ������
				else if (getDistance(_rushPos.x, _rushPos.y, _position.x, _position.y) > _skill.distance)
				{
					_ani->resume();
				}
				// �÷��̾�� �浹
				else if (playerCollision(playerPos))
				{
					_ani->resume();
				}
			}
			// ������ ������ ��
			if (!_ani->isPlay() && _ani->getPlayIndex() != 4)
			{
				_moving.force.x = RUSHSPEED;

				//_moving.gravity.x = 0;

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
	if (_isStand && _moving.force.y == 0)
	{
		_position.y -= 15;
		moveDir.y += 25;
	}

	_moving.force.y += _moving.gravity.y * timeElapsed;
	moveDir.y += _moving.force.y * timeElapsed;

	_lastPos = _position;
	_enemyManager->moveEnemy(this, moveDir);
	_currPos = _position;

	if (_isStand)
	{
		_moving.force.y = 0;
	}

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void Minotaurs::render()
{
	// �����
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);	// �νİŸ�
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));					// �ǰ� �� �浹 ��Ʈ

	// ������ ����
	_img->setScale(_scale);

	// ���� ������ ����
	Vector2 drawPos = _position;
	// �⺻ ���°� �ƴ� ��쿡
	if (_state != ENEMY_STATE::IDLE)
	{
		// �⺻ �̹����� ��������
		Image* img = IMAGE_MANAGER->findImage("Minotaurs/Idle");
		// ������ ���̸� ���Ѵ�
		Vector2 elapsePos((_img->getFrameSize().x - img->getFrameSize().x) * _scale, (_img->getFrameSize().y - img->getFrameSize().y) * _scale);
		// ���� ���̸�ŭ ���� ������ ����
		drawPos.x += elapsePos.x / 2 * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));
		drawPos.y -= elapsePos.y / 2;
	}
	// ���� ����
	_img->aniRender(CAMERA->getRelativeV2(drawPos), _ani, (_direction == DIRECTION::LEFT));
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
			_active = false;
		}
		break;
	}
}

void Minotaurs::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
}

bool Minotaurs::hitEffect(FloatRect * rc, AttackInfo * info)
{
	return false;
}

bool Minotaurs::hitEffect(FloatCircle * circle, AttackInfo * info)
{
	_hit.isHit = true;
	_hit.hitCount = 0;
	//_hit.knockCount = 0;
	_moving.gravity.x = info->knockBack;

	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			_img = IMAGE_MANAGER->findImage("Minotaurs/Idle_Shot");
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_img = IMAGE_MANAGER->findImage("Minotaurs/Attack_Shot");
		}
		break;
		case ENEMY_STATE::SKILL:
		{
			_img = IMAGE_MANAGER->findImage("Minotaurs/Skill_Shot");
		}
		break;
	}

	return false;
}

bool Minotaurs::hitEffect(Projectile * projectile, AttackInfo * info)
{
	return false;
}

bool Minotaurs::playerCollision(const Vector2& playerPos)
{
	if (_rect.left <= playerPos.x && playerPos.x <= _rect.right &&
		_rect.top <= playerPos.y && playerPos.y <= _rect.bottom)
	{
		return true;
	}

	return false;
}
