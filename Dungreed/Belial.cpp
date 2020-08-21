#include "stdafx.h"
#include "EnemyManager.h"
#include "Belial.h"

void Belial::init(const Vector2 & pos)
{
	// �ִϸ��̼� �Ҵ�
	_ani = new Animation;
	_backAni = new Animation;

	// �ı��� �ʱ�ȭ
	_backImg = IMAGE_MANAGER->findImage("Belial/Back/Circle");
	_backAni->init(_backImg->getWidth(), _backImg->getHeight(), _backImg->getMaxFrameX(), _backImg->getMaxFrameY());
	_backAni->setDefPlayFrame(false, true);
	_backAni->setFPS(15);
	_backAni->start();	

	// ó�� ���´� �⺻
	setState(ENEMY_STATE::IDLE);

	// ������ �ʱ�ȭ
	_position = pos;
	_direction = DIRECTION::DOWN;
	_scale = 4;
	_size = Vector2(_img->getFrameSize().x - 20, _img->getFrameSize().y);
	_size = _size * _scale;

	// �ı� ��ƼŬ �ʱ�ȭ
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

	// �̵� ����
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(0, 150);
	_moving.delay = 0.4;

	// ������ ź�� ����
	_shooting.init("Belial/Bullet", "Belial/Bullet_FX", Vector2(500, 500), _scale, 0.1, 3, false, true, true, false, true, false);
	_shooting.attackInit(3, 5, 1);
	_shooting.angle = 0;

	// �� ����
	ZeroMemory(&_swordAtk, sizeof(_swordAtk));
	_swordAtk.attackInit(3, 5, 0);
	_swordAtk.delay = 0.2;
	_swordAtk.circleSize = 130;

	// ���� �ֱ� ����
	ZeroMemory(&_attackCycle, sizeof(&_attackCycle));
	_attackCycle.delay = 3;

	ZeroMemory(&_dieEffect, sizeof(_dieEffect));
	_dieEffect.delay = 0.17;
	_effectNum = 0;

	// �ǰ� ����Ʈ �ֱ� ����
	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	// ��Ƽ�� = 1, ���������� �ʱ�ȭ
	_active = true;
	_laserNum = _backMove = 0;

	_curHp = _maxHp = 100;

	_myEnemyType = static_cast<int>(ENEMY_TYPE::BELIAL);

	// �� �ʱ�ȭ
	_handL.init(Vector2(_position.x - 130 * _scale, _position.y + 50 * _scale));
	_handR.init(Vector2(_position.x + 130 * _scale, _position.y + 50 * _scale));

	
	// ������ ������ �ʱ�ȭ
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

	// ���� ������ �ʱ�ȭ
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
	_playerPos = _enemyManager->getPlayerPos();

	Vector2 moveDir(0, 0);	
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			headMove(timeElapsed);
			// ���� �ֱ� üũ
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
					if (_ani->getPlayIndex() >= 3)
					{
						_backMove = true;
					}
					// ���� �غ� ����� ������
					if (!_ani->isPlay())
					{
						// ���� �������� �Ѿ
						setPhase(BELIAL_PHASE::SHOOTING_START);
					}
				}
				break;
				case BELIAL_PHASE::SHOOTING_START:
				{
					// �Ѿ� �߻� �ֱ�
					if (_shooting.delayUpdate(timeElapsed))
					{
						// �Ѿ� �߻� ��ġ
						Vector2 bulletPos = _position;
						bulletPos.x += 30;
						bulletPos.y += 110;

						// �Ѿ� 4���� �߻�
						for (int i = 0; i < 4; i++)
						{
							_shooting.createBullet(bulletPos, (_shooting.angle + (PI / 2)));
							_shooting.fireBullet(_myEnemyType, _enemyManager);
						}
						_shooting.angle += timeElapsed * 8.0f;
					}
					// ���� �ð��� ������
					if (_attackCycle.update(timeElapsed))
					{
						setPhase(BELIAL_PHASE::SHOOTING_FINAL);
					}
				}
				break;
				case BELIAL_PHASE::SHOOTING_FINAL:
				{
					if (_ani->getPlayIndex() > 6)
					{
						_backMove = false;
					}
					// ���� ��� �ݾ�����
					if (!_ani->isPlay())
					{
						setState(ENEMY_STATE::IDLE);
					}
				}
				break;
				// �� ��ȯ
				case BELIAL_PHASE::SWORD_READY:
				{
					headMove(timeElapsed);

					if (_swordAtk.update(timeElapsed) && _sword.size() < 6)
					{
						tagSwordInfo* sword = new tagSwordInfo;

						sword->img = IMAGE_MANAGER->findImage("Belial/Sword");
						sword->setPosition(Vector2((_position.x - 80 * _scale) + _swordNum * 150, _position.y - 50 * _scale));
						sword->setSize(Vector2(50, 50));
						sword->setActive(true);
						sword->chargeEffect.delay = 0.5;

						EFFECT_MANAGER->play("Enemy_Destroy", sword->getPosition(), Vector2(sword->img->getSize().x * _scale, sword->img->getSize().x * _scale));

						_sword.push_back(sword);
						_swordNum++;
					}					
					if (_sword.size() == 6 && _swordAtk.update(timeElapsed * 5.5))
					{
						setPhase(BELIAL_PHASE::SWORD_START);
						_swordNum = 0;
					}					
				}
				break;
				// �� ������
				case BELIAL_PHASE::SWORD_START:
				{
					headMove(timeElapsed);

					// �� ���� �̹��� ����
					if (_sword[_swordNum]->getActive())
					{
						_sword[_swordNum]->img = IMAGE_MANAGER->findImage("Belial/Sword_Shoot");
					}					
					_sword[_swordNum]->setActive(false);

					Vector2 moveSword(0, 0);

					moveSword.x += cosf(_sword[_swordNum]->angle) * 2500 * timeElapsed;
					moveSword.y -= sinf(_sword[_swordNum]->angle) * 2500 * timeElapsed;

					Vector2 lastDir = _sword[_swordNum]->getPosition();
					_enemyManager->moveEnemy(_sword[_swordNum], moveSword, true, false);
					Vector2 currDir = _sword[_swordNum]->getPosition();

					// ���� ����
					float startRad = _sword[_swordNum]->angle - PI / 15;
					float endRad = _sword[_swordNum]->angle + PI / 15;
					_swordAtk.attackCircle(_myEnemyType, _enemyManager, _sword[_swordNum]->getPosition(), startRad, endRad);

					// ���� ���� ������
					if (lastDir + moveSword != currDir)
					{						
						EFFECT_MANAGER->play("Belial/Sword_Hit", _sword[_swordNum]->getPosition(), IMAGE_MANAGER->findImage("Belial/Sword_Hit")->getFrameSize() * _scale, _sword[_swordNum]->angle * (180 / PI));
						// �̹��� �������
						_sword[_swordNum]->img = IMAGE_MANAGER->findImage("Belial/Sword");
						// ���� �� ������
						_swordNum++;
						// ���� ID �ʱ�ȭ
						_swordAtk.id.clear();
						// ��� ���� ���������
						if (_swordNum > _sword.size() - 1)
						{
							_swordNum = 0;
							// �� ���� ������� ����
							setPhase(BELIAL_PHASE::SWORD_FINAL);
						}
					}					
				}
				break;
				// �� ����
				case BELIAL_PHASE::SWORD_FINAL:
				{
					headMove(timeElapsed);

					if (_swordAtk.update(timeElapsed))
					{
						EFFECT_MANAGER->play("Enemy_Destroy", _sword[0]->getPosition(), Vector2(_sword[0]->img->getSize().x * _scale, _sword[0]->img->getSize().x * _scale));
						_sword.erase(_sword.begin());						
					}
					if (_sword.empty())
					{
						setState(ENEMY_STATE::IDLE);
					}
				}
				break;
				// ������ ������ �߻�
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
				// ������ ���� �߻�
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
				_effectNum++;
				for (int i = 0; i < 5; i++)
				{
					EFFECT_MANAGER->play(
						"Enemy_Destroy",
						Vector2(RANDOM->getFromFloatTo(_position.x - 200, _position.x + 200), RANDOM->getFromFloatTo(_position.y - 200, _position.y + 200)),
						Vector2(150, 150)
					);
				}				
			}
			if (_effectNum > 50)
			{
				_active = false;
			}
		}
		break;
	}
	hitReaction(_playerPos, moveDir, timeElapsed);

	// �� ���� ���� ���� �� ����Ʈ ���
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

	_ani->frameUpdate(timeElapsed);

	_backAni->frameUpdate(timeElapsed);
	for (int i = 0; i < 5; i++)
	{
		_particle.ani[i]->frameUpdate(timeElapsed);
	}

	_handL.update(timeElapsed, _myEnemyType, _enemyManager);
	_handR.update(timeElapsed, _myEnemyType, _enemyManager);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

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
		setState(ENEMY_STATE::DIE);
	}
}

