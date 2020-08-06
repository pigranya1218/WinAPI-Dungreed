#include "stdafx.h"
#include "Player.h"

void Player::move(Vector2 moveDir)
{
}

void Player::init()
{
	setPosition(Vector2(WINSIZEX / 2, WINSIZEY / 2));
	setSize(Vector2(80, 120));
}

void Player::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Player::update()
{
	switch (_state)
	{
	case IDLE:
	{
		_img = IMAGE_MANAGER->findImage("PLAYER/IDLE");
		_img->setScale(2);
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), 
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);

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
}

void Player::render()
{
}
