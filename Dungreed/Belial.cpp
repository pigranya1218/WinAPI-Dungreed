#include "stdafx.h"
#include "EnemyManager.h"
#include "Belial.h"

void Belial::init(const Vector2 & pos)
{
	{
	_head._Ani = new Animation;
	_rHand._Ani = new Animation;
	_lHand._Ani = new Animation;
	_back._Ani = new Animation;
	}
	{
		setHeadState(ENEMY_STATE::IDLE);
		setRHandState(ENEMY_STATE::IDLE);
		setLHandState(ENEMY_STATE::IDLE);
	}

	{
		_scale = 5;
		_head._size = _head._img->getFrameSize() * _scale;
		_rHand._size = _rHand._img->getFrameSize() * _scale;
		_lHand._size = _lHand._img->getFrameSize() * _scale;
	}

	{
		_head._Position  = pos;
		_rHand._Position.x = _head._Position.x - _rHand._img->getWidth() / 2;
		_lHand._Position.x = _head._Position.x + _lHand._img->getWidth() / 2;

		_rHand._Position = Vector2((_rHand._Position.x-(70* _scale)), _head._Position.y + 200);
		_lHand._Position = Vector2((_lHand._Position.x+ (70 * _scale)), _head._Position.y + 200);
	}

	_rHand._Rect = rectMakePivot(_rHand._Position,_rHand._size, PIVOT::CENTER);
	_lHand._Rect = rectMakePivot(_lHand._Position,_lHand._size, PIVOT::CENTER);

	ZeroMemory(&_head._moving, sizeof(_head._moving));
	_head._moving.gravity.y = 30;
	_head._moving.delay = 1;

	ZeroMemory(&_rHand._moving, sizeof(_rHand._moving));
	_rHand._moving.force.y = 300;
	_rHand._moving.delay = 3;

	ZeroMemory(&_lHand._moving, sizeof(_lHand._moving));
	_lHand._moving.force.y = 300;
	_lHand._moving.delay = 3;



	ZeroMemory(&_head._attaking, sizeof(_head._attaking));
	_head._attaking.delay = 4;

	ZeroMemory(&_rHand._attaking, sizeof(_rHand._attaking));
	_rHand._attaking.delay = 2;

	ZeroMemory(&_lHand._attaking, sizeof(_lHand._attaking));
	_lHand._attaking.delay = 2;


	_force = Vector2(0,0);
	_position = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	_detectRange = 30000;
}

void Belial::release()
{
	_head._Ani->release();
	SAFE_DELETE(_head._Ani);

	_back._Ani->release();
	SAFE_DELETE(_back._Ani);

	_rHand._Ani->release();
	SAFE_DELETE(_rHand._Ani);

	_lHand._Ani->release();
	SAFE_DELETE(_lHand._Ani);

}

