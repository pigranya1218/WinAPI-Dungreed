#include "stdafx.h"
#include "EnemyManager.h"
#include "Minotaurs.h"

#define RUSHSPEED 1000.0f

void Minotaurs::init(const Vector2 & pos, DIRECTION direction, bool spawnEffect)
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

	if (spawnEffect)
	{
		setState(ENEMY_STATE::ENTER);
	}

	// �̵� ���� ���� >> ���⼭�� ������ ���
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(RUSHSPEED, 0.0f);
	_moving.gravity = Vector2(10, 4000);

	// ���� ���� ����
	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay =	2.5;		// ���� ������ �ʱ�ȭ
	_attack.distance = 100;	// ���� ���� ���� �Ÿ�
	_attack.circleSize = 150;
	_attack.attackInit(5, 10, 15,0,0,25);

	// ���� ���� ����
	ZeroMemory(&_skill, sizeof(_skill));
	_skill.delay = 2.5;		// ���� ������ �ʱ�ȭ
	_skill.distance = 800;	// ���� ���� �� �ִ� �Ÿ�
	_skill.attackInit(2,3,5, 0, 0, 50);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;
	
	// ���� �ʱ�ȭ
	_isDetect = 0;				// �÷��̾� ���� �÷���
	_rushPos = Vector2(0, 0);	// ���� ���� ��ġ

	_active = true;

	_curHp = _maxHp = 90;
	_enterCount = 0;
	_myEnemyType = static_cast<int>(ENEMY_TYPE::MINOTAURS);
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
		case ENEMY_STATE::ENTER:
		{
			if (!_ani->isPlay())
			{
				SOUND_MANAGER->stop("Enemy/Spawn");
				SOUND_MANAGER->play("Enemy/Spawn", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

				EFFECT_MANAGER->play("Enemy_Destroy", _position, IMAGE_MANAGER->findImage("Enemy_Destroy")->getFrameSize() * _scale);
				setState(ENEMY_STATE::IDLE);
			}
		}
		break;
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
			// ���� ������
			if (_ani->getPlayIndex() == 3)
			{
				Vector2 attackPos = _position;
				attackPos.y += _size.y * 0.2f;

				float startRad = (_direction == DIRECTION::LEFT) ? (1.22) : (-PI / 6);
				float endRad = startRad + PI / 6 * 5;

				_attack.attackCircle(_myEnemyType, _enemyManager, Vector2(attackPos), startRad, endRad);
			}
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
				_moving.force.x -= _moving.gravity.x * timeElapsed;
				moveDir.x += (_moving.force.x) * timeElapsed * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

				//EFFECT_MANAGER->play("Minotaurs/Effect", Vector2(_position.x, _position.y), IMAGE_MANAGER->findImage("Minotaurs/Effect")->getFrameSize() * _scale);

				_skill.attackRect(_myEnemyType, _enemyManager, rectMakePivot(_position, _size, PIVOT::CENTER));

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
	hitReaction(playerPos, moveDir, timeElapsed);

	if (_state != ENEMY_STATE::ENTER)
	{
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
	}

	_ani->frameUpdate(timeElapsed);

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		_enterCount = 0;
		SOUND_MANAGER->stop("Enemy/Spawn");
		setState(ENEMY_STATE::DIE);
	}
}

void Minotaurs::render()
{
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

	if (_curHp < _maxHp)
	{
		// DEBUG TEST
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}

	_attack.circleDebug.render(true);
}

void Minotaurs::setState(ENEMY_STATE state)
{
	_state = state;

	// ���¿� ���� �ִϸ��̼� ����
	switch (state)
	{
		case ENEMY_STATE::ENTER:
		{
			_img = IMAGE_MANAGER->findImage("Enemy_Create");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setPlayFrame(14, 0, false, false);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::IDLE:
		{
			_imageName = "Minotaurs/Idle";

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
			_imageName = "Minotaurs/Attack";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();

			_attack.id.clear();
		}
		break;
		case ENEMY_STATE::SKILL:
		{
			_imageName = "Minotaurs/Skill";

			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();

			_skill.id.clear();
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
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				{
					_imageName = "Minotaurs/Idle";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					_imageName = "Minotaurs/Attack";
				}
				break;
				case ENEMY_STATE::SKILL:
				{
					_imageName = "Minotaurs/Skill";
				}
				break;
			}
			_img = IMAGE_MANAGER->findImage(_imageName);
			_hit.isHit = false;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));
	}
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
