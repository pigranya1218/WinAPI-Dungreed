#include "Player.h"
#include "GameScene.h"
#include "Item.h"

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

void Player::attack(FloatRect* rect, tagAttackInfo* info)
{
	// 아이템 효과 적용
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->attack(rect, info);
		}
	}

	// 플레이어 스탯 적용
}

void Player::attack(FloatCircle* circle, tagAttackInfo* info)
{
	// 아이템 효과 적용
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->attack(circle, info);
		}
	}

	// 플레이어 스탯 적용
}

void Player::attack(Projectile* projectile, tagAttackInfo* info)
{
	// 아이템 효과 적용
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->attack(projectile, info);
		}
	}

	// 플레이어 스탯 적용
}

void Player::init()
{
	setSize(Vector2(80, 110));
	setPosition(Vector2(200, WINSIZEY - 250));
	_direction = DIRECTION::RIGHT;
	_jumpCount = 1;
	_xGravity = 2000.f;
	_yGravity = 1600.f;
	_isLanded = false;
	_force = Vector2(0, 0);

	_ani = new Animation;
	setAni(PLAYER_ANIMATION::IDLE);
}

void Player::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Player::update(float const elapsedTime)
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

	// 공격
	/*if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
	{
		_equippedWeapon[_currWeaponIndex]->attack(_position, atan2f(-(_ptMouse.y - _position.y), (_ptMouse.x - _position.x)));
		for (int i = 0; i < 4; i++)
		{
			if (_equippedAcc[i] != nullptr)
			{
				_equippedAcc[i]->attack(_position, atan2f(-(_ptMouse.y - _position.y), (_ptMouse.x - _position.x)));
			}
		}
	}*/

	//이동
	Vector2 moveDir(0, 0);
	//좌측 이동중
	if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_LEFT)))
	{
		moveDir.x -= 350 * elapsedTime;
		if (!_isLanded)
		{
			if (_aniState != PLAYER_ANIMATION::MOVE)
			{
				setAni(PLAYER_ANIMATION::MOVE);
				_aniState = PLAYER_ANIMATION::MOVE;
			}
			//_position.x -= 200 * TIME_MANAGER->getElapsedTime();
		}
		//else _position.x -= 150 * TIME_MANAGER->getElapsedTime();*/
	}
	//좌측 정지
	if (KEY_MANAGER->isOnceKeyUp(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_LEFT)))
	{
		if (_aniState != PLAYER_ANIMATION::IDLE)
		{
			setAni(PLAYER_ANIMATION::IDLE);
			_aniState = PLAYER_ANIMATION::IDLE;
		}
	}
	//우측 이동중
	if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_RIGHT)))
	{
		moveDir.x += 350 * elapsedTime;

		if (!_isLanded)
		{
			// if(moveDir.x == 0) 이때 IDLE
			if (_aniState != PLAYER_ANIMATION::MOVE)
			{
				setAni(PLAYER_ANIMATION::MOVE);
				_aniState = PLAYER_ANIMATION::MOVE;
			}
			//_position.x += 200 * TIME_MANAGER->getElapsedTime();
		}
		//else _position.x += 150 * TIME_MANAGER->getElapsedTime();
	}
	//우측 정지
	if (KEY_MANAGER->isOnceKeyUp(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_RIGHT)))
	{
		if (_aniState != PLAYER_ANIMATION::IDLE)
		{
			setAni(PLAYER_ANIMATION::IDLE);
			_aniState = PLAYER_ANIMATION::IDLE;
		}
	}
	/*if (KEY_MANAGER->isOnceKeyUp('A'))
	{
		if (_aniState != PLAYER_ANIMATION::IDLE)
		{
			setAni(PLAYER_ANIMATION::IDLE);
			_aniState = PLAYER_ANIMATION::IDLE;
		}
	}
	if (KEY_MANAGER->isOnceKeyUp('D'))
	{
		if (_aniState != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
		_aniState = PLAYER_ANIMATION::IDLE;
	}*/

	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::JUMP)) && _jumpCount > 0)
	{
		_force.y -= _jumpPower;
		_aniState = PLAYER_ANIMATION::DEFAULT;
		_jumpCount -= 1;
		_isLanded = true;
	}

	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::DASH)))
	{
		float angle = atan2f(-(_ptMouse.y - _position.y), (_ptMouse.x - _position.x));
		_force.x = cosf(angle) * _dashPower;
		_force.y = -sinf(angle) * _dashPower;
	}
	
	if (_force.x != 0) // 대쉬 상태라면
	{
		//점프 이미지로 교체 해야 함.


		if (_force.x > 0)
		{
			_force.x -= _xGravity * elapsedTime;
			if (_force.x < 0)
			{
				_force.x = 0;
			}
		}
		else
		{
			_force.x += _xGravity * elapsedTime;
			if (_force.x > 0)
			{
				_force.x = 0;
			}
		}
		moveDir.x = _force.x * elapsedTime;
	}
	//점프 하강
	_force.y += _yGravity * elapsedTime;
	moveDir.y = _force.y * elapsedTime;

	Vector2 lastPos = _position;
	_gameScene->moveTo(this, moveDir);
	//착지
	if (moveDir.y != 0 && lastPos.y == _position.y) // 땅에 착지
	{
		if(_aniState == PLAYER_ANIMATION::DEFAULT) setAni(PLAYER_ANIMATION::IDLE);
		_aniState = PLAYER_ANIMATION::IDLE;
		_isLanded = false;
		_force.y = 0;
		_jumpCount = 1;
	}

	//점프 처리
	if (_isLanded)
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("PLAYER/JUMP");
		_aniState = PLAYER_ANIMATION::DEFAULT;
		//_yGravity -= 3.f;
		//_position.y -= _jumpPower + _yGravity * TIME_MANAGER->getElapsedTime();
		/*if (_position.y + _size.y / 2 > _testScene->getGroundRect().top)
		{
			_position.y = _testScene->getGroundRect().top - _size.y / 2;
			if (_aniState != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
			_aniState = PLAYER_ANIMATION::IDLE;
			_jumpCount = 2;
			_yGravity = 5.f;
			_isLanded = false;
		}*/
	}

	//착지 처리
	//캐릭터 이미지의 height 값이 그라운드의 top보다 작으면
	//if (!_isLanded)
	//{
	//	//if (_position.y + _size.y / 2 < _testScene->getGroundRect().top)
	//	//{
	//	//	_position.y += 20 * TIME_MANAGER->getElapsedTime();
	//	//}
	//	//else // 착지 하면
	//	//{
	//	//	_position.y = _testScene->getGroundRect().top - _size.y / 2;
	//	//	_jumpCount = 2;
	//	//	/*if (_setAni != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
	//	//	_setAni = PLAYER_ANIMATION::IDLE;*/
	//	//}
	//}

	_ani->frameUpdate(elapsedTime);
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
	wstring str = L" isLanded[0 = 착지상태 / 1 = 체공상태] : " + to_wstring((int)_isLanded);
	D2D_RENDERER->renderText(0, 0, str, 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
	str = L" aniState[0 = DEFAULT / 1 = IDLE / 2 = MOVE] : " + to_wstring(int(_aniState));
	D2D_RENDERER->renderText(0, 20, str, 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
}
