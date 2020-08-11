#include "Player.h"
#include "GameScene.h"
#include "Item.h"
#include "ShortSpear.h"
#include "Punch.h"
#include "SpikeBall.h"
#include "babyGreenBat.h"
#include "bombPouch.h"
#include "MatchLockGun.h"
#include "Matchlock.h"
#include "ShortSword.h"

void Player::setBaseStat()
{
	_baseStat.maxHp = 80;
	_baseStat.maxJumpCount = 1;
	_baseStat.maxDashCount = 2;
	_baseStat.dashCoolTime = 1.5f;
	_baseStat.maxSatiety = 100;
	_baseStat.power = 5;
	_baseStat.damage = 0; //0 ~ 4
	_baseStat.trueDamage = 0;
	_baseStat.criticalChance = 2;
	_baseStat.criticalDamage = 1; // + 100%
	_baseStat.toughness = 0;
	_baseStat.defense = 0;
	_baseStat.block = 0;
	_baseStat.evasion = 0;
	_baseStat.attackSpeed = 0;
	_baseStat.reloadSpeed = 0; // --
	_baseStat.moveSpeed = 350;
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
	_level = 1;
	_currJumpCount = _adjustStat.maxJumpCount;
	_currDashCount = _adjustStat.maxDashCount;
	_currDashCoolTime = 0;
	//_currHp = _adjustStat.maxHp;
	_currHp = 40;
	_currSatiety = 0;
	_currGold = 1000;
	_force = Vector2(0, 0);

	_ani = new Animation;
	setAni(PLAYER_ANIMATION::IDLE);

	//test 
	/*ShortSpear* testWeapon = new ShortSpear;
	testWeapon->init();
	_equippedWeapon.push_back(testWeapon);
	_currWeaponIndex = 0;*/

	/*MatchLockGun* testWeapon = new MatchLockGun;
	testWeapon->init();
	_equippedWeapon.push_back(testWeapon);
	_currWeaponIndex = 0;*/
	
	/*SpikeBall* testAcc = new SpikeBall;
	testAcc->init();
	_equippedAcc.push_back(testAcc);
	
	babyGreenBat* testAcc1 = new babyGreenBat;
	testAcc1->init();
	_equippedAcc.push_back(testAcc1);

	bombPouch* testAcc2 = new bombPouch;
	testAcc2->init();
	_equippedAcc.push_back(testAcc2);*/

	//ShortSpear* testWeapon = new ShortSpear;
	ShortSpear* testWeapon1 = new ShortSpear;
	testWeapon1->init();
	_equippedWeapon.push_back(testWeapon1);
	
	Punch* testWeapon2 = new Punch;
	testWeapon2->init();
	_equippedWeapon.push_back(testWeapon2);

	_currWeaponIndex = 1;
	_currWeaponChangeCoolTime = 0;
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

	// 장비 교체
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::CHANGE_WEAPON)) && _currWeaponChangeCoolTime == 0)
	{
		_currWeaponIndex == 0 ? _currWeaponIndex = 1 : _currWeaponIndex = 0;
		_currWeaponChangeCoolTime = 1;
	}

	// 장비 교체 시간 딜레이
	if (_currWeaponChangeCoolTime > 0)
	{
		_currWeaponChangeCoolTime -= elapsedTime;
		if (_currWeaponChangeCoolTime < 0) _currWeaponChangeCoolTime = 0;
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
	//좌측 이동중
	if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_LEFT)))
	{
		moveDir.x -= _baseStat.moveSpeed * elapsedTime;
		if (_isStand)
		{
			if (moveDir.x == 0)
			{
				if(_aniState != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
				_aniState = PLAYER_ANIMATION::IDLE;
			}
			else if (moveDir.x != 0)
			{
				if(_aniState != PLAYER_ANIMATION::MOVE) setAni(PLAYER_ANIMATION::MOVE);
				_aniState = PLAYER_ANIMATION::MOVE;
			}
		}
	}
	//우측 이동중
	if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_RIGHT)))
	{
		moveDir.x += _baseStat.moveSpeed * elapsedTime;

		if (_isStand)
		{
			// if(moveDir.x == 0) 이때 IDLE
			if (moveDir.x == 0)
			{
				if(_aniState != PLAYER_ANIMATION::IDLE) setAni(PLAYER_ANIMATION::IDLE);
				_aniState = PLAYER_ANIMATION::IDLE;
			}
			else if(moveDir.x != 0)
			{
				if(_aniState != PLAYER_ANIMATION::MOVE) setAni(PLAYER_ANIMATION::MOVE);
				_aniState = PLAYER_ANIMATION::MOVE;
			}
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

	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::JUMP)) && _currJumpCount > 0)
	{
		_force.y = -_adjustStat.jumpPower;
		// _aniState = PLAYER_ANIMATION::DEFAULT;
		_currJumpCount -= 1;
	}
	//대쉬
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::DASH)) && _currDashCount > 0)
	{
		_currDashCount -= 1;
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

	//대쉬 쿨타임
	if (_currDashCount < _adjustStat.maxDashCount)
	{
		_currDashCoolTime += elapsedTime;
		if (_currDashCoolTime > _adjustStat.dashCoolTime)
		{
			_currDashCount += 1;
			_currDashCoolTime = 0;
		}
	}

	//하강중
	_force.y += _adjustStat.yGravity * elapsedTime;
	moveDir.y = 1.5 + _force.y * elapsedTime;

	_gameScene->moveTo(this, moveDir);
	//착지
	if (_isStand)
	{
		_force.y = 200;
		_currJumpCount = _adjustStat.maxJumpCount;
		if (moveDir.x == 0 && _aniState != PLAYER_ANIMATION::IDLE)
		{
			setAni(PLAYER_ANIMATION::IDLE);
			_aniState = PLAYER_ANIMATION::IDLE;
		}
	}

	//점프 처리
	if (!_isStand)
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("PLAYER/JUMP");
		_aniState = PLAYER_ANIMATION::DEFAULT;
	}

	_ani->frameUpdate(elapsedTime);

	// 무기 업데이트
	_equippedWeapon[0]->update(this, elapsedTime);
	_equippedWeapon[1]->update(this, elapsedTime);
	// 악세사리 업데이트
	/*_equippedAcc[1]->update(this, elapsedTime);
	_equippedAcc[0]->update(this, elapsedTime);
	_equippedAcc[2]->update(this, elapsedTime);*/
	
}

