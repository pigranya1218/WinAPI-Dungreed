#include "stdafx.h"
#include "EnemyManager.h"
#include "Niflheim.h"

void Niflheim::init(const Vector2& pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(tagState::ENTER);
	_phase = tagPhase::FIRST;
	_pillaMod = tagAttackMod::PROTECT;


	_position = Vector2(WINSIZEX / 2, WINSIZEY / 2);

	_scale = 4;

	for (int i = 0; i < PILLAMAX ; i++)
	{
		ZeroMemory(&_pillar[i], sizeof(_pillar[i]));
		_pillar[i].ani = new Animation;

		_pillar[i].img = IMAGE_MANAGER->findImage("Niflheim/Pillar");
		_pillar[i].ani->init(_pillar[i].img->getWidth(), _pillar[i].img->getHeight(), _pillar[i].img->getMaxFrameX(), _pillar[i].img->getMaxFrameY());
		_pillar[i].ani->setDefPlayFrame(false, false);
		_pillar[i].ani->setFPS(15);
		_pillar[i].ani->start();

		_pillar[i].angle = PI / 2 * i;

		_pillar[i].position = _position;
		_pillar[i].position.x += cosf(_pillar[i].angle) * 200;
		_pillar[i].position.y -= sinf(_pillar[i].angle) * 200;


	}

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 8;
	_move_x = _move_y = 0;
	_active = true;


	_shooting.init("Belial/Bullet", "Belial/Bullet_FX", Vector2(300, 300), _scale, 0.15, 3, false, true, true, false, false, false);
	_shooting.attackInit(3, 5, 1, 25);
	_shooting.angle = 0;


	_myEnemyType = static_cast<int>(ENEMY_TYPE::NIFLHEIM);
}

void Niflheim::release()
{

}

