#include "stdafx.h"
#include "Player.h"
#include "TestScene.h"

void Player::move(Vector2 moveDir)
{
}

void Player::init()
{
	setPosition(Vector2(WINSIZEX / 2, WINSIZEY / 2));
	setSize(Vector2(80, 120));

	_direction == DIRECTION::RIGHT;
	_state = IDLE;

	_img = IMAGE_MANAGER->findImage("PLAYER/IDLE");
	//_img->setScale(2);
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(10);
	_ani->setPlayFrame(0, 5, false, true);
	_ani->start();

}

void Player::release()
{
	/*_ani->release();
	SAFE_DELETE(_ani);*/
}

void Player::update()
{


	//스테이트에 따른 애니메이션 재생
	switch (_state)
	{
	case IDLE:
	{
		if (!_ani->isPlay())
		{
			_img = IMAGE_MANAGER->findImage("PLAYER/IDLE");
			//_img->setScale(2);
			_ani = new Animation;
			_ani->init(_img->getWidth(), _img->getHeight(),
				_img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setFPS(10);
			if (_direction == DIRECTION::RIGHT)
			{
				_ani->setPlayFrame(0, 5, false, true);
			}
			else if (_direction == DIRECTION::LEFT)
			{
				//좌우반전

			}
			_ani->start();
		}
	}
	break;
	case MOVE:
	{
		//_img = IMAGE_MANAGER->findImage("")
	}
	break;
	case JUMP:
	{

	}
	break;
	case DIE:
	{

	}
	break;
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void Player::render()
{
	_img->setScale(3);
	CAMERA_MANAGER->aniRender(_img, Vector2(WINSIZEX/2, WINSIZEY/2), _ani);
}
