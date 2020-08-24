#include "stdafx.h"
#include "EnemyManager.h"
#include "Belial.h"

void Belial::init(const Vector2 & pos)
{
	// 애니메이션 할당
	_ani = new Animation;
	_backAni = new Animation;

	// 후광구 초기화
	_backImg = IMAGE_MANAGER->findImage("Belial/Back/Circle");
	_backAni->init(_backImg->getWidth(), _backImg->getHeight(), _backImg->getMaxFrameX(), _backImg->getMaxFrameY());
	_backAni->setDefPlayFrame(false, true);
	_backAni->setFPS(15);
	_backAni->start();	

	// 처음 상태는 기본
	setState(ENEMY_STATE::IDLE);

	// 변수들 초기화
	_position = pos;
	_direction = DIRECTION::DOWN;
	_scale = 4;
	_size = Vector2(_img->getFrameSize().x - 20, _img->getFrameSize().y);
	_size = _size * _scale;

	// 후광 파티클 초기화
	_particle.img = IMAGE_MANAGER->findImage("Belial/Back/Particle");
	for (int i = 0; i < 5; i++)
	{
		_particle.ani[i] = new Animation;
		_particle.ani[i]->init(_particle.img->getWidth(), _particle.img->getHeight(), _particle.img->getMaxFrameX(), _particle.img->getMaxFrameY());
		_particle.ani[i]->setDefPlayFrame(false, false);
		_particle.ani[i]->setFPS(10 + i);

		_particle.pos[i] = Vector2(RANDOM->getFromFloatTo((_position.x + 30) - 120, (_position.x + 30) + 120), RANDOM->getFromFloatTo((_position.y + 60) - 50, (_position.y + 60) + 100));
		_particle.ani[i]->start();
	}

	// 죽을 때 파편 이미지 초기화
	_deadParticle[0].img = IMAGE_MANAGER->findImage("Belial/Dead/Head");
	_deadParticle[1].img = IMAGE_MANAGER->findImage("Belial/Dead/Mouth");
	_deadParticle[2].img = IMAGE_MANAGER->findImage("Belial/Dead/Particle_1");
	_deadParticle[3].img = IMAGE_MANAGER->findImage("Belial/Dead/Particle_2");
	_deadParticle[4].img = IMAGE_MANAGER->findImage("Belial/Dead/Particle_3");
	_deadParticle[5].img = IMAGE_MANAGER->findImage("Belial/Dead/Particle_4");

	// 파편 위치들 초기화
	_deadParticle[0].setPosition(Vector2(_position.x - 30, _position.y - 30));
	_deadParticle[1].setPosition(Vector2(_position.x, _position.y + 180));
	_deadParticle[2].setPosition(Vector2(_position.x - 90, _position.y + 80));
	_deadParticle[3].setPosition(Vector2(_position.x + 90, _position.y + 80));
	_deadParticle[4].setPosition(Vector2(_position.x - 90, _position.y + 120));
	_deadParticle[5].setPosition(Vector2(_position.x + 90, _position.y + 120));

	// 사이즈 초기화
	for (int i = 0; i < 6; i++)
	{
		_deadParticle[i].setSize(Vector2(_deadParticle[i].img->getSize().x * _scale, _deadParticle[i].img->getSize().y * _scale));
	}
	_deadAngle = -PI / 25;

	// 이동 수정
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(0, 150);
	_moving.delay = 0.4;
	_moving.gravity = Vector2(0, 7000);

	// 벨리알 탄막 패턴
	_shooting.init("Belial/Bullet", "Belial/Bullet_FX", Vector2(500, 500), _scale, 0.1, 3, false, true, true, false, true, false);
	_shooting.attackInit(1,3,1);
	_shooting.angle = 0;

	// 검 패턴
	ZeroMemory(&_swordAtk, sizeof(_swordAtk));
	_swordAtk.attackInit(1, 5, 3);
	_swordAtk.delay = 0.09;
	_swordAtk.circleSize = 130;

	// 공격 주기 설정
	ZeroMemory(&_attackCycle, sizeof(&_attackCycle));
	_attackCycle.delay = 2.8;

	// 죽은 상태 설정
	ZeroMemory(&_dieEffect, sizeof(_dieEffect));
	_dieEffect.delay = 0.2;
	_effectNum = 0;

	// 피격 이펙트 주기 설정
	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	// 액티브 = 1, 레이저변수 초기화
	_active = true;
	_laserNum = _backMove = _angleWay = 0;

	// 체력 초기화
	_curHp = _maxHp = 800;

	// 에너미해시코드 초기화
	_myEnemyType = static_cast<int>(ENEMY_TYPE::BELIAL);

	// 손 초기화
	_handL.init(Vector2(_position.x - 130 * _scale, _position.y + 50 * _scale));
	_handR.init(Vector2(_position.x + 130 * _scale, _position.y + 50 * _scale));
	
	// 오른쪽 레이저 초기화
	{
		Vector2 size = _handR.laserHeadImg->getFrameSize() * _scale;
		FloatRect headRc(Vector2(_handR.position.x - size.x * 0.7f, _handR.position.y), size, PIVOT::CENTER);
		_handR.laserRect.push_back(headRc);		
		for (int i = 1; i < 50; i++)
		{
			size = _handR.laserBodyImg->getFrameSize() * _scale;
			FloatRect headRc(Vector2(_handR.laserRect[i - 1].left - size.x * 0.5f, _handR.position.y), size, PIVOT::CENTER);
			_handR.laserRect.push_back(headRc);
		}
		_handR.atkRect = rectMakePivot(
			Vector2(_handR.laserRect[_handR.laserRect.size() - 1].left, _handR.laserRect[_handR.laserRect.size() - 1].top),
			Vector2(_handR.laserRect[0].right - _handR.laserRect[_handR.laserRect.size() - 1].left, size.y), 
			PIVOT::LEFT_TOP
		);
	}

	// 왼쪽 레이저 초기화
	{
		Vector2 size = _handR.laserHeadImg->getFrameSize() * _scale;
		FloatRect headRc(Vector2(_handL.position.x + size.x * 0.7f, _handL.position.y), size, PIVOT::CENTER);
		_handL.laserRect.push_back(headRc);
		for (int i = 1; i < 50; i++)
		{
			size = _handR.laserBodyImg->getFrameSize() * _scale;
			FloatRect headRc(Vector2(_handL.laserRect[i - 1].right + size.x * 0.5f, _handL.position.y), size, PIVOT::CENTER);
			_handL.laserRect.push_back(headRc);
		}
		_handL.atkRect = rectMakePivot(
			Vector2(_handL.laserRect[0].left, _handL.laserRect[0].top),
			Vector2(_handL.laserRect[_handL.laserRect.size() - 1].right - _handL.laserRect[0].left, size.y),
			PIVOT::LEFT_TOP
		);
	}

	// 알파값 초기화
	_handAlpha = _headAlpha = 0;

	setState(ENEMY_STATE::ENTER);
}