void Niflheim::update(float const timeElapsed)
{
	_count = RANDOM->getFromIntTo(0,5);
	const Vector2 playerPos = _enemyManager->getPlayerPos();



	_ani->frameUpdate(timeElapsed);
	for (int i = 0; i < 4; i++)
	{
		_pillar[i].angle += timeElapsed * 2;
		if (_pillar[i].angle > PI2) _pillar[i].angle = 0;
		_pillar[i].ani->frameUpdate(timeElapsed);

		_pillar[i].position = _position;
		//포지션과의 거리
		_pillar[i].position.x += cosf(_pillar[i].angle) * 200;
		_pillar[i].position.y -= sinf(_pillar[i].angle) * 200;
	}

	//페이즈 및 패턴
	switch (_phase)
	{
	case tagPhase::FIRST:
	{
		switch (_State)
		{
		case ENTER:
		{
			//후에 등장 이벤트 종료로 변경
			if (!_ani->isPlay())
			{
				_position.x = RANDOM->getFromFloatTo(100, WINSIZEX +100);
				_position.y = RANDOM->getFromFloatTo(100, WINSIZEY +100);
				_position = Vector2(_position.x, _position.y);
				setState(tagState::IDLE);
			}
		}
		break;
		case IDLE:
		{
			//아이들 상태일때 4가지중 하나로 상태라면 다시 기본상태로 복구
			if (_pillaMod == tagAttackMod::ARROW || _pillaMod == tagAttackMod::SQUARE || _pillaMod == tagAttackMod::CYCLONE || _pillaMod == tagAttackMod::LINE)
			{
				_pillaMod = tagAttackMod::PROTECT;
			}
			//조건문은 후에 변경
			if (_moving.update(timeElapsed))
			{
				if (_count == 0)
				{
					//공격 이미지 변경후

					_pillaMod = tagAttackMod::SQUARE;

				}
				else if (_count == 1)
				{
					//공격 이미지 변경 및 공격 패턴 변경
					_pillaMod = tagAttackMod::LINE;
	
				}
				else if (_count == 2)
				{
					_boost = 0;
					for (int i = 0; i < PILLAMAX; i++)
					{
						_pillar[i].angle = PI / 2 * i;
					}
					//공격 이미지 변경 및 공격 패턴 변경
					_pillaMod = tagAttackMod::CYCLONE;

				}
				else if (_count == 3)
				{
					//공격 이미지 변경 및 공격 패턴 변경
					_pillaMod = tagAttackMod::ICECLE;
	
				}
				_position = Vector2(_position.x, _position.y);
				setState(tagState::ATTACK);
			}
		}
		break;
		case ATTACK:
		{
			if (_shooting.delayUpdate(timeElapsed))
			{
				// 총알 발사 위치
				Vector2 bulletPos = _position;
				bulletPos.x += 30;
				bulletPos.y += 30;

				// 총알 4개씩 발사
				for (int i = 0; i < 8; i++)
				{
					_shooting.createBullet(bulletPos, (_shooting.angle + (PI / 4)));
					_shooting.fireBullet(_myEnemyType, _enemyManager);
				}
				_shooting.angle += timeElapsed * 8.0f;
			}

			//일정 체력이 달시 피격가능상태로 변경
			if (_moving.update(timeElapsed))
			{
				setState(tagState::STURN);
			}
		}
		break;
		//몇초 지나면  다시 대기 상태 체력에따라 페이즈 변경역할
		case STURN:
		{
			//일정시간후 다시 무적상태로 변경
			if (_moving.update(timeElapsed))
			{
				_position.x = RANDOM->getFromFloatTo(100, WINSIZEX + 100);
				_position.y = RANDOM->getFromFloatTo(100, WINSIZEY + 100);
				_position = Vector2(_position.x, _position.y);
				//_phase = tagPhase::SECOND;
				setState(tagState::IDLE);
			} 
		}
		break;
		}
	}
	case tagPhase::SECOND:
	{
		switch (_State)
		{
		case ENTER:
		{
			//후에 등장 이벤트 종료로 변경
			if (!_ani->isPlay())
			{
				_position.x = RANDOM->getFromFloatTo(100, WINSIZEX + 100);
				_position.y = RANDOM->getFromFloatTo(100, WINSIZEY + 100);
				_position = Vector2(_position.x, _position.y);
				setState(tagState::IDLE);
			}
		}
		break;
		case IDLE:
		{
			//아이들 상태일때 4가지중 하나로 상태라면 다시 기본상태로 복구
			if (_pillaMod == tagAttackMod::ARROW || _pillaMod == tagAttackMod::SQUARE || _pillaMod == tagAttackMod::CYCLONE || _pillaMod == tagAttackMod::LINE)
			{
				_pillaMod = tagAttackMod::PROTECT;
			}
			//조건문은 후에 변경
			if (_moving.update(timeElapsed))
			{
				if (_count == 0)
				{
					//공격 이미지 변경후

					_pillaMod = tagAttackMod::SQUARE;

				}
				else if (_count == 1)
				{
					//공격 이미지 변경 및 공격 패턴 변경
					_pillaMod = tagAttackMod::LINE;

				}
				else if (_count == 2)
				{
					_boost = 0;
					for (int i = 0; i < PILLAMAX; i++)
					{
						_pillar[i].angle = PI / 2 * i;
					}
					//공격 이미지 변경 및 공격 패턴 변경
					_pillaMod = tagAttackMod::CYCLONE;

				}
				else if (_count == 3)
				{
					//공격 이미지 변경 및 공격 패턴 변경
					_pillaMod = tagAttackMod::ICECLE;

				}
				_position = Vector2(_position.x, _position.y);
				setState(tagState::ATTACK);
			}
		}
		break;
		case ATTACK:
		{


			//일정 체력이 달시 피격가능상태로 변경
			if (_moving.update(timeElapsed))
			{
				setState(tagState::STURN);
			}
		}
		break;
		//몇초 지나면  다시 대기 상태 체력에따라 페이즈 변경역할
		case STURN:
		{
			//일정시간후 다시 무적상태로 변경
			if (_moving.update(timeElapsed))
			{
				_position.x = RANDOM->getFromFloatTo(100, WINSIZEX + 100);
				_position.y = RANDOM->getFromFloatTo(100, WINSIZEY + 100);
				_position = Vector2(_position.x, _position.y);
				//_phase = tagPhase::SECOND;
				setState(tagState::IDLE);
			}
		}
		break;
		}
	}
	break;
	case tagPhase::LAST:
	{
		switch (_State)
		{
		case IDLE:
			break;
		case ATTACK:
			break;
		case STURN:
			break;
		case DIE:
			break;
		}
	}
	break;
	}


	//각 공격당 필라의 이동 및 위치
	{
		switch (_pillaMod)
		{
		case PROTECT:
		{

			for (int i = 0; i < PILLAMAX; i++)
			{

				_pillar[i].angle += timeElapsed;
				if (_pillar[i].angle > PI2) _pillar[i].angle = 0;
				_pillar[i].position = _position;
				_pillar[i].position.x += cosf(_pillar[i].angle) * 200;
				_pillar[i].position.y -= sinf(_pillar[i].angle) * 200;
			}

		}
		break;
		case SQUARE:
		{
			for (int i = 0; i < PILLAMAX; i++)
			{
				_pillar[i].angle += timeElapsed;
				//if (_pillar[i].angle > PI2) _pillar[i].angle = 0;
				if (i == 0)
				{
					_pillar[i].position.x = ((WINSIZEX / 2) / 2);
					_pillar[i].position.y = ((WINSIZEY / 2) / 2);
				}
				
				if (i == 1)
				{
					_pillar[i].position.x = (WINSIZEX / 2) + ((WINSIZEX / 2) / 2);
					_pillar[i].position.y = (WINSIZEX / 2) + ((WINSIZEY / 2) / 2);
				}
				if (i == 2)
				{
					_pillar[i].position.x = (WINSIZEX / 2) / 2;
					_pillar[i].position.y = (WINSIZEX / 2) + ((WINSIZEY / 2) / 2);
				}
				if (i == 3)
				{
					_pillar[i].position.x = (WINSIZEX / 2) + ((WINSIZEX / 2) / 2);
					_pillar[i].position.y = ((WINSIZEY / 2) / 2);
				}
				
			}


			if (_moving.update(timeElapsed))
			{
				for (int i = 0; i < PILLAMAX; i++)
				{
					_pillar[i].angle = PI / 2 * i;
				}
				_position.x = RANDOM->getFromFloatTo(0, WINSIZEX);
				_position.y = RANDOM->getFromFloatTo(0, WINSIZEY);
				_position = Vector2(_position.x, _position.y);
				setState(tagState::IDLE);
			}
		}
		break;
		case CYCLONE:
		{
			if (_boost < 10)
			{
				//사이클 시 가속도
				_boost += 0.1;
			}
			for (int i = 0; i < PILLAMAX; i++)
			{
				_pillar[i].angle += timeElapsed * _boost;
				if (_pillar[i].angle > PI2) _pillar[i].angle = 0;
				_pillar[i].position = _position;
				_pillar[i].position.x += cosf(_pillar[i].angle) * 130;
				_pillar[i].position.y -= sinf(_pillar[i].angle) * 130;
			}


			if (_moving.update(timeElapsed))
			{
				//다시 초기화해서 기둥 사이 보정 
				for (int i = 0; i < PILLAMAX; i++)
				{
					_pillar[i].angle = PI / 2 * i;
				}
				_position.x = RANDOM->getFromFloatTo(100, WINSIZEX + 100);
				_position.y = RANDOM->getFromFloatTo(100, WINSIZEY + 100);
				_position = Vector2(_position.x, _position.y);
				setState(tagState::IDLE);
			}
		}
		break;
		case LINE:
		{
			for (int i = 0; i < PILLAMAX; i++)
			{
				_pillar[i].angle += timeElapsed;

				_pillar[i].position.x = (((WINSIZEX / 2) / 2) + ((i * 100)*_scale));
				_pillar[i].position.y = ((WINSIZEY / 2) / 2);
			}
			if (_moving.update(timeElapsed))
			{
				for (int i = 0; i < PILLAMAX; i++)
				{
					_pillar[i].angle = PI / 2 * i;
				}
				_position.x = RANDOM->getFromFloatTo(100, WINSIZEX + 100);
				_position.y = RANDOM->getFromFloatTo(100, WINSIZEY + 100);
				_position = Vector2(_position.x, _position.y);
				setState(tagState::IDLE);
			}
		}
		break;
		case ARROW:
		{
			for (int i = 0; i < PILLAMAX; i++)
			{
				_pillar[i].angle += timeElapsed;

				_pillar[i].position.x = (((WINSIZEX / 2) / 2) + ((i * 100)*_scale));
				_pillar[i].position.y = ((WINSIZEY / 2) / 2);
			}




			if (_moving.update(timeElapsed))
			{
				for (int i = 0; i < PILLAMAX; i++)
				{
					_pillar[i].angle = PI / 2 * i;
				}
				_position.x = RANDOM->getFromFloatTo(100, WINSIZEX + 100);
				_position.y = RANDOM->getFromFloatTo(100, WINSIZEY + 100);
				_position = Vector2(_position.x, _position.y);
				setState(tagState::IDLE);
			}
		}
		break;
		case ICECLE:
		{
			if (!_ani->isPlay())
			{
				for (int i = 0; i < PILLAMAX; i++)
				{
					_pillar[i].angle = PI / 2 * i;
				}
				_position.x = RANDOM->getFromFloatTo(100, WINSIZEX + 100);
				_position.y = RANDOM->getFromFloatTo(100, WINSIZEY + 100);
				_position = Vector2(_position.x, _position.y);
				setState(tagState::IDLE);
			}
		}
		break;
		case SPEAR:
		{
			if (!_ani->isPlay())
			{
				for (int i = 0; i < PILLAMAX; i++)
				{
					_pillar[i].angle = PI / 2 * i;
				}
				_position.x = RANDOM->getFromFloatTo(100, WINSIZEX + 100);
				_position.y = RANDOM->getFromFloatTo(100, WINSIZEY + 100);
				_position = Vector2(_position.x, _position.y);
				setState(tagState::IDLE);
			}
		}
		break;
		}
	}
}