void Belial::update(float const timeElapsed)
{
	_count = RANDOM->getFromIntTo(0, 10);
	const Vector2 playerPos = _enemyManager->getPlayerPos();

	Vector2 _moveDir(0, 0);

	_head._size = _head._img->getFrameSize() * _scale;

	_head._moveDir = _moveDir;
	_rHand._moveDir = _moveDir;
	_lHand._moveDir = _moveDir;


	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	switch (_head._State)
	{
	case ENEMY_STATE::IDLE:
	{
		_direction = (_head._Position.y > _position.y) ? (DIRECTION::UP) : (DIRECTION::DOWN);

		if (_head._moving.update(timeElapsed))
		{
			_head._moving.gravity = _head._moving.gravity * (_direction == DIRECTION::UP ? (-1) : (1));
		}
		if (_head._attaking.update(timeElapsed) && _rHand._State == ENEMY_STATE::IDLE)
		{
			setHeadState(ENEMY_STATE::ATTACK);
		}

	}

	case ENEMY_STATE::MOVE:
	{

	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		_head._moving.gravity.y = 0;

		if (!_head._Ani->isPlay())
		{
			_head._Ani->stop();
			_head._Ani->setPlayFrame(6, 10, false, false);
			_head._Ani->start();
		}
		if (_head._attaking.update(timeElapsed))
		{
			_head._moving.gravity.y = 30.;
			setHeadState(ENEMY_STATE::IDLE);
		}
	}
	break;

	case ENEMY_STATE::DIE:
	{

	}
	break;
	}

	if (_head._State == ENEMY_STATE::IDLE)
	{
		switch (_rHand._State)
		{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				// 계속 움직임
				_rHand._moving.angle = RANDOM->getFromFloatTo(0, PI2);
				if (_lHand._State == ENEMY_STATE::IDLE)
				{
					setRHandState(ENEMY_STATE::MOVE);
				}
			}
		}
		break;

		//움직이고 
		case ENEMY_STATE::MOVE:
		{
			_rHand._moveDir.y -= sinf(_rHand._moving.angle)* (timeElapsed *_rHand._moving.force.y);
			setPosition(_position + _rHand._moveDir);

			_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

			_rHand._moving.angle = getAngle(_rHand._Position.x, _rHand._Position.y, playerPos.x, playerPos.y);
			_rHand._moving.force.y = HANDSPEED;

			if (_rHand._attaking.update(timeElapsed))
			{
				setRHandState(ENEMY_STATE::ATTACK);
			}
		}
		break;
		//발사
		case ENEMY_STATE::ATTACK:
		{
			if (!_rHand._Ani->isPlay())
			{
				_count++;

				_rHand._Ani->stop();
				_rHand._Ani->setPlayFrame(11, 15, false, true);
				_rHand._Ani->start();
			}
			if (_rHand._attaking.update(timeElapsed))
			{
				setRHandState(ENEMY_STATE::IDLE);
				if (_count % 3 == 0)
				{
					setLHandState(ENEMY_STATE::MOVE);
				}
			}

		}
		break;

		case ENEMY_STATE::DIE:
			break;
		}
	}
	switch (_lHand._State)
	{

	case ENEMY_STATE::IDLE:
	{
		if (_isDetect)
		{
			// 계속 움직임
			_lHand._moving.angle = RANDOM->getFromFloatTo(0, PI2);
		}
		if (_lHand._moving.update(timeElapsed))
		{

		}
	}
	break;

	//움직이고 
	case ENEMY_STATE::MOVE:
	{
		_lHand._moveDir.y -= sinf(_lHand._moving.angle)* (timeElapsed *_lHand._moving.force.y);
		setPosition(_position + _lHand._moveDir);

		_direction = (playerPos.x > _position.x) ? (DIRECTION::RIGHT) : (DIRECTION::LEFT);

		_lHand._moving.angle = getAngle(_lHand._Position.x, _lHand._Position.y, playerPos.x, playerPos.y);
		_lHand._moving.force.y = HANDSPEED;

		if (_lHand._attaking.update(timeElapsed))
		{
			setLHandState(ENEMY_STATE::ATTACK);
			setRHandState(ENEMY_STATE::IDLE);
		}
	}
	break;
	//발사
	case ENEMY_STATE::ATTACK:
	{
		if (!_lHand._Ani->isPlay())
		{
			_lHand._Ani->stop();
			_lHand._Ani->setPlayFrame(11, 15, false, true);
			_lHand._Ani->start();
		}
		if (_lHand._attaking.update(timeElapsed))
		{
			setLHandState(ENEMY_STATE::IDLE);
		}

	}
	break;

	case ENEMY_STATE::DIE:
		break;

	}


	//프레임 업데이트
	{
		_back._Ani->frameUpdate(timeElapsed);
		_head._Ani->frameUpdate(timeElapsed);
		_rHand._Ani->frameUpdate(timeElapsed);
		_lHand._Ani->frameUpdate(timeElapsed);
	}
	//랙트
	{
		_head._Rect = rectMakePivot(_head._Position, _head._size, PIVOT::CENTER);
		_rHand._Rect = rectMakePivot(_rHand._Position, _rHand._size, PIVOT::CENTER);
		_lHand._Rect = rectMakePivot(_lHand._Position, _lHand._size, PIVOT::CENTER);
	}

	{
		_back._backimg = IMAGE_MANAGER->findImage("Belial/Back");
		_back._Ani->init(_back._backimg->getWidth(), _back._backimg->getHeight(), _back._backimg->getMaxFrameX(), _back._backimg->getMaxFrameY());
		_back._Ani->setDefPlayFrame(false, true);
		_back._Ani->setFPS(10);
		_back._Ani->start();
	}

	_head._moveDir.y += (_head._moving.gravity.y * timeElapsed);
	_head._Position = (_head._Position + _head._moveDir);

	_rHand._Position = (_rHand._Position + _rHand._moveDir);
	_lHand._Position = (_lHand._Position + _lHand._moveDir);

}