void Player::render()
{
	_img->setScale(4);

	/*_equippedAcc[0]->backRender(_position, angle);
	_equippedAcc[1]->backRender(_position, angle);
	_equippedAcc[2]->backRender(_position, angle);*/
	_equippedWeapon[_currWeaponIndex]->backRender(this);

	if (_aniState == PLAYER_ANIMATION::DEFAULT)
	{
		_img->render(_position, _direction == DIRECTION::LEFT);
	}
	else
	{
		_img->aniRender(_position, _ani, _direction == DIRECTION::LEFT);
	}

	/*_equippedAcc[0]->frontRender(_position, angle);
	_equippedAcc[1]->frontRender(_position, angle);
	_equippedAcc[2]->frontRender(_position, angle);*/
	_equippedWeapon[_currWeaponIndex]->frontRender(this);
	
	wstring str = L" 대쉬 카운트 : " + to_wstring(_currDashCount) + L" | 대쉬 쿨타임 : " + to_wstring(_currDashCoolTime) + L" / " + to_wstring(_adjustStat.dashCoolTime);
	D2D_RENDERER->renderText(0, 0, str, 20, D2DRenderer::DefaultBrush::Blue, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
	str = L" 무기 교체 딜레이 시간 : " + to_wstring(_currWeaponChangeCoolTime);
	D2D_RENDERER->renderText(600, 0, str, 20, D2DRenderer::DefaultBrush::Green, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
}