void Belial::release()
{
	_ani->release();
	_backAni->release();

	SAFE_DELETE(_ani);
	SAFE_DELETE(_backAni);

	_handL.release();
	_handR.release();

	for (int i = 0; i < 5; i++)
	{
		_particle.ani[i]->release();
		SAFE_DELETE(_particle.ani[i]);
	}
}

void Belial::update(float const timeElapsed)
{
	// 플레이어 좌표는 항상 가지고 있음
	_playerPos = _enemyManager->getPlayerPos();

	Vector2 moveDir(0, 0);	
	switch (_state)
	{
		case ENEMY_STATE::ENTER:
		{
			headMove(timeElapsed);

			_headAlpha += timeElapsed;

			if (_headAlpha >= 1.0f)
			{
				_headAlpha = 1.0f;

				_handAlpha += timeElapsed;

				if (_handAlpha >= 1.0f)
				{
					_handAlpha = 1.0f;
					setState(ENEMY_STATE::IDLE);
				}
			}
		}
		break;
		// 기본 상태
		case ENEMY_STATE::IDLE:
		{
			// 머리는 항상 움직임
			headMove(timeElapsed);

			// 공격 주기 체크
			if (_attackCycle.update(timeElapsed))
			{
				// 공격 상태로 전환
				setState(ENEMY_STATE::ATTACK);
			}
		}
		break;
		// 공격 상태
		case ENEMY_STATE::ATTACK:
		{
			// 공격 페이즈
			switch (_phase)
			{
				// 탄막 준비
				case BELIAL_PHASE::SHOOTING_READY:
				{
					// 벨리알 입이 벌려있음
					if (_ani->getPlayIndex() >= 3)
					{
						// 후광구 위치 조정 플래그 ON
						_backMove = true;
					}
					// 공격 준비 모션이 끝나면
					if (!_ani->isPlay())
					{
						// 투사체 발사 페이즈
						setPhase(BELIAL_PHASE::SHOOTING_START);
					}
				}
				break;
				// 투사체 발사 페이즈
				case BELIAL_PHASE::SHOOTING_START:
				{
					// 총알 발사 주기
					if (_shooting.delayUpdate(timeElapsed))
					{
						// 총알 발사 위치
						Vector2 bulletPos = _position;
						//bulletPos.x += 7.5f * _scale;
						bulletPos.y += 27.5f * _scale;

						// 총알 4개씩 발사
						for (int i = 0; i < 4; i++)
						{
							_shooting.createBullet(bulletPos, (_shooting.angle + (PI / 2)));
							_shooting.fireBullet(_myEnemyType, _enemyManager);
						}

						SOUND_MANAGER->stop("Belial/Bullet");
						SOUND_MANAGER->play("Belial/Bullet", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

						// 투사체 발사 각도 회전
						_shooting.angle += timeElapsed * 8.0f;
					}
					// 공격 시간이 끝나면
					if (_attackCycle.update(timeElapsed))
					{
						// 투사체 발사 완료 페이즈
						setPhase(BELIAL_PHASE::SHOOTING_FINAL);
					}
				}
				break;
				// 투사체 발사 완료 페이즈
				case BELIAL_PHASE::SHOOTING_FINAL:
				{
					// 입을 모두 닫았으면
					if (_ani->getPlayIndex() > 6)
					{
						// 후광구 위치 조정
						_backMove = false;
					}
					// 입을 모두 닫았으면
					if (!_ani->isPlay())
					{
						// 기본 상태로 돌아감						
						setState(ENEMY_STATE::IDLE);
					}
				}
				break;
				// 검 소환
				case BELIAL_PHASE::SWORD_READY:
				{
					// 머리도 항상 움직임
					headMove(timeElapsed);

					// 일정 주기마다 검 6개까지 생성
					if (_swordAtk.update(timeElapsed) && _sword.size() < 6)
					{
						tagSwordInfo* sword = new tagSwordInfo;

						// 검 초기화
						sword->img = IMAGE_MANAGER->findImage("Belial/Sword");
						sword->setPosition(Vector2((_position.x - 80 * _scale) + _swordNum * 150, _position.y - 50 * _scale));
						sword->setSize(Vector2(50, 50));
						sword->setActive(true);
						sword->chargeEffect.delay = 0.5;

						EFFECT_MANAGER->play("Enemy_Destroy", sword->getPosition(), Vector2(160, 160));

						SOUND_MANAGER->stop("Belial/Sword");
						SOUND_MANAGER->play("Belial/Sword", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

						_sword.push_back(sword);
						_swordNum++;
					}					
					if (_sword.size() == 6 && _swordAtk.update(timeElapsed * 5.5f))
					{
						setPhase(BELIAL_PHASE::SWORD_START);
						_swordNum = 0;
					}					
				}
				break;
				// 검 던지기
				case BELIAL_PHASE::SWORD_START:
				{
					headMove(timeElapsed);

					// 검 공격 이미지 변경
					if (_sword[_swordNum]->getActive())
					{
						_sword[_swordNum]->img = IMAGE_MANAGER->findImage("Belial/Sword_Shoot");
					}					
					_sword[_swordNum]->setActive(false);

					Vector2 moveSword(0, 0);

					moveSword.x += cosf(_sword[_swordNum]->angle) * 2700 * timeElapsed;
					moveSword.y -= sinf(_sword[_swordNum]->angle) * 2700 * timeElapsed;

					Vector2 lastDir = _sword[_swordNum]->getPosition();
					_enemyManager->moveEnemy(_sword[_swordNum], moveSword, true, false);
					Vector2 currDir = _sword[_swordNum]->getPosition();

					// 공격 판정
					float startRad = _sword[_swordNum]->angle - PI / 15;
					float endRad = _sword[_swordNum]->angle + PI / 15;
					_swordAtk.attackCircle(_myEnemyType, _enemyManager, _sword[_swordNum]->getPosition(), startRad, endRad);

					// 붉은 선에 닿으면
					if (lastDir + moveSword != currDir)
					{						
						EFFECT_MANAGER->play("Belial/Sword_Hit", _sword[_swordNum]->getPosition(), IMAGE_MANAGER->findImage("Belial/Sword_Hit")->getFrameSize() * _scale, _sword[_swordNum]->angle * (180 / PI));
						// 이미지 원래대로
						_sword[_swordNum]->img = IMAGE_MANAGER->findImage("Belial/Sword");
						// 다음 검 날린다
						_swordNum++;
						// 공격 ID 초기화
						_swordAtk.id.clear();
						// 모든 검을 사용했으면
						if (_swordNum > _sword.size() - 1)
						{
							_swordNum = 0;
							// 검 삭제 페이즈로 변경
							setPhase(BELIAL_PHASE::SWORD_FINAL);
						}
					}					
				}
				break;
				// 검 삭제
				case BELIAL_PHASE::SWORD_FINAL:
				{
					headMove(timeElapsed);

					if (_swordAtk.update(timeElapsed))
					{
						EFFECT_MANAGER->play("Enemy_Destroy", _sword[0]->getPosition(), Vector2(_sword[0]->img->getSize().x * _scale, _sword[0]->img->getSize().x * _scale));
						SAFE_DELETE(_sword[_swordNum]);
						_sword.erase(_sword.begin());
					}
					if (_sword.empty())
					{
						setState(ENEMY_STATE::IDLE);
					}
				}
				break;
				// 레이저 오른쪽 발사
				case BELIAL_PHASE::LASER_R:
				{
					headMove(timeElapsed);

					if (_laserNum > 0)
					{
						if (_handR.state == HAND_STATE::ATTACK_FINAL)
						{
							
							setPhase(BELIAL_PHASE::LASER_L);
						}
					}
					else
					{
						if (_handL.state == HAND_STATE::IDLE)
						{
							setState(ENEMY_STATE::IDLE);
						}
					}					
				}
				break;
				// 레이저 왼쪽 발사
				case BELIAL_PHASE::LASER_L:
				{
					headMove(timeElapsed);

					if (_laserNum > 0)
					{
						if (_handL.state == HAND_STATE::ATTACK_FINAL)
						{
							setPhase(BELIAL_PHASE::LASER_R);
						}
					}
					else
					{
						if (_handL.state == HAND_STATE::IDLE)
						{
							setState(ENEMY_STATE::IDLE);
						}
					}					
				}
				break;
			}
		}
		break;
		case ENEMY_STATE::DIE:
		{
			if (_dieEffect.update(timeElapsed))
			{
				// 처음에 랜덤으로 터질 떄
				if (_effectNum < 20)
				{
					_effectNum++;

					for (int i = 0; i < 8; i++)
					{
						EFFECT_MANAGER->play(
							"Enemy_Destroy",
							Vector2(RANDOM->getFromFloatTo(_position.x - 300, _position.x + 300), RANDOM->getFromFloatTo(_position.y - 200, _position.y + 200)),
							Vector2(160, 160)
						);						
					}
					SOUND_MANAGER->stop("Enemy/Die");
					SOUND_MANAGER->play("Enemy/Die", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
				}
				// 그 후 가운데에서 퍼지면서 터질 때
				if (_effectNum >= 20 && _effectNum < 25)
				{
					_effectNum++;

					_dieEffect.delay = 0.15f;

					float angle = 0;
					for (int i = 0; i < 10; i++)
					{
						angle += PI / 6;

						Vector2 drawPos = _position;
						drawPos.x += cosf(angle) * ((_effectNum - 20) * 80);
						drawPos.y -= sinf(angle) * ((_effectNum - 20) * 80);

						EFFECT_MANAGER->play("Enemy_Destroy", drawPos, Vector2(160, 160));

						if (i == 4) angle += PI / 6;
					}
					SOUND_MANAGER->stop("Enemy/Die");
					SOUND_MANAGER->play("Enemy/Die", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

					if (!_realDead) _realDead = true;
				}				
			}
			// 파티클 움직임
			if (_realDead)
			{
				moveDir = Vector2(0, 0);

				for (int i = 0; i < 6; i++)
				{
					_moving.force.y += _moving.gravity.y * timeElapsed;
					moveDir.y = _moving.force.y * timeElapsed;

					_enemyManager->moveEnemy(&_deadParticle[i], moveDir);
					_moving.force.y = 150;					
				}

				// 머리 흔들리는 효과
				if (_deadParticle[0].getIsStand())
				{
					// 우측으로
					if (_angleWay)
					{
						_moving.angle -= timeElapsed / 7;

						if (_moving.angle < _deadAngle)
						{
							_deadAngle += timeElapsed * 0.8;
							_deadAngle = min(_deadAngle, 0);
							_angleWay = false;
						}
					}
					// 좌측으로
					else
					{
						_moving.angle += timeElapsed / 7;

						if (_moving.angle > 0)
						{
							_angleWay = true;
						}
					}
				}
			}
		}
		break;
	}	
	hitReaction(_playerPos, moveDir, timeElapsed);

	if (_state != ENEMY_STATE::DIE)
	{
		_ani->frameUpdate(timeElapsed);

		_enemyManager->activeBossUI(true);
		_enemyManager->setBossUIHp(_maxHp, _curHp);

		_backAni->frameUpdate(timeElapsed);
		for (int i = 0; i < 5; i++)
		{
			_particle.ani[i]->frameUpdate(timeElapsed);
		}

		_handL.update(timeElapsed, _myEnemyType, _enemyManager);
		_handR.update(timeElapsed, _myEnemyType, _enemyManager);

		// 검 패턴 각도 설정 및 이펙트 재생
		for (int i = 0; i < _sword.size(); i++)
		{
			if (!_sword[i]->getActive()) continue;
			_sword[i]->angle = getAngle(_sword[i]->getPosition().x, _sword[i]->getPosition().y, _playerPos.x, _playerPos.y);

			if (_sword[i]->chargeEffect.update(timeElapsed))
			{
				EFFECT_MANAGER->play(
					"Belial/Sword_Charge",
					_sword[i]->getPosition(),
					IMAGE_MANAGER->findImage("Belial/Sword_Charge")->getFrameSize() * _scale,
					(_sword[i]->angle) * (180 / PI)
				);
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (!_particle.ani[i]->isPlay())
		{
			_particle.pos[i] = Vector2(RANDOM->getFromFloatTo((_position.x + 30) - 120, (_position.x + 30) + 120), RANDOM->getFromFloatTo((_position.y + 60) - 50, (_position.y + 60) + 100));
			_particle.ani[i]->start();
		}
	}

	if (_curHp <= 0 && _state != ENEMY_STATE::DIE)
	{
		_enemyManager->activeBossUI(false);
		_enemyManager->makeR2REvent(RGB(255, 255, 255), 3);
		_enemyManager->makeTimeRatioEvent(0.5, 3);
		setState(ENEMY_STATE::DIE);
	}
}

void Belial::render()
{
	if (_state != ENEMY_STATE::DIE)
	{
		for (int i = 0; i < 5; i++)
		{
			_particle.img->setScale(_scale);
			_particle.img->aniRender(CAMERA->getRelativeV2(_particle.pos[i]), _particle.ani[i]);
		}
	}

	if (!_realDead)
	{
		// 후광구 출력
		Vector2 backPos = _position;
		// 기본 상태 위치
		//backPos.x += 10;
		backPos.y += 60;
		// 공격 상태 위치
		if (_backMove)
		{
			// 입을 벌린 상태임
			backPos.y += 50;
		}
		_backImg->setAlpha(_headAlpha);
		_backImg->setScale(_scale);
		_backImg->aniRender(CAMERA->getRelativeV2(backPos), _backAni);

		// 머리 출력
		Vector2 headPos = _position;
		headPos.x -= 30;
		_img->setAlpha(_headAlpha);
		_img->setScale(_scale);
		_img->aniRender(CAMERA->getRelativeV2(headPos), _ani);

		_handL.render(_scale, _handAlpha);
		_handR.render(_scale, _handAlpha, true);

		// 검 출력
		for (int i = 0; i < _sword.size(); i++)
		{
			_sword[i]->img->setScale(_scale);
			_sword[i]->img->setAngle((_sword[i]->angle) * (180 / PI));
			_sword[i]->img->render(CAMERA->getRelativeV2(_sword[i]->getPosition()));
		}

		// 좌측 레이저 출력
		if (_handL.laserBodyAni->isPlay() && _handL.laserHeadAni->isPlay())
		{
			_handL.laserHeadImg->setScale(_scale);
			_handL.laserHeadImg->aniRender(CAMERA->getRelativeV2(_handL.laserRect[0].getCenter()), _handL.laserHeadAni);

			for (int i = 1; i < _handL.laserRect.size(); i++)
			{
				_handL.laserBodyImg->setScale(_scale);
				_handL.laserBodyImg->aniRender(CAMERA->getRelativeV2(_handL.laserRect[i].getCenter()), _handL.laserBodyAni);
			}
		}
		// 우측 레이저 출력
		if (_handR.laserBodyAni->isPlay() && _handR.laserHeadAni->isPlay())
		{
			_handR.laserHeadImg->setScale(_scale);
			_handR.laserHeadImg->aniRender(CAMERA->getRelativeV2(_handR.laserRect[0].getCenter()), _handR.laserHeadAni, true);

			for (int i = 1; i < _handR.laserRect.size(); i++)
			{
				_handR.laserBodyImg->setScale(_scale);
				_handR.laserBodyImg->aniRender(CAMERA->getRelativeV2(_handR.laserRect[i].getCenter()), _handR.laserBodyAni, true);
			}
		}
	}
	else
	{
		_deadParticle[0].img->setAngle((_moving.angle) * (180 / PI));
		_deadParticle[0].img->setAnglePos(Vector2(_deadParticle[0].img->getSize().x * 0.5f, _deadParticle[0].img->getSize().y));
		for (int i = 5; i >= 0; i--)
		{
			_deadParticle[i].img->setScale(_scale);
			_deadParticle[i].img->render(CAMERA->getRelativeV2(_deadParticle[i].getPosition()));
		}
	}
}

void Belial::setState(ENEMY_STATE state)
{
	_state = state;

	switch (state)
	{
		case ENEMY_STATE::ENTER:
		{
			SOUND_MANAGER->stop("Belial/Enter");
			SOUND_MANAGER->play("Belial/Enter", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
		}
		break;
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
			unsigned pattern = RANDOM->getFromIntTo(0, 3);

			switch (pattern)
			{
				// 탄막
				case 0:
				{
					setPhase(BELIAL_PHASE::SHOOTING_READY);
				}
				break;
				// 검
				case 1:
				{
					setPhase(BELIAL_PHASE::SWORD_READY);
				}
				break;
				// 레이저
				case 2:
				{
					unsigned laserPattern = RANDOM->getFromIntTo(0, 3);

					switch (laserPattern)
					{
						// 레이저 좌측 발사
						case 0: 
						{
							_laserNum = 0;
							setPhase(BELIAL_PHASE::LASER_R);
						}
						break;
						// 레이저 우측 발사
						case 1: 
						{
							_laserNum = 0;
							setPhase(BELIAL_PHASE::LASER_L);
						}
						break;
						// 레이저 번갈아서 발사
						case 2:
						{
							_laserNum = 3;
							setPhase(BELIAL_PHASE::LASER_R);							
						}
						break;
					}
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
			_ani->setPlayFrame(0, 6, false, false);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
		case BELIAL_PHASE::SHOOTING_START:
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
			
		}
		break;
		case BELIAL_PHASE::SWORD_START:
		{

		}
		break;
		case BELIAL_PHASE::SWORD_FINAL:
		{

		}
		break;
		case BELIAL_PHASE::LASER_R:
		{
			_handR.setState(HAND_STATE::MOVE, _playerPos);
			_laserNum--;
		}
		break;
		case BELIAL_PHASE::LASER_L:
		{
			_handL.setState(HAND_STATE::MOVE, _playerPos);
			_laserNum--;
		}
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
						case BELIAL_PHASE::SHOOTING_START:
						case BELIAL_PHASE::SHOOTING_FINAL:
						{
							_imageName = "Belial/Head/Attack";
						}
						break;
						case BELIAL_PHASE::SWORD_READY:
						case BELIAL_PHASE::SWORD_START:
						case BELIAL_PHASE::SWORD_FINAL:
						case BELIAL_PHASE::LASER_R:
						case BELIAL_PHASE::LASER_L:
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

void Belial::headMove(const float timeElapsed)
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
}

void Belial::tagHandInfo::init(const Vector2& pos)
{
	// 손 애니메이션 할당
	ani = new Animation;

	// 레이저 애니메이션 할당
	laserHeadAni = new Animation;
	laserBodyAni = new Animation;

	// 포지션 설정
	position = pos;

	// 기본 상태로 설정
	setState(HAND_STATE::IDLE);

	// 레이저 이미지 저장
	laserHeadImg = IMAGE_MANAGER->findImage("Belial/Laser/Head");
	laserBodyImg = IMAGE_MANAGER->findImage("Belial/Laser/Body");

	// 레이저 애니메이션 초기화
	laserHeadAni->init(laserHeadImg->getWidth(), laserHeadImg->getHeight(), laserHeadImg->getMaxFrameX(), laserHeadImg->getMaxFrameY());
	laserBodyAni->init(laserBodyImg->getWidth(), laserBodyImg->getHeight(), laserBodyImg->getMaxFrameX(), laserBodyImg->getMaxFrameY());
	
	// 움직인다.
	ZeroMemory(&moving, sizeof(moving));
	moving.force = Vector2(0, 800);

	// 레이저 공격정보 초기화
	laserAtk.attackInit(3, 5, 0);
}

void Belial::tagHandInfo::update(const float timeElapsed, int enemyType, EnemyManager* enemyManager)
{
	switch (state)
	{
		case HAND_STATE::IDLE:
		{

		}
		break;
		// 플레이어 좌표 추적
		case HAND_STATE::MOVE:
		{
			// 플레이어 좌표와의 거리가 스피드 값보다 크면
			if (fabsf(movePos.y - position.y) > moving.force.y * timeElapsed)
			{
				// 이동
				position.y += moving.force.y * timeElapsed * ((movePos.y > position.y) ? (1) : (-1));				
			}
			// 이동을 완료한 경우
			else
			{
				// 포지션 조정
				position.y = movePos.y;
				// 레이저 렉트 모두 조정
				for (int i = 0; i < laserRect.size(); i++)
				{
					laserRect[i] = FloatRect(Vector2(laserRect[i].getCenter().x, position.y), laserRect[i].getSize(), PIVOT::CENTER);
				}
				// 공격렉트 설정
				atkRect = rectMakePivot(Vector2(atkRect.getCenter().x, position.y), atkRect.getSize(), PIVOT::CENTER);

				// 공격 준비로 변경
				setState(HAND_STATE::ATTACK_READY);
			}
		}
		break;
		// 공격 준비
		case HAND_STATE::ATTACK_READY:
		{
			// 손 프레임이 레이저 발사 프레임과 일치하면
			if (ani->getPlayIndex() == 8 && !laserHeadAni->isPlay() && !laserBodyAni->isPlay())
			{
				// 레이저 발사 및 공격				
				setState(HAND_STATE::ATTACK_START);
			}			
		}
		break;
		// 여기서 공격판정
		case HAND_STATE::ATTACK_START:
		{
			// 공격
			laserAtk.attackRect(enemyType, enemyManager, atkRect);

			if (!ani->isPlay())
			{
				setState(HAND_STATE::ATTACK_FINAL);
				// 공격 ID 초기화
				laserAtk.id.clear();
			}
		}
		break;
		// 레이저 종료 중
		case HAND_STATE::ATTACK_FINAL:
		{
			// 레이저가 완전히 종료되면
			if (!laserHeadAni->isPlay() && !laserBodyAni->isPlay())
			{
				// 기본 상태로 변경				
				setState(HAND_STATE::IDLE);
			}
		}
		break;
	}

	ani->frameUpdate(timeElapsed);

	laserHeadAni->frameUpdate(timeElapsed);
	laserBodyAni->frameUpdate(timeElapsed);
}

void Belial::tagHandInfo::render(const float scale, const float alpha, bool bisymmetry)
{
	img->setAlpha(alpha);
	img->setScale(scale);
	img->aniRender(CAMERA->getRelativeV2(position), ani, bisymmetry);
}

void Belial::tagHandInfo::setState(HAND_STATE state, const Vector2& movePos)
{
	this->state = state;

	switch (state)
	{
		case HAND_STATE::IDLE:
		{
			img = IMAGE_MANAGER->findImage("Belial/Hand/Idle");

			ani->stop();
			ani->init(img->getWidth(), img->getHeight(), img->getMaxFrameX(), img->getMaxFrameY());
			ani->setDefPlayFrame(false, true);
			ani->setFPS(15);
			ani->start();
		}
		break;
		case HAND_STATE::MOVE:
		{
			img = IMAGE_MANAGER->findImage("Belial/Hand/Idle");

			ani->stop();
			ani->init(img->getWidth(), img->getHeight(), img->getMaxFrameX(), img->getMaxFrameY());
			ani->setDefPlayFrame(false, true);
			ani->setFPS(15);
			ani->start();

			this->movePos = movePos;
		}
		break;
		case HAND_STATE::ATTACK_READY:
		{
			img = IMAGE_MANAGER->findImage("Belial/Hand/Attack");

			ani->stop();
			ani->init(img->getWidth(), img->getHeight(), img->getMaxFrameX(), img->getMaxFrameY());
			ani->setDefPlayFrame(false, false);
			ani->setFPS(20);
			ani->start();

			laserHeadAni->stop();
			laserBodyAni->stop();
			laserHeadAni->setPlayFrame(0, 2, false, true);
			laserBodyAni->setPlayFrame(0, 2, false, true);
			laserHeadAni->setFPS(20);
			laserBodyAni->setFPS(20);
		}
		break;
		case HAND_STATE::ATTACK_START:
		{
			laserHeadAni->start();
			laserBodyAni->start();

			SOUND_MANAGER->stop("Belial/Laser");
			SOUND_MANAGER->play("Belial/Laser", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
		}
		break;
		case HAND_STATE::ATTACK_FINAL:
		{
			img = IMAGE_MANAGER->findImage("Belial/Hand/Idle");

			ani->stop();
			ani->init(img->getWidth(), img->getHeight(), img->getMaxFrameX(), img->getMaxFrameY());
			ani->setDefPlayFrame(false, true);
			ani->setFPS(15);
			ani->start();

			laserHeadAni->stop();
			laserBodyAni->stop();
			laserHeadAni->setDefPlayFrame(false, false);
			laserBodyAni->setDefPlayFrame(false, false);
			laserHeadAni->start();
			laserBodyAni->start();

			SOUND_MANAGER->stop("Belial/Laser");
		}
		break;
	}
}