void Belial::render()
{
	_back._backimg->setScale(_scale);
	_back._backimg->aniRender(CAMERA->getRelativeV2(Vector2(_head._Position.x, (_head._Rect.bottom) - (35 * _scale))), _back._Ani, 0);

	_head._img->setScale(_scale);
	_head._img->aniRender(CAMERA->getRelativeV2(_head._Position), _head._Ani, 0);

	_rHand._img->setScale(_scale);
	_rHand._img->aniRender(CAMERA->getRelativeV2(_rHand._Position), _rHand._Ani, 0);

	_lHand._img->setScale(_scale);
	_lHand._img->aniRender(CAMERA->getRelativeV2(_lHand._Position), _lHand._Ani,1);


	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_head._Rect));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rHand._Rect));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_lHand._Rect));
}

void Belial::setHeadState(ENEMY_STATE headState)
{
	_head._State = headState;


	switch (headState)
	{
	case ENEMY_STATE::IDLE :
	{
		_head._Rect = rectMakePivot(_head._Position, _size, PIVOT::CENTER);
		_head._img = IMAGE_MANAGER->findImage("Belial/Head/Idle");
		_head._Ani->stop();
		_head._Ani->init(_head._img->getWidth(), _head._img->getHeight(), _head._img->getMaxFrameX(), _head._img->getMaxFrameY());
		_head._Ani->setDefPlayFrame(false,true);
		_head._Ani->setFPS(10);
		_head._Ani->start();

	}
		break;
	case ENEMY_STATE::ATTACK:
	{
		_head._img = IMAGE_MANAGER->findImage("Belial/Head/Attack");
		_head._Ani->stop();
		_head._Ani->init(_head._img->getWidth(), _head._img->getHeight(), _head._img->getMaxFrameX(), _head._img->getMaxFrameY());
		_head._Ani->setDefPlayFrame(false, false);
		_head._Ani->setFPS(10);
		_head._Ani->start();
	}
	break;
	case ENEMY_STATE::DIE:
	{
	}
	break;

	}
}

void Belial::setRHandState(ENEMY_STATE RhandState)
{
	_rHand._State = RhandState;
	switch (RhandState)
	{
	case ENEMY_STATE::IDLE:
	case ENEMY_STATE::MOVE:
	{
		_rHand._Ani->stop();
		_rHand._img = IMAGE_MANAGER->findImage("Belial/Hand/Idle");
		_rHand._Ani->init(_rHand._img->getWidth(), _rHand._img->getHeight(), _rHand._img->getMaxFrameX(), _rHand._img->getMaxFrameY());
		_rHand._Ani->setDefPlayFrame(false, true);
		_rHand._Ani->setFPS(10);
		_rHand._Ani->start();





	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		_rHand._Ani->stop();
		_rHand._img = IMAGE_MANAGER->findImage("Belial/Hand/Attack");
		_rHand._Ani->init(_rHand._img->getWidth(), _rHand._img->getHeight(), _rHand._img->getMaxFrameX(), _rHand._img->getMaxFrameY());
		_rHand._Ani->setDefPlayFrame(false, false);
		_rHand._Ani->setFPS(10);
		_rHand._Ani->start();







	}
	break;
	case ENEMY_STATE::DIE:
	{
	}
	break;

	}
}

void Belial::setLHandState(ENEMY_STATE LhandState)
{
	_lHand._State = LhandState;
	switch (LhandState)
	{
	case ENEMY_STATE::IDLE:
	case ENEMY_STATE::MOVE:
	{
		_lHand._Ani->stop();
		_lHand._img = IMAGE_MANAGER->findImage("Belial/Hand/Idle");
		_lHand._Ani->init(_lHand._img->getWidth(), _lHand._img->getHeight(), _lHand._img->getMaxFrameX(), _lHand._img->getMaxFrameY());
		_lHand._Ani->setDefPlayFrame(false, true);
		_lHand._Ani->setFPS(15);
		_lHand._Ani->start();

	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		_lHand._Ani->stop();
		_lHand._img = IMAGE_MANAGER->findImage("Belial/Hand/Attack");
		_lHand._Ani->init(_lHand._img->getWidth(), _lHand._img->getHeight(), _lHand._img->getMaxFrameX(), _lHand._img->getMaxFrameY());
		_lHand._Ani->setDefPlayFrame(false, true);
		_lHand._Ani->setFPS(8);
		_lHand._Ani->start();

	}
	break;
	case ENEMY_STATE::DIE:
	{
	}
	break;
	}
}

bool Belial::playerCollision(const Vector2 & playerPos)
{
	if (_rect.top <= playerPos.y && playerPos.y <= _rect.bottom)
	{
		return true;
	}

	return false;
}