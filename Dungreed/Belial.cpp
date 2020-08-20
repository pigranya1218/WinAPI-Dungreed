#include "stdafx.h"
#include "EnemyManager.h"
#include "Belial.h"

void Belial::init(const Vector2 & pos)
{
	// 애니메이션 할당
	_ani = new Animation;
	_backAni = new Animation;

	// 검 이미지 세팅
	_swordImg = IMAGE_MANAGER->findImage("Belial/Sword");

	// 후광구 초기화
	_backImg = IMAGE_MANAGER->findImage("Belial/Back");
	_backAni->init(_backImg->getWidth(), _backImg->getHeight(), _backImg->getMaxFrameX(), _backImg->getMaxFrameY());
	_backAni->setDefPlayFrame(false, true);
	_backAni->setFPS(15);
	_backAni->start();

	// 처음 상태는 기본
	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = DIRECTION::DOWN;
	_scale = 4;
	_size = Vector2(_img->getFrameSize().x - 20, _img->getFrameSize().y);
	_size = _size * _scale;

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(0, 150);
	_moving.delay = 0.4;

	_shooting.init("Belial/Bullet", "Belial/Bullet_FX", Vector2(300, 300), _scale, 0.15, 3, false, true, true, false, false, false);
	_shooting.attackInit(3, 5, 1);
	_shooting.angle = 0;

	_swordBullet.init("Belial/Sword_Shoot", "Belial/Sword_Charge", Vector2(1500, 1500), _scale, 0.3, 3, true, false, false, false, false, false);
	_swordBullet.attackInit(3, 5, 1);

	ZeroMemory(&_attackCycle, sizeof(&_attackCycle));
	_attackCycle.delay = 1;

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	_active = true;

	_curHp = _maxHp = 100;

	_myEnemyType = static_cast<int>(ENEMY_TYPE::BELIAL);
}

void Belial::release()
{
}

void Belial::update(float const timeElapsed)
{
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			// 현재 디렉션 따라서
			switch (_direction)
			{
				case DIRECTION::UP:
				{
					// 위로 간다
					_position.y -= _moving.force.y * timeElapsed;
					// 딜레이 완료 시 아래로
					if (_moving.update(timeElapsed))
					{
						_direction = DIRECTION::DOWN;
					}
				}
				break;
				case DIRECTION::DOWN:
				{
					// 아래로 간다
					_position.y += _moving.force.y * timeElapsed;
					// 딜레이 완료 시 위로
					if (_moving.update(timeElapsed))
					{
						_direction = DIRECTION::UP;
					}
				}
				break;
			}
			// 공격 주기 체크
			if (_attackCycle.update(timeElapsed))
			{
				setState(ENEMY_STATE::ATTACK);
			}
		}
		break;
		case ENEMY_STATE::ATTACK:
		{
			switch (_phase)
			{
				case BELIAL_PHASE::SHOOTING_READY:
				{
					// 공격 준비 모션이 끝나면
					if (!_ani->isPlay())
					{
						// 실제 공격으로 넘어감
						setPhase(BELIAL_PHASE::SHOOTING);
						//_shooting.count = _shooting.delay;
					}
				}
				break;
				case BELIAL_PHASE::SHOOTING:
				{
					// 총알 발사 주기
					if (_shooting.delayUpdate(timeElapsed))
					{
						// 총알 발사 위치
						Vector2 bulletPos = _position;
						bulletPos.x += 30;
						bulletPos.y += 60;

						// 총알 4개씩 발사
						for (int i = 0; i < 4; i++)
						{
							_shooting.createBullet(bulletPos, (_shooting.angle + (PI / 2)));
							_shooting.fireBullet(_myEnemyType, _enemyManager);
						}
						_shooting.angle += timeElapsed * 8.0f;
					}
					// 공격 시간이 끝나면
					if (_attackCycle.update(timeElapsed * 0.2f))
					{
						setPhase(BELIAL_PHASE::SHOOTING_FINAL);
					}
				}
				break;
				case BELIAL_PHASE::SHOOTING_FINAL:
				{
					// 입을 모두 닫았으면
					if (!_ani->isPlay())
					{
						setState(ENEMY_STATE::IDLE);
					}
				}
				break;
				case BELIAL_PHASE::SWORD_READY:
				{
					// 딜레이마다 검을 만들어냄
					if (_swordBullet.delayUpdate(timeElapsed))
					{
						tagSwordPosAngle sword;
						ZeroMemory(&sword, sizeof(sword));

						sword.pos = _swordPosAngle[_swordPosAngle.size() - 1].pos;
						sword.pos.x += 200;

						_swordPosAngle.push_back(sword);
					}
					// 검을 모두 만들었으면
					if(_swordPosAngle.size() >= 6)
					{
						// 검을 발사한다
						setPhase(BELIAL_PHASE::SWORD);
					}
					// 각도는 계속 업데이트한다
					for (int i = 0; i < _swordPosAngle.size(); i++)
					{
						_swordPosAngle[i].angle = getAngle(_swordPosAngle[i].pos.x, _swordPosAngle[i].pos.y, playerPos.x, playerPos.y);
					}
				}
				break;
				case BELIAL_PHASE::SWORD:
				{
					for (int i = 0; i < _swordPosAngle.size(); i++)
					{
						_swordPosAngle[i].angle = getAngle(_swordPosAngle[i].pos.x, _swordPosAngle[i].pos.y, playerPos.x, playerPos.y);
					}

					if (_swordBullet.delayUpdate(timeElapsed * 0.5f) && !_swordPosAngle.empty())
					{
						_swordBullet.createBullet(_swordPosAngle[0].pos, _swordPosAngle[0].angle);
						_swordBullet.fireBullet(_myEnemyType, _enemyManager);
						_swordPosAngle.erase(_swordPosAngle.begin());
					}
					if(_swordPosAngle.empty())
					{
						setPhase(BELIAL_PHASE::SWORD_FINAL);
					}
				}
				break;
				case BELIAL_PHASE::SWORD_FINAL:
				{
					setState(ENEMY_STATE::IDLE);
				}
				break;
				case BELIAL_PHASE::LASER:
				break;
			}
		}
		break;
		case ENEMY_STATE::DIE:
		{

		}
		break;
	}
	hitReaction(playerPos, moveDir, timeElapsed);

	_ani->frameUpdate(timeElapsed);
	_backAni->frameUpdate(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void Belial::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);

	// 후광구 출력
	Vector2 backPos = _position;
	backPos.x += 30;
	backPos.y += 60;
	/*if (_phase == BELIAL_PHASE::SHOOTING && _ani->getPlayIndex() >= 6)
	{
		backPos.y += 20 * _ani->getPlayIndex();
	}*/
	_backImg->setScale(_scale);
	_backImg->aniRender(CAMERA->getRelativeV2(backPos), _backAni);
	
	// 머리 출력
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani);

	for (int i = 0; i < _swordPosAngle.size(); i++)
	{
		_swordImg->setAngle(_swordPosAngle[i].angle * (180 / PI));
		_swordImg->setScale(_scale);
		_swordImg->render(CAMERA->getRelativeV2(_swordPosAngle[i].pos));
	}
}