void Belial::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);

	for (int i = 0; i < 5; i++)
	{
		_particle.img->setScale(_scale);
		_particle.img->aniRender(CAMERA->getRelativeV2(_particle.pos[i]), _particle.ani[i]);
	}

	// �ı��� ���
	Vector2 backPos = _position;
	// �⺻ ���� ��ġ
	backPos.x += 30;
	backPos.y += 60;
	// ���� ���� ��ġ
	if (_backMove)
	{
		// ���� ���� ������
		backPos.y += 50;
	}
	_backImg->setScale(_scale);
	_backImg->aniRender(CAMERA->getRelativeV2(backPos), _backAni);
	
	// �Ӹ� ���
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani);

	_handL.render(_scale);
	_handR.render(_scale, true);

	// �� ���
	for (int i = 0; i < _sword.size(); i++)
	{
		_sword[i]->img->setScale(_scale);
		_sword[i]->img->setAngle((_sword[i]->angle) * (180 / PI));
		_sword[i]->img->render(CAMERA->getRelativeV2(_sword[i]->getPosition()));
	}

	_swordAtk.circleDebug.render(true);

	// ���� ������ ���
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
	// ���� ������ ���
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
			unsigned pattern = RANDOM->getFromIntTo(0, 3);

			switch (pattern)
			{
				// ź��
				case 0:
				{
					setPhase(BELIAL_PHASE::SHOOTING_READY);
				}
				break;
				// ��
				case 1:
				{
					setPhase(BELIAL_PHASE::SWORD_READY);
				}
				break;
				// ������
				case 2:
				{
					unsigned laserPattern = RANDOM->getFromIntTo(0, 3);

					switch (laserPattern)
					{
						// ������ ���� �߻�
						case 0: 
						{
							_laserNum = 0;
							setPhase(BELIAL_PHASE::LASER_R);
						}
						break;
						// ������ ���� �߻�
						case 1: 
						{
							_laserNum = 0;
							setPhase(BELIAL_PHASE::LASER_L);
						}
						break;
						// ������ �����Ƽ� �߻�
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
	// ���� �𷺼� ����
	switch (_direction)
	{
	case DIRECTION::UP:
	{
		// ���� ����
		_position.y -= _moving.force.y * timeElapsed;
		// ������ �Ϸ� �� �Ʒ���
		if (_moving.update(timeElapsed))
		{
			_direction = DIRECTION::DOWN;
		}
	}
	break;
	case DIRECTION::DOWN:
	{
		// �Ʒ��� ����
		_position.y += _moving.force.y * timeElapsed;
		// ������ �Ϸ� �� ����
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
	// �� �ִϸ��̼� �Ҵ�
	ani = new Animation;

	// ������ �ִϸ��̼� �Ҵ�
	laserHeadAni = new Animation;
	laserBodyAni = new Animation;

	// ������ ����
	position = pos;

	// �⺻ ���·� ����
	setState(HAND_STATE::IDLE);

	// ������ �̹��� ����
	laserHeadImg = IMAGE_MANAGER->findImage("Belial/Laser/Head");
	laserBodyImg = IMAGE_MANAGER->findImage("Belial/Laser/Body");

	// ������ �ִϸ��̼� �ʱ�ȭ
	laserHeadAni->init(laserHeadImg->getWidth(), laserHeadImg->getHeight(), laserHeadImg->getMaxFrameX(), laserHeadImg->getMaxFrameY());
	laserBodyAni->init(laserBodyImg->getWidth(), laserBodyImg->getHeight(), laserBodyImg->getMaxFrameX(), laserBodyImg->getMaxFrameY());
	
	// �����δ�.
	ZeroMemory(&moving, sizeof(moving));
	moving.force = Vector2(0, 800);

	// ������ �������� �ʱ�ȭ
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
		// �÷��̾� ��ǥ ����
		case HAND_STATE::MOVE:
		{
			// �÷��̾� ��ǥ���� �Ÿ��� ���ǵ� ������ ũ��
			if (fabsf(movePos.y - position.y) > moving.force.y * timeElapsed)
			{
				// �̵�
				position.y += moving.force.y * timeElapsed * ((movePos.y > position.y) ? (1) : (-1));				
			}
			// �̵��� �Ϸ��� ���
			else
			{
				// ������ ����
				position.y = movePos.y;
				// ������ ��Ʈ ��� ����
				for (int i = 0; i < laserRect.size(); i++)
				{
					laserRect[i] = FloatRect(Vector2(laserRect[i].getCenter().x, position.y), laserRect[i].getSize(), PIVOT::CENTER);
				}
				// ���ݷ�Ʈ ����
				atkRect = rectMakePivot(Vector2(atkRect.getCenter().x, position.y), atkRect.getSize(), PIVOT::CENTER);

				// ���� �غ�� ����
				setState(HAND_STATE::ATTACK_READY);
			}
		}
		break;
		// ���� �غ�
		case HAND_STATE::ATTACK_READY:
		{
			// �� �������� ������ �߻� �����Ӱ� ��ġ�ϸ�
			if (ani->getPlayIndex() == 8 && !laserHeadAni->isPlay() && !laserBodyAni->isPlay())
			{
				// ������ �߻� �� ����
				setState(HAND_STATE::ATTACK_START);
			}			
		}
		break;
		// ���⼭ ��������
		case HAND_STATE::ATTACK_START:
		{
			// ����
			laserAtk.attackRect(enemyType, enemyManager, atkRect);

			if (!ani->isPlay())
			{
				setState(HAND_STATE::ATTACK_FINAL);
				// ���� ID �ʱ�ȭ
				laserAtk.id.clear();
			}
		}
		break;
		// ������ ���� ��
		case HAND_STATE::ATTACK_FINAL:
		{
			// �������� ������ ����Ǹ�
			if (!laserHeadAni->isPlay() && !laserBodyAni->isPlay())
			{
				// �⺻ ���·� ����
				setState(HAND_STATE::IDLE);
			}
		}
		break;
	}

	ani->frameUpdate(timeElapsed);

	laserHeadAni->frameUpdate(timeElapsed);
	laserBodyAni->frameUpdate(timeElapsed);
}

void Belial::tagHandInfo::render(const float scale, bool bisymmetry)
{
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
			ani->setFPS(15);
			ani->start();

			laserHeadAni->stop();
			laserBodyAni->stop();
			laserHeadAni->setPlayFrame(0, 2, false, true);
			laserBodyAni->setPlayFrame(0, 2, false, true);
			laserHeadAni->setFPS(15);
			laserBodyAni->setFPS(15);	
		}
		break;
		case HAND_STATE::ATTACK_START:
		{
			laserHeadAni->start();
			laserBodyAni->start();
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
		}
		break;
	}
}
