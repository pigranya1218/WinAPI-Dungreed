#include "stdafx.h"
#include "Player.h"
#include "TestScene.h"

void Player::move(Vector2 moveDir)
{
}

void Player::setAni(PLAYER_ANIMATION setAni)
{
	switch (setAni)
	{
	case IDLE:
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("PLAYER/IDLE");
		//_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
		_ani->start();
	}
	break;
	case MOVE:
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("PLAYER/RUN");
		//_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
		_ani->start();
	}
	break;
	default:
	{
		_ani->stop();
		_ani = nullptr;
	}
	break;
	}
}

void Player::init()
{
	setSize(Vector2(80, 110));
	setPosition(Vector2(200, WINSIZEY - 150));
	_direction == DIRECTION::RIGHT;
	_jumpCount = 2;
	_jumpPower = 6.f;
	_gravity = 5.f;
	_jumpSpeed = 0;
	_isJump = false;

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
	_ani->release();
	SAFE_DELETE(_ani);
}

void Player::update()
{
	//방향 조정
	if (_ptMouse.x < _position.x)
	{
		//좌측
	}
	else
	{
		//우측
	}

	//이동
	if (KEY_MANAGER->isStayKeyDown('A'))
	{
		if (!_isJump)
		{
			if(_setAni != PLAYER_ANIMATION::MOVE) setAni(PLAYER_ANIMATION::MOVE);
			_setAni = PLAYER_ANIMATION::MOVE;
			_position.x -= 200 * TIME_MANAGER->getElapsedTime();
		}
		else _position.x -= 150 * TIME_MANAGER->getElapsedTime();
	}
	if (KEY_MANAGER->isOnceKeyUp('A'))
	{
		if (_setAni != PLAYER_ANIMATION::IDLE)
		{
			setAni(PLAYER_ANIMATION::IDLE);
			_setAni = PLAYER_ANIMATION::IDLE;
		}
	}
	if (KEY_MANAGER->isStayKeyDown('D'))
	{
		if (!_isJump)
		{
			if (_setAni != PLAYER_ANIMATION::MOVE) setAni(PLAYER_ANIMATION::MOVE);
			_setAni = PLAYER_ANIMATION::MOVE;
			_position.x += 200 * TIME_MANAGER->getElapsedTime();
		}
		else _position.x += 150 * TIME_MANAGER->getElapsedTime();
	}
	if (KEY_MANAGER->isOnceKeyUp('D'))
	{
		if (_setAni != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
		_setAni = PLAYER_ANIMATION::IDLE;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_SPACE) && _jumpCount > 0)
	{
		_setAni = PLAYER_ANIMATION::DEFALT;
		_jumpCount -= 1;
		_isJump = true;
	}
	
	//점프 처리
	if (_isJump)
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("PLAYER/JUMP");
		_gravity -= 3.f;
		_position.y -= _jumpPower + _gravity * TIME_MANAGER->getElapsedTime() * 2;
		//착지
		if (_position.y + _size.y / 2 > _testScene->getGroundRect().top)
		{
			_position.y = _testScene->getGroundRect().top - _size.y / 2;
			if (_setAni != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
			_setAni = PLAYER_ANIMATION::IDLE;
			_jumpCount = 2;
			_gravity = 5.f;
			_isJump = false;
		}
	}

	//착지 처리
	//캐릭터 이미지의 height 값이 그라운드의 top보다 작으면
	if (!_isJump)
	{
		if (_position.y + _size.y / 2 < _testScene->getGroundRect().top)
		{
			_position.y += 20 * TIME_MANAGER->getElapsedTime();
		}
		else // 착지 하면
		{
			_position.y = _testScene->getGroundRect().top - _size.y / 2;
			_jumpCount = 2;
			/*if (_setAni != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
			_setAni = PLAYER_ANIMATION::IDLE;*/
		}
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
	
}

void Player::render()
{
	_img->setScale(5);
	//CAMERA_MANAGER->aniRender(_img, _position, _ani);
	//Camera::aniRender(_img, _position, _ani, false);
	//Image::aniRender();
	D2D_RENDERER->drawRectangle(FloatRect(_position, _size, PIVOT::CENTER));
}