void Belial::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_imageName = "Belial/Head/Idle";

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
			int pattern = RANDOM->getFromIntTo(0, 2);
			pattern = 1;

			switch (pattern)
			{
				case 0:
				{
					setPhase(BELIAL_PHASE::SHOOTING_READY);
				}
				break;
				case 1:
				{
					setPhase(BELIAL_PHASE::SWORD_READY);
				}
				break;
			}
		}
		break;
		case ENEMY_STATE::DIE:
		{

		}
		break;
	}
}

void Belial::setPhase(BELIAL_PHASE phase)
{
	_phase = phase;

	switch (phase)
	{
		case BELIAL_PHASE::SHOOTING_READY:
		{
			_imageName = "Belial/Head/Attack";

			_ani->stop();
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case BELIAL_PHASE::SHOOTING:
		{
			_ani->stop();
			_ani->setPlayFrame(6, 9, false, true);
			_ani->start();
		}
		break;
		case BELIAL_PHASE::SHOOTING_FINAL:
		{
			_ani->stop();			
			_ani->setPlayFrame(9, 0, false, false);
			_ani->start();
		}
		break;
		case BELIAL_PHASE::SWORD_READY:
		{
			tagSwordPosAngle sword;
			ZeroMemory(&sword, sizeof(sword));

			sword.pos = _position;
			sword.pos.x -= 400;

			_swordPosAngle.push_back(sword);
		}
		break;
		case BELIAL_PHASE::SWORD:
		{

		}
		break;
		case BELIAL_PHASE::SWORD_FINAL:
		{

		}
		break;
	case BELIAL_PHASE::LASER:
		break;
	default:
		break;
	}
}

void Belial::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_state)
			{
				case ENEMY_STATE::IDLE:
				{
					_imageName = "Belial/Head/Idle";
				}
				break;
				case ENEMY_STATE::ATTACK:
				{
					switch (_phase)
					{
						case BELIAL_PHASE::SHOOTING_READY:
						case BELIAL_PHASE::SHOOTING:
						case BELIAL_PHASE::SHOOTING_FINAL:
						{
							_imageName = "Belial/Head/Attack";
						}
						break;
						case BELIAL_PHASE::SWORD:
						case BELIAL_PHASE::LASER:
						{
							_imageName = "Belial/Head/Idle";
						}
						break;
					}					
				}
				break;
			}
			_img = IMAGE_MANAGER->findImage(_imageName);
			_hit.isHit = false;
		}
	}
}