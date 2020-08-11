#include "Player.h"
#include "GameScene.h"
#include "Item.h"
#include "ShortSpear.h"
#include "MatchLockGun.h"
#include "Matchlock.h"

void Player::setBaseStat()
{
	_baseStat.maxHp = 75;
	_baseStat.maxJumpCount = 1;
	_baseStat.maxDashCount = 2;
	_baseStat.maxSatiety = 100;
	_baseStat.dashXPower = 2400;
	_baseStat.dashYPower = 1700;
	_baseStat.jumpPower = 1700;
	_baseStat.xGravity = 10000;
	_baseStat.yGravity = 5000;
}

// 장착 아이템 및 스킬에 따른 스탯 변화주기
void Player::updateAdjustStat()
{
	_adjustStat = _baseStat;
	

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
	setSize(Vector2(40, 90));
	setPosition(Vector2(200, WINSIZEY - 250));
	_direction = DIRECTION::RIGHT;
	

	setBaseStat();
	updateAdjustStat();
	_currJumpCount = _adjustStat.maxJumpCount;
	_currHp = _adjustStat.maxHp;
	_currSatiety = 0;

	_force = Vector2(0, 0);

	_ani = new Animation;
	setAni(PLAYER_ANIMATION::IDLE);

	//test 
	/*ShortSpear* testWeapon = new ShortSpear;
	testWeapon->init();
	_equippedWeapon.push_back(testWeapon);
	_currWeaponIndex = 0;*/

	MatchLockGun* testWeapon = new MatchLockGun;
	testWeapon->init();
	_equippedWeapon.push_back(testWeapon);
	_currWeaponIndex = 0;
}

void Player::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Player::update(float const elapsedTime)
{
	// 아이템, 스킬에 따른 스탯 조정 (변경이 생길 때)
	// updateAdjustStat();

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
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
	{
		_equippedWeapon[_currWeaponIndex]->attack(_position, atan2f(-(_ptMouse.y - _position.y), (_ptMouse.x - _position.x)));
		/*for (int i = 0; i < 4; i++)
		{
			if (_equippedAcc[i] != nullptr)
			{
				_equippedAcc[i]->attack(_position, atan2f(-(_ptMouse.y - _position.y), (_ptMouse.x - _position.x)));
			}
		}*/
	}

	//이동
	Vector2 moveDir(0, 0);
	if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_LEFT)))
	{
		moveDir.x -= 350 * elapsedTime;
		/*if (!_isLanded)
		{
			if(_aniState != PLAYER_ANIMATION::MOVE) setAni(PLAYER_ANIMATION::MOVE);
			_aniState = PLAYER_ANIMATION::MOVE;
			_position.x -= 200 * TIME_MANAGER->getElapsedTime();
		}
		else _position.x -= 150 * TIME_MANAGER->getElapsedTime();*/
	}
	if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_RIGHT)))
	{
		moveDir.x += 350 * elapsedTime;

		/*if (!_isLanded)
		{
			if (_aniState != PLAYER_ANIMATION::MOVE) setAni(PLAYER_ANIMATION::MOVE);
			_aniState = PLAYER_ANIMATION::MOVE;
			_position.x += 200 * TIME_MANAGER->getElapsedTime();
		}
		else _position.x += 150 * TIME_MANAGER->getElapsedTime();*/
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

	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::JUMP)) && _currJumpCount > 0)
	{
		_force.y = -_adjustStat.jumpPower;
		// _aniState = PLAYER_ANIMATION::DEFAULT;
		_currJumpCount -= 1;
	}

	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::DASH)))
	{
		float angle = atan2f(-(_ptMouse.y - _position.y), (_ptMouse.x - _position.x));
		_force.x = cosf(angle) * _adjustStat.dashXPower;
		_force.y = -sinf(angle) * _adjustStat.dashYPower;
	}
	
	if (_force.x != 0) // 대쉬 상태라면
	{
		if (_force.x > 0)
		{
			_force.x -= _adjustStat.xGravity * elapsedTime;
			if (_force.x < 0)
			{
				_force.x = 0;
			}
		}
		else
		{
			_force.x += _adjustStat.xGravity * elapsedTime;
			if (_force.x > 0)
			{
				_force.x = 0;
			}
		}
		moveDir.x = _force.x * elapsedTime;
	}
	_force.y += _adjustStat.yGravity * elapsedTime;
	moveDir.y = _force.y * elapsedTime;

	_gameScene->moveTo(this, moveDir);
	if (_isStand) // 땅에 착지
	{
		_force.y = 200;
		_currJumpCount = _adjustStat.maxJumpCount;
	}

	////점프 처리
	//if (_isLanded)
	//{
	//	_ani->stop();
	//	_img = IMAGE_MANAGER->findImage("PLAYER/JUMP");
	//	_yGravity -= 3.f;
	//	_position.y -= _jumpPower + _yGravity * TIME_MANAGER->getElapsedTime() * 2;
	//	/*if (_position.y + _size.y / 2 > _testScene->getGroundRect().top)
	//	{
	//		_position.y = _testScene->getGroundRect().top - _size.y / 2;
	//		if (_aniState != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
	//		_aniState = PLAYER_ANIMATION::IDLE;
	//		_jumpCount = 2;
	//		_yGravity = 5.f;
	//		_isLanded = false;
	//	}*/
	//}

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

	// 무기 업데이트
	_equippedWeapon[_currWeaponIndex]->update(elapsedTime);
}

void Player::render()
{
	_img->setScale(4);
	//_weapon = IMAGE_MANAGER->findImage("ShortSpear");
	//_weapon->setScale(4);
	//float angle =  (TTYONE_UTIL::getAngle(_position.x, _position.y, _ptMouse.x, _ptMouse.y)) * (180 / PI);
	float angle =  fmod(atan2f(-(_ptMouse.y - (_position.y + 15)), (_ptMouse.x - _position.x)) * (180 / PI) + 360, 360);
	

	//_weapon->setAngle(angle);

	if (_aniState == PLAYER_ANIMATION::DEFAULT)
	{
		
		//D2D_RENDERER->fillRectangle(_rightHand, 251, 206, 177, 1);
		_img->render(_position, _direction == DIRECTION::LEFT);
		
	}
	else
	{
		_img->aniRender(_position, _ani, _direction == DIRECTION::LEFT);
		//D2D_RENDERER->fillRectangle(_leftHand, 251, 206, 177, 1);
	}
	
	
	D2D_RENDERER->drawRectangle(FloatRect(_position, _size, PIVOT::CENTER));
	
	// 무기 렌더
	_equippedWeapon[_currWeaponIndex]->render(_position, angle);
}
