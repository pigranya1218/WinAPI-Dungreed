#include "stdafx.h"
#include "Player.h"
#include "TestScene.h"

void Player::move(Vector2 moveDir)
{
}

void Player::setAni(PLAYER_ANIMATION setAni)
{
	_aniState = setAni;
	switch (setAni)
	{
	case PLAYER_ANIMATION::IDLE:
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("PLAYER/IDLE");
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
		_ani->start();
	}
	break;
	case PLAYER_ANIMATION::MOVE:
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("PLAYER/RUN");
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
	_direction = DIRECTION::RIGHT;
	_jumpCount = 2;
	_xGravity = 5.f;
	_yGravity = 5.f;
	_isJump = false;

	_ani = new Animation;
	setAni(PLAYER_ANIMATION::IDLE);
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
		_direction = DIRECTION::LEFT;
	}
	else
	{
		_direction = DIRECTION::RIGHT;
	}

	//이동
	if (KEY_MANAGER->isStayKeyDown('A'))
	{
		if (!_isJump)
		{
			if(_aniState != PLAYER_ANIMATION::MOVE) setAni(PLAYER_ANIMATION::MOVE);
			_aniState = PLAYER_ANIMATION::MOVE;
			_position.x -= 200 * TIME_MANAGER->getElapsedTime();
		}
		else _position.x -= 150 * TIME_MANAGER->getElapsedTime();
	}
	if (KEY_MANAGER->isOnceKeyUp('A'))
	{
		if (_aniState != PLAYER_ANIMATION::IDLE)
		{
			setAni(PLAYER_ANIMATION::IDLE);
			_aniState = PLAYER_ANIMATION::IDLE;
		}
	}
	if (KEY_MANAGER->isStayKeyDown('D'))
	{
		if (!_isJump)
		{
			if (_aniState != PLAYER_ANIMATION::MOVE) setAni(PLAYER_ANIMATION::MOVE);
			_aniState = PLAYER_ANIMATION::MOVE;
			_position.x += 200 * TIME_MANAGER->getElapsedTime();
		}
		else _position.x += 150 * TIME_MANAGER->getElapsedTime();
	}
	if (KEY_MANAGER->isOnceKeyUp('D'))
	{
		if (_aniState != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
		_aniState = PLAYER_ANIMATION::IDLE;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_SPACE) && _jumpCount > 0)
	{
		_aniState = PLAYER_ANIMATION::DEFAULT;
		_jumpCount -= 1;
		_isJump = true;
	}
	
	////점프 처리
	if (_isJump)
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("PLAYER/JUMP");
		_yGravity -= 3.f;
		_position.y -= _jumpPower + _yGravity * TIME_MANAGER->getElapsedTime() * 2;
		if (_position.y + _size.y / 2 > _testScene->getGroundRect().top)
		{
			_position.y = _testScene->getGroundRect().top - _size.y / 2;
			if (_aniState != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
			_aniState = PLAYER_ANIMATION::IDLE;
			_jumpCount = 2;
			_yGravity = 5.f;
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
	if (_aniState == PLAYER_ANIMATION::DEFAULT)
	{
		_img->render(_position, _direction == DIRECTION::LEFT);
	}
	else
	{
		_img->aniRender(_position, _ani, _direction == DIRECTION::LEFT);
	}
	D2D_RENDERER->drawRectangle(FloatRect(_position, _size, PIVOT::CENTER));
}
