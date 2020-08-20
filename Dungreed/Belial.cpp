#include "stdafx.h"
#include "EnemyManager.h"
#include "Belial.h"

void Belial::init(const Vector2 & pos)
{

	for (int i = 0; i < 10; i++)
	{
		tagLaser _laser;
		_vlaser.push_back(_laser);
	}

	_ani = new Animation;
	for (int i = 0; i < _vlaser.size(); i++)
	{
		_vlaser[i]._ani = new Animation;
	}
	setState(ENEMY_STATE::IDLE);

	_position = pos;
	_direction = DIRECTION::DOWN;
	_scale = 4;
	_size = _img->getFrameSize() * _scale;
	ZeroMemory(&_moving, sizeof(_moving));
	_moving.force = Vector2(0, 200);
	_moving.delay = 0.5;

	ZeroMemory(&_attacking, sizeof(_attacking));
	_attacking.delay = 3;


	ZeroMemory(&_shooting, sizeof(_shooting));
	_shooting.delay = 5;


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
		switch (_direction)
		{
		case DIRECTION::UP:
		{
			_position.y -= _moving.force.y * timeElapsed;
			if (_moving.update(timeElapsed))
			{
				_direction = DIRECTION::DOWN;
			}
		}
		break;

		case DIRECTION::DOWN:
		{
			_position.y += _moving.force.y * timeElapsed;
			if (_moving.update(timeElapsed))
			{
				_direction = DIRECTION::UP;
			}
		}
		break;

		}

		if (_attacking.update(timeElapsed))
		{
			_attacking.delay = 1;
			setState(ENEMY_STATE::ATTACK);
		}

	}
	break;

	case ENEMY_STATE::MOVE:
		break;

	case ENEMY_STATE::ATTACK:
	{
		//
		if (_ani->getPlayIndex() == 11 && _isAttack == false && _replayCount < 1)
		{
			_isAttack = true;
			_ani->stop();
			_ani->setPlayFrame(11, 15, false, false);
			_ani->start();

			for (int i = 0; i < _vlaser.size(); i++)
			{
				_vlaser[i]._ani->stop();
				_vlaser[i]._ani->setPlayFrame(1, 3, false, true);
				_vlaser[i]._ani->start();
			}

		}
		if (_isAttack == true)
		{
			if (!_ani->isPlay())
			{
				_ani->stop();
				_ani->start();
			}

			if (_attacking.update(timeElapsed))
			{
				_replayCount++;
				_ani->stop();
				_ani->setPlayFrame(15, 18, false, false);
				_ani->start();
				for (int i = 0; i < _vlaser.size(); i++)
				{
					_vlaser[i]._ani->stop();
				}

				_isAttack = false;
			}
		}
		if (_isAttack == false && _replayCount >= 1)
		{
			if (!_ani->isPlay())
			{
				if (_attacking.update(timeElapsed))
				{
					_replayCount = 0;
					setState(ENEMY_STATE::IDLE);
				}
			}
		}

		for (int i = 0; i < _vlaser.size(); i++)
		{
			if (i == 0)
			{
				_vlaser[i]._laserPosition = _position;
				//왼손일경우
				//_vlaser[i]._laserPosition.x =_position.x + (i + 1 * (_vlaser[i]._img->getFrameSize().x * _scale));
				//오른손일경우
				//_vlaser[i]._laserPosition.x = _position.x - (i + 1 * (_vlaser[i]._img->getFrameSize().x * _scale));


			}
			if (i > 0)
			{
				_vlaser[i]._laserPosition = _position;
				//왼손일경우
				//_vlaser[i]._laserPosition.x = _vlaser[i - 1]._laserPosition.x + ((_vlaser[i - 1]._img->getFrameSize().x * _scale));

				//오른손일경우
				//_vlaser[i]._laserPosition.x = _vlaser[i - 1]._laserPosition.x - ((_vlaser[i - 1]._img->getFrameSize().x * _scale));

			}
		}

	}
		break;
	case ENEMY_STATE::SKILL:
		break;
	case ENEMY_STATE::DIE:
		break;
	}

	_ani->frameUpdate(timeElapsed);
	for (int i = 0; i < _vlaser.size(); i++)
	{
		_vlaser[i]._ani->frameUpdate(timeElapsed);
	}
}

void Belial::render()
{

	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani);

	for (int i = 0; i < _vlaser.size(); i++)
	{
		if (_state == ENEMY_STATE::ATTACK && _vlaser[i]._ani->isPlay())
		{
			_vlaser[i]._img->setScale(_scale);
			_vlaser[i]._img->aniRender(CAMERA->getRelativeV2(_vlaser[i]._laserPosition), _vlaser[i]._ani);
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

		_imageName = "Belial/Hand/Idle";
		_ani->stop();
		_img = IMAGE_MANAGER->findImage(_imageName);
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());;
		_ani->setDefPlayFrame(false, true);
		_ani->setFPS(15);
		_ani->start();

	}
	break;
	case ENEMY_STATE::ATTACK:
	{

		_imageName = "Belial/Hand/Attack";
		_ani->stop();
		_img = IMAGE_MANAGER->findImage(_imageName);
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, false);
		_ani->setFPS(15);
		_ani->start();

		for (int i = 0; i < _vlaser.size(); i++)
		{
			if (i == 0)
			{
				_vlaser[i]._ani->stop();
				_vlaser[i]._imageName = "Belial/Laser/Head";
				_vlaser[i]._img = IMAGE_MANAGER->findImage(_vlaser[i]._imageName);
				_vlaser[i]._ani->init(_vlaser[i]._img->getWidth(), _vlaser[i]._img->getHeight(), _vlaser[i]._img->getMaxFrameX(), _vlaser[i]._img->getMaxFrameY());
				_vlaser[i]._ani->setDefPlayFrame(false, false);
				_vlaser[i]._ani->setFPS(15);
			}
			else if (i > 0)
			{
				_vlaser[i]._ani->stop();
				_vlaser[i]._imageName = "Belial/Laser";
				_vlaser[i]._img = IMAGE_MANAGER->findImage(_vlaser[i]._imageName);
				_vlaser[i]._ani->init(_vlaser[i]._img->getWidth(), _vlaser[i]._img->getHeight(), _vlaser[i]._img->getMaxFrameX(), _vlaser[i]._img->getMaxFrameY());
				_vlaser[i]._ani->setDefPlayFrame(false, false);
				_vlaser[i]._ani->setFPS(15);
			}
		}

	}
	break;
	case ENEMY_STATE::DIE:
	{

	}
	break;
	}
}