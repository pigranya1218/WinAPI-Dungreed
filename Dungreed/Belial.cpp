#include "stdafx.h"
#include "EnemyManager.h"
#include "Belial.h"

void Belial::init(const Vector2 & pos)
{
	// �ִϸ��̼� �Ҵ�
	_ani = new Animation;
	_backAni = new Animation;

	// �� �̹��� ����
	_swordImg = IMAGE_MANAGER->findImage("Belial/Sword");

	// �ı��� �ʱ�ȭ
	_backImg = IMAGE_MANAGER->findImage("Belial/Back/Circle");
	_backAni->init(_backImg->getWidth(), _backImg->getHeight(), _backImg->getMaxFrameX(), _backImg->getMaxFrameY());
	_backAni->setDefPlayFrame(false, true);
	_backAni->setFPS(15);
	_backAni->start();

	// ó�� ���´� �⺻
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
	_attackCycle.delay = 2;

	ZeroMemory(&_hit, sizeof(_hit));
	_hit.delay = 0.3;

	_active = true;
	_laserNum = 0;

	_curHp = _maxHp = 300;

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
}

void Belial::update(float const timeElapsed)
{
	_playerPos = _enemyManager->getPlayerPos();

	Vector2 moveDir(0, 0);
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
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
						bulletPos.y += 60;

						// �Ѿ� 4���� �߻�
						for (int i = 0; i < 4; i++)
						{
							_shooting.createBullet(bulletPos, (_shooting.angle + (PI / 2)));
							_shooting.fireBullet(_myEnemyType, _enemyManager);
						}
						_shooting.angle += timeElapsed * 8.0f;
					}
					// ���� �ð��� ������
					if (_attackCycle.update(timeElapsed * 0.2f))
					{
						setPhase(BELIAL_PHASE::SHOOTING_FINAL);
					}
				}
				break;
				case BELIAL_PHASE::SHOOTING_FINAL:
				{
					// ���� ��� �ݾ�����
					if (!_ani->isPlay())
					{
						setState(ENEMY_STATE::IDLE);
					}
				}
				break;
				case BELIAL_PHASE::SWORD_READY:
				{
					// �����̸��� ���� ����
					if (_swordBullet.delayUpdate(timeElapsed))
					{
						tagSwordPosAngle sword;
						ZeroMemory(&sword, sizeof(sword));

						sword.pos = _swordPosAngle[_swordPosAngle.size() - 1].pos;
						sword.pos.x += 200;

						_swordPosAngle.push_back(sword);
					}
					// ���� ��� ���������
					if(_swordPosAngle.size() >= 6)
					{
						// ���� �߻��Ѵ�
						setPhase(BELIAL_PHASE::SWORD_START);
					}
					// ������ ��� ������Ʈ�Ѵ�
					for (int i = 0; i < _swordPosAngle.size(); i++)
					{
						_swordPosAngle[i].angle = getAngle(_swordPosAngle[i].pos.x, _swordPosAngle[i].pos.y, _playerPos.x, _playerPos.y);
					}
				}
				break;
				case BELIAL_PHASE::SWORD_START:
				{
					for (int i = 0; i < _swordPosAngle.size(); i++)
					{
						_swordPosAngle[i].angle = getAngle(_swordPosAngle[i].pos.x, _swordPosAngle[i].pos.y, _playerPos.x, _playerPos.y);
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
				// ������ ������ �߻�
				case BELIAL_PHASE::LASER_R:
				{
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

		}
		break;
	}
	hitReaction(_playerPos, moveDir, timeElapsed);

	_ani->frameUpdate(timeElapsed);
	_backAni->frameUpdate(timeElapsed);

	_handL.update(timeElapsed);
	_handR.update(timeElapsed);

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void Belial::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);

	// �ı��� ���
	Vector2 backPos = _position;
	backPos.x += 30;
	backPos.y += 60;
	/*if (_phase == BELIAL_PHASE::SHOOTING && _ani->getPlayIndex() >= 6)
	{
		backPos.y += 20 * _ani->getPlayIndex();
	}*/
	_backImg->setScale(_scale);
	_backImg->aniRender(CAMERA->getRelativeV2(backPos), _backAni);
	
	// �Ӹ� ���
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani);

	for (int i = 0; i < _swordPosAngle.size(); i++)
	{
		_swordImg->setAngle(_swordPosAngle[i].angle * (180 / PI));
		_swordImg->setScale(_scale);
		_swordImg->render(CAMERA->getRelativeV2(_swordPosAngle[i].pos));
	}

	_handL.render(_scale);
	_handR.render(_scale, true);
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
			pattern = 2;

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
			_ani->setDefPlayFrame(false, false);
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
			tagSwordPosAngle sword;
			ZeroMemory(&sword, sizeof(sword));

			sword.pos = _position;
			sword.pos.x -= 400;

			_swordPosAngle.push_back(sword);
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
}

void Belial::tagHandInfo::update(const float timeElapsed)
{
	switch (state)
	{
		case HAND_STATE::IDLE:
		{

		}
		break;
		case HAND_STATE::MOVE:
		{
			if (fabsf(movePos.y - position.y) > moving.force.y * timeElapsed * 5)
			{
				position.y += moving.force.y * timeElapsed * ((movePos.y > position.y) ? (1) : (-1));				
			}
			else
			{
				position.y = movePos.y;
				for (int i = 0; i < laserRect.size(); i++)
				{
					laserRect[i] = FloatRect(Vector2(laserRect[i].getCenter().x, position.y + 20), laserRect[i].getSize(), PIVOT::CENTER);
					//laserRect[i] = rectMakePivot(Vector2(laserRect[i].getCenter().x, position.y), laserRect[i].getSize(), PIVOT::CENTER);
				}
				setState(HAND_STATE::ATTACK_READY);
			}
		}
		break;
		case HAND_STATE::ATTACK_READY:
		{
			if (ani->getPlayIndex() == 8 && !laserHeadAni->isPlay() && !laserBodyAni->isPlay())
			{
				setState(HAND_STATE::ATTACK_START);
			}			
		}
		break;
		// ���⼭ ��������
		case HAND_STATE::ATTACK_START:
		{
			if (!ani->isPlay())
			{
				setState(HAND_STATE::ATTACK_FINAL);
			}
		}
		break;
		case HAND_STATE::ATTACK_FINAL:
		{
			if (!laserHeadAni->isPlay() && !laserBodyAni->isPlay())
			{
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

	if (laserBodyAni->isPlay() && laserHeadAni->isPlay())
	{
		laserHeadImg->setScale(scale);
		laserHeadImg->aniRender(CAMERA->getRelativeV2(laserRect[0].getCenter()), laserHeadAni, bisymmetry);

		for (int i = 1; i < laserRect.size(); i++)
		{
			laserBodyImg->setScale(scale);
			laserBodyImg->aniRender(CAMERA->getRelativeV2(laserRect[i].getCenter()), laserBodyAni, bisymmetry);
		}
	}
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
