#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelBigNormal.h"

void SkelBigNormal::init(const Vector2 & pos, DIRECTION direction)
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
	_moving.force = Vector2(150, 0);
	_moving.gravity = Vector2(0, 4000);
	_moving.delay = 0.2;

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 1.5f;
	_attack.distance = 100;	

	_isDetect =  0;
	_active = true;
}

void SkelBigNormal::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SkelBigNormal::update(float const timeElapsed)
{
	// 플레이어를 아직 감지 못했다면
	if (!_isDetect)
	{
		// 계속 감지
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	Vector2 moveDir(0, 0);
	// 상태에 따른 행동처리
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				setState(ENEMY_STATE::MOVE);
			}
			break;
		}
		case ENEMY_STATE::MOVE:
		{
			const Vector2 playerPos = _enemyManager->getPlayerPos();

			// 일정 주기로 방향 변경
			if (_moving.update(timeElapsed))
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);
			}

			// X축 설정
			moveDir.x += timeElapsed * _moving.force.x * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));
			// 거리 계산
			float distance = getDistance(playerPos.x, playerPos.y, _position.x, _position.y);
			// 플레이어와의 X축 거리 계산
			if (fabsf(_position.x - playerPos.x) < _size.x)
			{
				// 땅에 서있는 상태
				if (_isStand)
				{
					// 위에 있다면
					if (playerPos.y < (_position.y - _size.y * 1.3f))
					{
						_moving.force.y = -1400;
					}
					// 아래에 있다면
					else if (playerPos.y > (_position.y + _size.y * 0.5f))
					{
						_position.y += 1.5f;
						_moving.force.y = 0.1f;
					}
				}
			}
			if (distance < _attack.distance)
			{
				if (_attack.update(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
				}
			}
			break;
		}
		case ENEMY_STATE::ATTACK:
		{
			if (!_ani->isPlay())
			{
				setState(ENEMY_STATE::MOVE);
			}
			break;
		}
		case ENEMY_STATE::DIE:
		{
			break;
		}
	}

	if (_isStand && _moving.force.y == 0)
	{
		_position.y -= 15;
		moveDir.y += 17;
	}
	_moving.force.y += _moving.gravity.y * timeElapsed;
	moveDir.y += _moving.force.y * timeElapsed;

	// 이동할 포지션 최종
	_enemyManager->moveEnemy(this, moveDir);
	if (_isStand)
	{
		_moving.force.y = 0;
	}

	_ani->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void SkelBigNormal::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rect));
	D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_position), _detectRange);	

	Vector2 drawPos = _position;
	if (_state == ENEMY_STATE::ATTACK)
	{
		// 이동 이미지 기준으로
		Image* img = IMAGE_MANAGER->findImage("Skel/Big_Normal/Move");

		// 이미지 간의 사이즈 차이 구하고
		Vector2 elapsePos((_img->getFrameSize().x - img->getFrameSize().x) * _scale, (_img->getFrameSize().y - img->getFrameSize().y) * _scale);

		// 최종 출력 포지션 설정
		drawPos.x += (_direction == DIRECTION::RIGHT) ? +(elapsePos.x / 2) : -(elapsePos.x / 2);
		drawPos.y -= elapsePos.y / 2;
	}
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(drawPos), _ani, (_direction == DIRECTION::LEFT));
}

void SkelBigNormal::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Big_Normal/Idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Big_Normal/Move");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(10);
			_ani->start();
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Skel/Big_Normal/Attack");
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
