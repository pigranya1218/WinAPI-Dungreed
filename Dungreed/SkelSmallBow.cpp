//#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelSmallBow.h"

void SkelSmallBow::init(const Vector2 & pos, DIRECTION direction)
{
	// 애니메이션 할당
	_ani = new Animation;
	_weaponAni = new Animation;

	// 손 이미지 
	_handImg = IMAGE_MANAGER->findImage("Skel/Small/Hand");

	// 활 공격 이미지 초기화
	_weaponImg = IMAGE_MANAGER->findImage("Skel/Small/Bow");
	_weaponAni->init(_weaponImg->getWidth(), _weaponImg->getHeight(), _weaponImg->getMaxFrameX(), _weaponImg->getMaxFrameY());
	_weaponAni->setDefPlayFrame(false, false);
	_weaponAni->setFPS(10);
	_weaponAni->stop();

	// 상태 초기화
	setState(ENEMY_STATE::IDLE);

	// 에너미 관련 변수 초기화
	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	// 충돌 사이즈 및 렉트 초기화
	_size = Vector2(_img->getFrameSize().x, _img->getFrameSize().y);
	_size = _size * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	// 공격 관련 초기화
	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 3;
	_attack.angle = (_direction == DIRECTION::LEFT) ? (PI) : (0);

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.gravity = Vector2(0, 4000);

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.hitDelay = 0.3;

	_shooting.init("Arrow00", "ArrowHitEffect", _scale, 1.5, 400, 500, true, true, false, false);

	// 플레이어 감지 변수 초기화
	_isDetect = 0;

	_active = true;
}

void SkelSmallBow::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SkelSmallBow::update(float const timeElapsed)
{
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
			if (_isDetect)
			{
				_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

				_attack.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y);
				if (_attack.angle > 360) _attack.angle -= 360;

				if (_attack.update(timeElapsed))
				{
					_shooting.createBullet(_position, _attack.angle);
					setState(ENEMY_STATE::ATTACK);
				}
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			if (_weaponAni->getPlayIndex() == 3 && !_shooting.bullets.empty())
			{
				if (_weaponAni->isPlay())
				{
					_weaponAni->pause();
				}
				if (_shooting.delayUpdate(timeElapsed))
				{
					_weaponAni->resume();
					_shooting.fireBullet(_enemyManager);
				}
			}
			if (!_weaponAni->isPlay() && _shooting.bullets.empty())
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
	hitReaction(playerPos, moveDir, timeElapsed);

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

	_weaponAni->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void SkelSmallBow::render()
{
	_img->setScale(_scale);
	_handImg->setScale(_scale);
	_handImg->setAngle(_attack.angle * (180 / PI));
	_weaponImg->setScale(_scale);

	_img->render(CAMERA->getRelativeV2(_position), (_direction == DIRECTION::LEFT));

	// 활 시위 당기는 손 좌표 설정
	Vector2 handPos = _position;
	handPos.x += cosf(_attack.angle) * 15;
	handPos.y -= sinf(_attack.angle) * 20;

	// 무기 좌표 설정
	Vector2 weaponPos = handPos;
	weaponPos.x += cosf(_attack.angle) * 9;
	weaponPos.y -= sinf(_attack.angle) * 9;
	_weaponImg->setAngle(_attack.angle * (180 / PI));
	_weaponImg->aniRender(CAMERA->getRelativeV2(weaponPos), _weaponAni);

	// 활 시위 당기는 프레임에 따라 손 좌표도 수정
	if (_weaponAni->getPlayIndex() <= 3)
	{
		handPos.x += cosf(_attack.angle) * (_weaponAni->getPlayIndex() * ((_direction == DIRECTION::LEFT) ? (5) : (-5)));
		handPos.y -= sinf(_attack.angle) * (_weaponAni->getPlayIndex() * ((_direction == DIRECTION::LEFT) ? (5) : (-5)));
	}
	_handImg->render(CAMERA->getRelativeV2(handPos));	// 손 출력

	// 고정되는 손 좌표 설정
	handPos = _position;
	_handImg->setScale(_scale);
	_handImg->setAngle(_attack.angle * (180 / PI));
	handPos.x += cosf(_attack.angle) * 35;
	handPos.y -= sinf(_attack.angle) * 40;
	_handImg->render(CAMERA->getRelativeV2(handPos));	// 다른 손 출력

	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Black, 1, 2);
}

void SkelSmallBow::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_weaponAni->stop();

			_img = IMAGE_MANAGER->findImage("Skel/Small/Idle");
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			_weaponAni->stop();
			_ani->stop();

			_img = IMAGE_MANAGER->findImage("Skel/Small/Idle");
			_weaponAni->start();
		}
		break;
		case ENEMY_STATE::DIE:
		{
			_active = false;
		}
		break;
	}
}

void SkelSmallBow::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.hitUpdate(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				case ENEMY_STATE::ATTACK:
				{
					_img = IMAGE_MANAGER->findImage("Skel/Small/Idle");
				}
				break;
			}
			_hit.isHit = false;
		}
		_moving.force.x -= _moving.gravity.x * timeElapsed;
		_moving.gravity.x -= _moving.gravity.x * timeElapsed;
		moveDir.x += _moving.force.x * timeElapsed * ((playerPos.x > _position.x) ? (1) : (-1));
	}
}

bool SkelSmallBow::hitEffect(FloatRect * rc, AttackInfo * info)
{
	return false;
}

bool SkelSmallBow::hitEffect(FloatCircle * circle, AttackInfo * info)
{
	_hit.isHit = true;
	_hit.hitCount = 0;
	//_hit.knockCount = 0;
	_moving.gravity.x = info->knockBack;

	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		case ENEMY_STATE::ATTACK:
		{
			_img = IMAGE_MANAGER->findImage("Skel/Small/Idle_Shot");
		}
		break;
	}

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= 20;
	_enemyManager->showDamage(damageInfo, renderPos);

	return true; // 맞았다면 TRUE 반환
}

bool SkelSmallBow::hitEffect(Projectile * projectile, AttackInfo * info)
{
	return false;
}