void Niflheim::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	for (int i = 0; i < 4; i++)
	{
		_pillar[i].img->setScale(4);

		//(필라의 각도 에서 )
		if (_pillaMod == tagAttackMod::PROTECT|| _pillaMod == tagAttackMod::CYCLONE)
		{
			_pillar[i].img->setAngle((_pillar[i].angle * (180 / PI)) + 90);
		}
		if (_pillaMod == tagAttackMod::SQUARE|| _pillaMod == tagAttackMod::LINE)
		{
			_pillar[i].img->setAngle((_pillar[i].angle * (360/ PI)));
		}
		//_pillar[i].img->setAnglePos(Vector2((_pillar[i].img->getFrameSize().x * 4) * 0.5f, (_pillar[i].img->getFrameSize().y * 4) * 0.5f));
		_pillar[i].img->aniRender(CAMERA->getRelativeV2(_pillar[i].position), _pillar[i].ani);
	}
}

void Niflheim::setState(tagState state)
{
	_State = state;
	switch (state)
	{
	case ENTER:
	{
		_ani->stop();
		_imageName = "Niflheim/Spawn";
		_img = IMAGE_MANAGER->findImage(_imageName);
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, false);
		_ani->setFPS(15);
		_ani->start();

	}
	break;
	case IDLE:
	case STURN:
	{
		_ani->stop();
		_imageName = "Niflheim/Idle";
		_img = IMAGE_MANAGER->findImage(_imageName);
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, true);
		_ani->setFPS(15);
		_ani->start();


	}
	break;
	case ATTACK:
	{
		switch (_pillaMod)
		{
		case tagAttackMod::PROTECT:
		case tagAttackMod::CYCLONE:
		case tagAttackMod::LINE:
		case tagAttackMod::SQUARE:
		{
			_ani->stop();
			_imageName = "Niflheim/Idle";
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}
		break;

		case tagAttackMod::ICECLE:
		case tagAttackMod::SPEAR:
		case tagAttackMod::ARROW:
		{
			_ani->stop();
			_imageName = "Niflheim/Attack_1";
			_img = IMAGE_MANAGER->findImage(_imageName);
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(15);
			_ani->start();

		}
		break;
		}

	}
	break;
	case::DIE:
	{
		_ani->stop();
		_imageName = "Niflheim/Die";
		_img = IMAGE_MANAGER->findImage(_imageName);
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, false);
		_ani->setFPS(15);
		_ani->start();

	}
	break;

	}
}

void Niflheim::hitReaction(const Vector2 & playerPos, Vector2 & moveDir, const float timeElapsed)
{
	if (_hit.isHit)
	{
		if (_hit.update(timeElapsed))
		{
			switch (_State)
			{
			case STURN:
			{






			}
				break;

			}
		}
	}
}
