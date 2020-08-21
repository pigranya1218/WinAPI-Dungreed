#include "stdafx.h"
#include "EnemyManager.h"
#include "Ghost.h"

void Ghost::init(const Vector2 & pos, DIRECTION direction)
{
	// 애니메이션 할당
	_ani = new Animation;

	// 처음 상태는 기본
	setState(ENEMY_STATE::IDLE);

	// 변수 초기화
	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	// 타격 사이즈 초기화
	_size = _img->getFrameSize() * _scale;

	// 공격 관련 변수 초기화
	ZeroMemory(&_attacking, sizeof(_attacking));
	_attacking.delay = 3;
	_attacking.attackInit(3, 5, 1);

	// 이동 관련 변수 초기화
	ZeroMemory(&_moving, sizeof(_moving));	
	_moving.force = Vector2(100, 0);
	_moving.delay = 0.5;

	// 피격 관련 변수 초기화
	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3f;

	// 변수 초기화
	_isDetect = 0;
	_active = true;

	// 체력 초기화
	_curHp = _maxHp = MAXHP;

	// 에너미 타입변수 초기화
	_myEnemyType = static_cast<int>(ENEMY_TYPE::GHOST);
}

void Ghost::release()
{
	// 메모리 해제
	_ani->release();
	SAFE_DELETE(_ani);
}

void Ghost::update(float const timeElapsed)
{
	// 플레이어 포지션 항상 가져옴
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
			// 플레이어 감지를 했으면
			if (_isDetect)
			{
				// 계속 움직임
				setState(ENEMY_STATE::MOVE);				
			}
		}
		break;
		case ENEMY_STATE::MOVE:
		{
			// 일정 주기마다 플레이어 좌표 확인 후 방향 변경
			if (_moving.update(timeElapsed))
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				_moving.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
			}
			// 이동좌표
			moveDir.x += cosf(_moving.angle) * (timeElapsed * _moving.force.x);
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * _moving.force.x);

			// 공격 쿨타임 완료
			if (_attacking.update(timeElapsed))
			{				
				// 공격 시작
				setState(ENEMY_STATE::ATTACK);
			}
		}
			break;
		case ENEMY_STATE::ATTACK:
		{
			// 공격 중에는 더 빨리 움직임
			moveDir.x += cosf(_moving.angle) * (timeElapsed * (_moving.force.x * 2.5f));
			moveDir.y -= sinf(_moving.angle) * (timeElapsed * (_moving.force.x * 2.5f));			

			// 공격 중에 어택 렉트 생성
			_attacking.attackRect(_myEnemyType, _enemyManager, rectMakePivot(_position, _size, PIVOT::CENTER));

			// 공격 쿨타임 종료
			if (_attacking.update(timeElapsed * 3))
			{
				// 기본 상태로 변경
				setState(ENEMY_STATE::IDLE);
			}
		}
		break;
		case ENEMY_STATE::DIE:
		{
		
		}
		break;
	}
	// 피격 리액션
	hitReaction(playerPos, moveDir, timeElapsed);

	// 에너미 좌표 이동
	_enemyManager->moveEnemy(this, moveDir, false, false);

	// 프레임 업데이트
	_ani->frameUpdate(timeElapsed);

	// 마지막에 체력 확인
	if (max(0, _curHp) <= 0 && _state != ENEMY_STATE::DIE)
	{
		setState(ENEMY_STATE::DIE);
	}
}

void Ghost::render()
{
	// 이미지 스케일 설정 및 출력
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));	

	// 한 대라도 맞으면 체력출력
	if (_curHp < _maxHp)
	{
		Vector2 renderPos = _position;
		renderPos.y += _size.y * 0.6f;
		_enemyManager->showEnemyHp(_maxHp, _curHp, renderPos);
	}
}

// 이미지 및 프레임 설정
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
	// 피격 판정이 되었다면
	if (_hit.isHit)
	{
		// 피격 쿨타임이 끝나면
		if (_hit.update(timeElapsed))
		{
			// 상태에 따라서
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
			// 이미지 초기화
			_img = IMAGE_MANAGER->findImage(_imageName);
			// 피격 판정 변수 초기화
			_hit.isHit = false;
			_moving.force.x = 100;
			return;
		}
		// 넉백이긴 한데 뭔가 이상함
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (-1) : (1));
	}	
}
