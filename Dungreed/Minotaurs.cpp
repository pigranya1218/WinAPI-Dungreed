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
	_detectRange = 200;		// 플레이어 감지 거리

	// 피격 렉트 및 사이즈 
	_size = Vector2(_img->getFrameSize().x - 15, _img->getFrameSize().y);
	_size = _size * _scale;

	if (spawnEffect)
	{
		setState(ENEMY_STATE::ENTER);
	}

	// 이동 관련 변수 >> 여기서는 돌진에 사용
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(RUSHSPEED, 0.0f);
	_moving.gravity = Vector2(10, 4000);

	// 공격 관련 변수
	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay =	2.5;		// 공격 딜레이 초기화
	_attack.distance = 100;	// 공격 시전 가능 거리
	_attack.circleSize = 150;
	_attack.attackInit(5, 10, 15,0,0,25);

	// 돌진 관련 변수
	ZeroMemory(&_skill, sizeof(_skill));
	_skill.delay = 2.5;		// 돌진 딜레이 초기화
	_skill.distance = 800;	// 돌진 시전 시 최대 거리
	_skill.attackInit(2,3,5, 0, 0, 50);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;
	
	// 변수 초기화
	_isDetect = 0;				// 플레이어 감지 플래그
	_rushPos = Vector2(0, 0);	// 돌진 시작 위치

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
	// 플레이어 좌표는 항상 받아옴
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	// 아직 플레이어 감지를 못했다면
	if (!_isDetect)
	{
		// 플레이어 감지 계속 실행
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	// 이동할 좌표 변수 초기화
	Vector2 moveDir(0, 0);

	// 상태에 따른 행동 처리
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
				// 플레이어 좌표 따라서 좌우 설정
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				// 플레이어와의 거리 계산
				float distance = getDistance(playerPos.x, playerPos.y, _position.x, _position.y);

				// 거리가 일반공격 사정거리안에 들어와 있으면
				if (distance < _attack.distance)
				{
					// 공격 딜레이 계산 후
					if (_attack.update(timeElapsed))
					{
						// 공격 상태로 전환
						setState(ENEMY_STATE::ATTACK);
					}
				}
				else
				{
					// 스킬 딜레이 계산용
					if (_skill.update(timeElapsed))
					{
						// 돌진 상태로 전환
						setState(ENEMY_STATE::SKILL);
						_rushPos = _position;
					}
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			// 공격 프레임
			if (_ani->getPlayIndex() == 3)
			{
				Vector2 attackPos = _position;
				attackPos.y += _size.y * 0.2f;

				float startRad = (_direction == DIRECTION::LEFT) ? (1.22) : (-PI / 6);
				float endRad = startRad + PI / 6 * 5;

				_attack.attackCircle(_myEnemyType, _enemyManager, Vector2(attackPos), startRad, endRad);
			}
			// 공격이 끝나면
			if (!_ani->isPlay())
			{
				// 기본 상태로 전환
				setState(ENEMY_STATE::IDLE);
			}
		}
		break;
		case ENEMY_STATE::SKILL:
		{
			// 돌진 공격 모션 프레임 고정
			if (_ani->getPlayIndex() == 4)
			{
				// 일시 정지
				if(_ani->isPlay()) _ani->pause();

				// 돌진한다
				_moving.force.x -= _moving.gravity.x * timeElapsed;
				moveDir.x += (_moving.force.x) * timeElapsed * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));

				//EFFECT_MANAGER->play("Minotaurs/Effect", Vector2(_position.x, _position.y), IMAGE_MANAGER->findImage("Minotaurs/Effect")->getFrameSize() * _scale);

				_skill.attackRect(_myEnemyType, _enemyManager, rectMakePivot(_position, _size, PIVOT::CENTER));

				// 이전 X축과 현재 X축이 같으면 벽에 부딪힌 것
				if (_lastPos.x == _currPos.x)
				{
					_ani->resume();
				}
				// 돌진 힘이 끝났을 때
				else if (_moving.force.x < 0)
				{
					_ani->resume();
				}
				// 돌진 사정거리 가 지나면
				else if (getDistance(_rushPos.x, _rushPos.y, _position.x, _position.y) > _skill.distance)
				{
					_ani->resume();
				}
				// 플레이어와 충돌
				else if (playerCollision(playerPos))
				{
					_ani->resume();
				}
			}
			// 돌진이 끝났을 때
			if (!_ani->isPlay() && _ani->getPlayIndex() != 4)
			{
				_moving.force.x = RUSHSPEED;

				// 플레이어와 거리 계산 후
				float distance = getDistance(playerPos.x, playerPos.y, _position.x, _position.y);

				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				// 일반 공격 사정거리에 들어와있으면
				if (distance < _attack.distance)
				{
					// 바로 일반공격
					setState(ENEMY_STATE::ATTACK);
				}
				else
				{
					// 기본 상태로 전환
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
		// 마지막에 중력 적용	
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
	// 스케일 설정
	_img->setScale(_scale);

	// 렌더 포지션 설정
	Vector2 drawPos = _position;
	// 기본 상태가 아닌 경우에
	if (_state != ENEMY_STATE::IDLE)
	{
		// 기본 이미지를 가져오고
		Image* img = IMAGE_MANAGER->findImage("Minotaurs/Idle");
		// 사이즈 차이를 구한다
		Vector2 elapsePos((_img->getFrameSize().x - img->getFrameSize().x) * _scale, (_img->getFrameSize().y - img->getFrameSize().y) * _scale);
		// 구한 차이만큼 렌더 포지션 수정
		drawPos.x += elapsePos.x / 2 * ((_direction == DIRECTION::RIGHT) ? (1) : (-1));
		drawPos.y -= elapsePos.y / 2;
	}
	// 최종 렌더
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

	// 상태에 따른 애니메이션 설정
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
