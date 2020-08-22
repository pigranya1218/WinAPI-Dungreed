#include "stdafx.h"
#include "EnemyManager.h"
#include "BatNormal.h"

#define DEFSPEED 200.0f	// �⺻ ���ǵ�

void BatNormal::init(const Vector2 & pos, DIRECTION direction, bool spawnEffect)
{
	_ani = new Animation;

	setState(ENEMY_STATE::MOVE);

	_position = pos;
	_direction = direction;
	_scale = 4;

	// ������ ����
	_size = Vector2(_img->getFrameSize().x - 20, _img->getFrameSize().y - 10);
	_size = _size * _scale;

	if (spawnEffect)
	{
		setState(ENEMY_STATE::ENTER);
	}

	// �̵� ���� ���� �ʱ�ȭ
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 3;
	_moving.force = Vector2(DEFSPEED, 0.0f);
	_moving.angle = RANDOM->getFromFloatTo(0, PI2);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;	

	_isDetect = 0;
	_active = true;
	_enterCount = 0;
	_curHp = _maxHp = 20;
}

void BatNormal::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void BatNormal::update(float const timeElapsed)
{
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	// �÷��̾� ��ǥ���� ���l ����
	_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
	
	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::ENTER:
		{


			if (!_ani->isPlay())
			{
				SOUND_MANAGER->stop("Enemy/Spawn");
				SOUND_MANAGER->play("Enemy/Spawn", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
				EFFECT_MANAGER->play("Enemy_Destroy", _position, IMAGE_MANAGER->findImage("Enemy_Destroy")->getFrameSize() * _scale);
				setState(ENEMY_STATE::MOVE);
			}
		}
		break;
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

			if (_moving.update(timeElapsed))
			{
				// ���̵� ���·� ����
				setState(ENEMY_STATE::IDLE);
			}
		}		
		break;
		case ENEMY_STATE::DIE:
		{
			SOUND_MANAGER->stop("Bat/Die");
		}
		break;
	}
	hitReaction(playerPos, moveDir, timeElapsed);
	
	_enemyManager->moveEnemy(this, moveDir, true, false);

	_ani->frameUpdate(timeElapsed);

	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		_enterCount = 0;
		SOUND_MANAGER->stop("Enemy/Spawn");
		SOUND_MANAGER->play("Bat/Die", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
		setState(ENEMY_STATE::DIE);
	}
}

void BatNormal::render()
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

void BatNormal::setState(ENEMY_STATE state)
{
	_state = state;

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
		case ENEMY_STATE::MOVE:
		{
			_imageName = "Bat/Normal/Move";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case ENEMY_STATE::DIE:
		{
			SOUND_MANAGER->stop("Bat/Die");
			_active = false;
		}
		break;
	}
}

void BatNormal::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
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
					_imageName = "Bat/Normal/Move";
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
