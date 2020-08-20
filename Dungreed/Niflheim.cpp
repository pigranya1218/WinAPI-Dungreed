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
		_pillar[i].position.x += cosf(_pillar[i].angle) * 100;
		_pillar[i].position.y -= sinf(_pillar[i].angle) * 100;
	}

	ZeroMemory(&_moving, sizeof(_moving));
	_moving.delay = 3;
	_move_x = _move_y = 0;
	_active = true;
}

void Niflheim::release()
{

}

void Niflheim::update(float const timeElapsed)
{
	_count = RANDOM->getFromIntTo(0, 5);
	_move_x = RANDOM->getFromFloatTo(-200, 200);
	_move_y = RANDOM->getFromFloatTo(-200, 200);

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
			if (!_ani->isPlay())
			{
				_position = Vector2(_position.x + _move_x, _position.y + _move_y);
				setState(tagState::IDLE);
			}
		}
		break;
		case IDLE:
		{
			_pillaMod = tagAttackMod::PROTECT;
			//조건문은 후에 변경
			if (_moving.update(timeElapsed))
			{
				if (_count == 0)
				{
					//공격 이미지 변경후

					_pillaMod = tagAttackMod::SQUARE;
					//패턴 이동
				}
				else if (_count == 1)
				{
					//공격 이미지 변경 및 공격 패턴 변경
					_pillaMod = tagAttackMod::LINE;
					//패턴 이동
				}
				else if (_count == 2)
				{
					//공격 이미지 변경 및 공격 패턴 변경
					_pillaMod = tagAttackMod::CYCLONE;
					//패턴 이동
				}
				else if (_count == 3)
				{
					//공격 이미지 변경 및 공격 패턴 변경
					_pillaMod = tagAttackMod::ICECLE;
					//패턴 이동
				}
				_position = Vector2(_position.x + _move_x, _position.y + _move_y);
				setState(tagState::ATTACK);
			}
		}
		break;
		case ATTACK:
		{

			//공격종류






			if (_moving.update(timeElapsed))
			{
				setState(tagState::STURN);
			}
		}
		break;
		//몇초 지나면  다시 대기 상태 체력에따라 페이즈 변경역할
		case STURN:
		{
			if (_moving.update(timeElapsed))
			{
				_position = Vector2(_position.x + _move_x, _position.y + _move_y);
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
		case IDLE:
			break;
		case ATTACK:
			break;
		case STURN:
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


	//각 공격당 필라의 이동
	{
		switch (_pillaMod)
		{
		case PROTECT:
		{

			for (int i = 0; i < PILLAMAX; i++)
			{

				_pillar[i].angle += timeElapsed * 2;
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
				_pillar[i].angle += timeElapsed * 4;
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
				setState(tagState::IDLE);
			}
		}
		break;
		case CYCLONE:
		{
			for (int i = 0; i < PILLAMAX; i++)
			{
				_pillar[i].angle += timeElapsed * 2;
				if (_pillar[i].angle > PI2) _pillar[i].angle = 0;
				_pillar[i].position = _position;
				_pillar[i].position.x += cosf(_pillar[i].angle) * 100;
				_pillar[i].position.y -= sinf(_pillar[i].angle) * 100;
			}


			if (_moving.update(timeElapsed))
			{
				setState(tagState::IDLE);
			}
		}
		break;
		case LINE:
		{
			for (int i = 0; i < PILLAMAX; i++)
			{
				_pillar[i].angle += timeElapsed * 4;

				_pillar[i].position.x = (((WINSIZEX / 2) / 2) + ((i * 100)*_scale));
				_pillar[i].position.y = ((WINSIZEY / 2) / 2);
			}
			if (_moving.update(timeElapsed))
			{
				setState(tagState::IDLE);
			}
		}
		break;
		case ARROW:
		{
			if (_moving.update(timeElapsed))
			{
				setState(tagState::IDLE);
			}
		}
		break;
		case ICECLE:
		{
			if (!_ani->isPlay())
			{
				setState(tagState::IDLE);
			}
		}
		break;
		case SPEAR:
		{
			if (!_ani->isPlay())
			{
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

		_pillar[i].img->setAngle((_pillar[i].angle * (180 / PI)) + 90);

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
		_img = IMAGE_MANAGER->findImage("Niflheim/Spawn");
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
		_img = IMAGE_MANAGER->findImage("Niflheim/Idle");
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
			_img = IMAGE_MANAGER->findImage("Niflheim/Idle");
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
			_img = IMAGE_MANAGER->findImage("Niflheim/Attack_1");
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
		_img = IMAGE_MANAGER->findImage("Niflheim/Attack_1");
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, false);
		_ani->setFPS(15);
		_ani->start();

	}
	break;

	}
}
