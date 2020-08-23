#include "Player.h"
#include "GameScene.h"
#include "Costume.h"
#include "Item.h"
#include "Food.h"

#include "ShortSpear.h"
#include "Punch.h"
#include "ShortSword.h"
#include "CosmosSword.h"
#include "KeresScythe.h"
#include "MartialArtOfTiger.h"
#include "PickaxeRed.h"
#include "PowerKatana.h"
#include "QuarterStaffBig.h"
#include "BigPaintBlush.h"
#include "Lumber.h"
#include "FluteGreatSword.h"

#include "OakBow.h"
#include "MatchLockGun.h"
#include "Boomerang.h"
#include "GatlingGun.h"
#include "MagicStick.h"

#include "SpikeBall.h"
#include "IceBall.h"
#include "miniEarth.h"
#include "watCher.h"
#include "babyGreenBat.h"
#include "GreenBat.h"
#include "GreenDadBat.h"
#include "GreenMomBat.h"
#include "bombPouch.h"
#include "Matchlock.h"
#include "MagnifyingGlass.h"
#include "Voluspa.h"
#include "HeartOfCosmos.h"
#include "DemonBoots.h"
#include "MultiBullet.h"
#include "DaisyRing.h"
#include "Wingboots.h"
#include "SilverBullet.h"
#include "Seeri.h"


// 장착 아이템 및 스킬에 따른 스탯 변화주기
void Player::updateAdjustStat()
{
	_adjustStat = _costume->getBaseStat();

	if (_equippedWeapon[_currWeaponIndex] != nullptr)
	{
		_adjustStat = _adjustStat + _equippedWeapon[_currWeaponIndex]->getAddStat();
	}
	else
	{
		_adjustStat = _adjustStat + _hand->getAddStat();
	}

	for (int i = 0; i < 4; i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_adjustStat = _adjustStat + _equippedAcc[i]->getAddStat();
		}
	}

	for (int i = 0; i < _specialAbility.size(); i++)
	{
		_adjustStat = _adjustStat + _specialAbility[i]->getAddStat();
	}

	for (int i = 0; i < _ateFood.size(); i++)
	{
		_adjustStat = _adjustStat + _ateFood[i]->getAddStat();
	}

	_adjustStat = _adjustStat + _abilityStat;

	if (_equippedWeapon[_currWeaponIndex] != nullptr)
	{
		_equippedWeapon[_currWeaponIndex]->equip(this);
	}
	else
	{
		_hand->equip(this);
	}


}

void Player::sellItem(int index)
{
	if (_inventory[index] != nullptr)
	{
		_currGold += _inventory[index]->getPrice() * 0.7;
		_inventory[index]->release();
		delete _inventory[index];
		_inventory[index] = nullptr;
	}
}

bool Player::buyItem(Item* item)
{
	if (_currGold >= item->getPrice())
	{
		for (int i = 0; i < _inventory.size(); i++)
		{
			if (_inventory[i] == nullptr)
			{
				_currGold -= item->getPrice();
				_inventory[i] = item;
				return true;
			}
		}
	}
	return false;
}

void Player::swap(Item *& a, Item *& b)
{
	Item* temp = a;
	a = b;
	b = temp;
	updateAdjustStat();
}

bool Player::attack(FloatRect* rect, AttackInfo* info)
{
	// 아이템 효과 적용
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->attack(this, rect, info);
		}
	}

	// 플레이어 스탯 적용 (위력, 크리티컬)
	info->minDamage *= ((100 + _adjustStat.power) / 100);
	info->maxDamage *= ((100 + _adjustStat.power) / 100);
	info->critical += _adjustStat.criticalChance;
	info->criticalDamage += _adjustStat.criticalDamage;
	info->trueDamage += _adjustStat.trueDamage;

	return _gameScene->attack(rect, info);
}

bool Player::attack(FloatCircle* circle, AttackInfo* info)
{
	// 아이템 효과 적용
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->attack(this, circle, info);
		}
	}

	// TODO : 플레이어 스탯 적용 (위력, 크리티컬)
	info->minDamage *= ((100 + _adjustStat.power) / 100);
	info->maxDamage *= ((100 + _adjustStat.power) / 100);
	info->critical += _adjustStat.criticalChance;
	info->criticalDamage += _adjustStat.criticalDamage;
	info->trueDamage += _adjustStat.trueDamage;

	return _gameScene->attack(circle, info);
}

void Player::attack(Projectile* projectile, AttackInfo* info)
{
	// 아이템 효과 적용
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->attack(this, projectile, info);
		}
	}

	// 플레이어 스탯 적용 (위력, 크리티컬)
	info->minDamage *= ((100 + _adjustStat.power) / 100);
	info->maxDamage *= ((100 + _adjustStat.power) / 100);
	info->critical += _adjustStat.criticalChance;
	info->criticalDamage += _adjustStat.criticalDamage;
	info->trueDamage += _adjustStat.trueDamage;

	_gameScene->attack(projectile, info);
}

void Player::init()
{
	setSize(Vector2(40, 80));
	setPosition(Vector2(200, 200));
	_direction = DIRECTION::RIGHT;
	
	_equippedWeapon.resize(2);
	_equippedAcc.resize(4);
	_inventory.resize(15);

	_hand = new Punch;
	_hand->init();

	//최초에 장착하는 코스튬
	setCurrCostume(DATA_MANAGER->getCostume(COSTUME_TYPE::ALICE));

	_level = 30;
	_currJumpCount = _adjustStat.maxJumpCount;
	_currDashCount = _adjustStat.maxDashCount;
	_currDashCoolTime = 0;
	//_currHp = _adjustStat.maxHp;
	_currHp = _adjustStat.maxHp;
	_currSatiety = 0;
	_currGold = 5000;
	_currHitTime = 0;
	_force = Vector2(0, 0);

	


	ShortSpear* testAcc1 = new ShortSpear;
	testAcc1->init();
	_inventory[4] = testAcc1;

	//Seeri* testAcc24 = new Seeri;
	//testAcc24->init();
	//_inventory[1] = testAcc24;

	//GreenBat* testAcc2 = new GreenBat;
	//testAcc2->init();
	//_inventory[5] = testAcc2;
	

	//GreenDadBat* testAcc3 = new GreenDadBat;
	//testAcc3->init();
	//_inventory[3] = testAcc3;

	
	ShortSword* testAcc4 = new ShortSword;
	testAcc4->init();
	_inventory[3] = testAcc4;


	MartialArtOfTiger* testAcc9 = new MartialArtOfTiger;
	testAcc9->init();
	_inventory[8] = testAcc9;


	//PowerKatana* testAcc5 = new PowerKatana;
	//testAcc5->init();
	//_inventory[6] = testAcc5;


	//IceBall* testAcc6 = new IceBall;
	//testAcc6->init();
	//_inventory[3] = testAcc6;
	//
	//
	//miniEarth* testAcc7 = new miniEarth;
	//testAcc7->init();
	//_inventory[7] = testAcc7;
	//
	//
	QuarterStaffBig* testAcc8 = new QuarterStaffBig;
	testAcc8->init();
	_inventory[8] = testAcc8;
	
	
	BigPaintBlush* testAcc10 = new BigPaintBlush;
	testAcc10->init();
	_inventory[9] = testAcc10;

	Lumber* testAcc11 = new Lumber;
	testAcc11->init();
	_inventory[10] = testAcc11;

	//HeartOfCosmos* testAcc12 = new HeartOfCosmos;
	//testAcc12->init();
	//_inventory[0] = testAcc12;

	//Seeri* testAcc21 = new Seeri;
	//testAcc21->init();
	//_inventory[5] = testAcc21;

	//DemonBoots* testAcc13 = new DemonBoots;
	//testAcc13->init();
	//_inventory[5] = testAcc13;

	Voluspa* testAcc22 = new Voluspa;
	testAcc22->init();
	_inventory[1] = testAcc22;

	MultiBullet* testAcc14 = new MultiBullet;
	testAcc14->init();
	_inventory[10] = testAcc14;

	//MartialArtOfTiger* testAcc16 = new MartialArtOfTiger;
	//testAcc16->init();
	//_inventory[1] = testAcc16;

	//Wingboots* testAcc17 = new Wingboots;
	//testAcc17->init();
	//_inventory[2] = testAcc17;

	FluteGreatSword* testAcc20 = new FluteGreatSword;
	testAcc20->init();
	_inventory[2] = testAcc20;
	

	//BigPaintBlush* testAcc15 = new BigPaintBlush;
	//testAcc15->init();
	//_inventory[7] = testAcc15;

	//DaisyRing* testAcc23 = new DaisyRing;
	//testAcc23->init();
	//_inventory[7] = testAcc23;
	

	/*KeresScythe* testWeapon1 = new KeresScythe;
	testWeapon1->init();
	_inventory[11] = testWeapon1;
	*/

	Lumber* testWeapon2 = new Lumber;
	testWeapon2->init();
	_inventory[11] = testWeapon2;

	//CosmosSword* testWeapon3 = new CosmosSword;
	//testWeapon3->init();
	//_inventory[12] = testWeapon3;
	//
	/*PickaxeRed* testWeapon4 = new PickaxeRed;
	testWeapon4->init();
	_inventory[13] = testWeapon4;*/

	/*BigPaintBlush* testWeapon5 = new BigPaintBlush;
	testWeapon5->init();
	_inventory[14] = testWeapon5;*/

	/*FluteGreatSword* testWeapon5 = new FluteGreatSword;
	testWeapon5->init();
	_inventory[14] = testWeapon5;*/

	CosmosSword* testWeapon5 = new CosmosSword;
	testWeapon5->init();
	_inventory[13] = testWeapon5;

	Boomerang* testweapon6 = new Boomerang;
	testweapon6->init();
	_inventory[12] = testweapon6;

	/*MatchLockGun* testWeapon6 = new MatchLockGun;
	testWeapon6->init();
	_inventory[14] = testWeapon6;*/

	GatlingGun* testWeapon7 = new GatlingGun;
	testWeapon7->init();
	_inventory[3] = testWeapon7;

	MagicStick* testWeapon8 = new MagicStick;
	testWeapon8->init();
	_inventory[14] = testWeapon8;

	//OakBow* testWeapon8 = new OakBow;
	//testWeapon8->init();
	//_inventory[14] = testWeapon8;

	/*SilverBullet* testAcc19 = new SilverBullet;
	testAcc19->init();
	_inventory[14] = testAcc19;*/

	MagnifyingGlass* testAcc18 = new MagnifyingGlass;
	testAcc18->init();
	_inventory[5] = testAcc18;

	

	

	_currWeaponIndex = 0;
	_currWeaponChangeCoolTime = 0;

	updateAdjustStat();
}

void Player::release()
{
	for (int i = 0; i < _inventory.size(); i++)
	{
		if (_inventory[i] == nullptr) continue;
		_inventory[i]->release();
		delete _inventory[i];
	}
	for (int i = 0; i < _equippedWeapon.size(); i++)
	{
		if (_equippedWeapon[i] == nullptr) continue;
		_equippedWeapon[i]->release();
		delete _equippedWeapon[i];
	}
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] == nullptr) continue;
		_equippedAcc[i]->release();
		delete _equippedAcc[i];
	}
	_inventory.clear();
	_equippedWeapon.clear();
	_equippedAcc.clear();
}

void Player::update(float const elapsedTime)
{
	// 아이템, 스킬에 따른 스탯 조정 (변경이 생길 때)
	// updateAdjustStat();

	//방향 조정
	if (CAMERA->getAbsoluteX(_ptMouse.x) < _position.x)
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
		_currWeaponIndex = !_currWeaponIndex;
		_currWeaponChangeCoolTime = 1;
		updateAdjustStat();
	}

	// 장비 교체 시간 딜레이
	if (_currWeaponChangeCoolTime > 0)
	{
		_currWeaponChangeCoolTime -= elapsedTime;
		if (_currWeaponChangeCoolTime < 0) _currWeaponChangeCoolTime = 0;
	}

	// 공격
	if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)) && !_gameScene->isUIActive())
	{
		if (_equippedWeapon[_currWeaponIndex] == nullptr)
		{
			_hand->attack(this);
		}
		else
		{
			_equippedWeapon[_currWeaponIndex]->attack(this);
		}
		for (int i = 0; i < _equippedAcc.size(); i++)
		{
			if (_equippedAcc[i] != nullptr)
			{
				_equippedAcc[i]->attack(this);
			}
		}
	}

	//이동
	Vector2 moveDir(0, 0);
	
	if (!_gameScene->isUIActive() && 
		(KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_LEFT)) || KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_RIGHT)))) // 좌우 이동중
	{
		if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_LEFT)))
		{
			moveDir.x -= _adjustStat.moveSpeed * elapsedTime;
		}
		if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_RIGHT)))
		{
			moveDir.x += _adjustStat.moveSpeed * elapsedTime;
		}
		_costume->setSprite(PLAYER_STATE::MOVE, false);
	}
	else // 이동 안하는 중 
	{
		_costume->setSprite(PLAYER_STATE::IDLE, false);
	}

	// 점프
	if (!_gameScene->isUIActive() && KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::JUMP)))
	{
		if (_isStand && KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_DOWN)))
		{
			_position.y += 1.5;
			_force.y = 0.1;
		}
		else if (_currJumpCount > 0)
		{
			_force.y = -_adjustStat.jumpPower;
			_currJumpCount -= 1;
		}
	}

	// 대쉬
	if (!_gameScene->isUIActive() && KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::DASH)) && _currDashCount > 0)
	{
		//대쉬 효과음 재생
		SOUND_MANAGER->play("Player/Dash", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
		//대쉬 이펙트 재생
		Vector2 dashEffectPos = Vector2(_position.x + _size.x / 2, _position.y + _size.y / 2);
		Vector2 dashEffectSize = Vector2(_size.x * 2, _size.y * 2);
		EFFECT_MANAGER->play("PLAYER/DASH_DUST_EFFECT", dashEffectPos, dashEffectSize, 0, false);

		_currDashCount -= 1;
		float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - _position.y), (CAMERA->getAbsoluteX(_ptMouse.x) - _position.x));
		_force.x = cosf(angle) * _adjustStat.dashXPower;
		_force.y = -sinf(angle) * _adjustStat.dashYPower;
		_currDashTime = 0.1f;
		if (angle < 0)
		{
			_position.y += 1.5;
		}

		for (int i = 0; i < 4; i++) 
		{
			if (_equippedAcc[i] != nullptr)
			{
				_equippedAcc[i]->dash(this);
			}
		}
	}
	
	if (_currDashTime > 0) // 대쉬 상태라면
	{
		_currDashTime = max(0, _currDashTime - elapsedTime);
		if (_currDashTime == 0)
		{
			//_force.y = 0;
			// 대쉬 종료
			SOUND_MANAGER->stop("Player/Dash");
		}

	}

	
	if (_force.x != 0) // 대쉬의 영향을 받고 있다면
	{
		if (_currDashTime == 0)
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

	//서 있는 상태라면
	if (_isStand && _force.y == 0)
	{
		_position.y -= 15;
		moveDir.y += 21;
	}
	
	if (_currDashTime == 0) // 대쉬 중이지 않을 때 중력의 영향을 받기 시작
	{
		_force.y += _adjustStat.yGravity * elapsedTime;
	}
	moveDir.y += _force.y * elapsedTime;

	Vector2 lastPos = _position;
	_gameScene->moveTo(this, moveDir);
	Vector2 currPos = _position;
	// 착지
	if (_isStand)
	{
		_force.y = 0;
		_currJumpCount = _adjustStat.maxJumpCount;
	}
	// 머리 부딪힘
	if (moveDir.y < 0 && lastPos.y == currPos.y)
	{
		_force.y = 0;
	}

	// 점프 처리
	if (!_isStand)
	{
		_costume->setSprite(PLAYER_STATE::JUMP, false);
	}

	// 재장전 키를 눌렀을 때
	if (!_gameScene->isUIActive() && KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::RELOAD)))
	{
		if (_equippedWeapon[_currWeaponIndex] != nullptr)
		{
			_equippedWeapon[_currWeaponIndex]->reload(this);
		}
	}

	// 코스튬 애니메이션 업데이트
	_costume->update(elapsedTime);

	// 무기 업데이트
	if (_equippedWeapon[0] == nullptr && _equippedWeapon[1] == nullptr)
	{
		_hand->update(this, elapsedTime);
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			if (_equippedWeapon[i] != nullptr)
			{
				_equippedWeapon[i]->update(this, elapsedTime);
			}
			else
			{
				_hand->update(this, elapsedTime);
			}
		}
	}
	
	
	// 악세사리 업데이트
	for (int i = 0; i < _equippedAcc.size(); i++) 
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->update(this, elapsedTime);
		}
	}

	// 특수 능력 업데이트
	for (int i = 0; i < _specialAbility.size(); i++)
	{
		_specialAbility[i]->update(this, elapsedTime);
	}

	if (_currHitTime > 0)
	{
		_currHitTime = max(0, _currHitTime - elapsedTime);
	}
}

void Player::render()
{
	// D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Black, 1);


	if (_gameScene->showPlayer())
	{
		// 캐릭터 뒤에 그리기
		for (int i = 0; i < 4; i++)
		{
			if (_equippedAcc[i] != nullptr)
			{
				_equippedAcc[i]->backRender(this);
			}
		}
		if (_equippedWeapon[_currWeaponIndex] != nullptr)
		{
			_equippedWeapon[_currWeaponIndex]->backRender(this);
		}
		else
		{
			_hand->backRender(this);
		}
		for (int i = 0; i < _specialAbility.size(); i++)
		{
			_specialAbility[i]->backRender(this);
		}

		// 캐릭터 그리기
		_costume->render(CAMERA->getRelativeV2(_position), _direction, (_currHitTime > 0));

		// 캐릭터 앞에 그리기
		for (int i = 0; i < 4; i++)
		{
			if (_equippedAcc[i] != nullptr)
			{
				_equippedAcc[i]->frontRender(this);
			}
		}
		if (_equippedWeapon[_currWeaponIndex] != nullptr)
		{
			_equippedWeapon[_currWeaponIndex]->frontRender(this);
		}
		else
		{
			_hand->frontRender(this);
		}
		for (int i = 0; i < _specialAbility.size(); i++)
		{
			_specialAbility[i]->frontRender(this);
		}

		if (_currHitTime > 0)
		{
			if (_currHitTime < 0.25)
			{
				IMAGE_MANAGER->findImage("UI/WARNING_LEFT")->setAlpha((_currHitTime / 0.25));
				IMAGE_MANAGER->findImage("UI/WARNING_RIGHT")->setAlpha((_currHitTime / 0.25));
			}
			IMAGE_MANAGER->findImage("UI/WARNING_LEFT")->render(Vector2(WINSIZEX * 0.25f, WINSIZEY * 0.5f), Vector2(WINSIZEX * 0.5, WINSIZEY));
			IMAGE_MANAGER->findImage("UI/WARNING_RIGHT")->render(Vector2(WINSIZEX * 0.75f, WINSIZEY * 0.5f), Vector2(WINSIZEX * 0.5, WINSIZEY));
		}
	}

	//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, Vector2(10, 10), PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 1, 5);
}

bool Player::isHit(FloatRect* rc, AttackInfo* info)
{
	// 2가지 검사를 함
	// 1. 이미 피격 처리를 한 공격인지에 대해 검사
	// 2. 공격 렉트와 Enemy 렉트의 충돌 여부

	// [1] 이미 피격 처리를 한 공격인지에 대해 검사
	bool alreadyAttacked = false;
	for (int i = 0; i < _attackedId.size(); i++)
	{
		if (_attackedId[i] == info->attackID)
		{
			alreadyAttacked = true;
			break;
		}
	}
	if (alreadyAttacked) return false; // 이미 피격처리한 공격이라면 피격 처리 안함

	// [2] 피격 판정이 이루어져야하는지 검사
	FloatRect enemyRc = FloatRect(_position, _size, PIVOT::CENTER);
	FloatRect attackRc = FloatRect(rc->getCenter(), rc->getSize(), PIVOT::CENTER);

	if (!FloatRect::intersect(enemyRc, attackRc)) // 사각형과 사각형의 충돌 검사 함수
	{
		return false; // 피격 판정이 아니므로 피격 처리 안함
	}

	if (_attackedId.size() == 10) // 피격 처리를 해야 하는데 공격 ID 저장 벡터 사이즈가 10이라면
	{
		_attackedId.erase(_attackedId.begin()); // 맨 먼저 들어온 ID를 제거하고		
	}
	_attackedId.push_back(info->attackID); // 맨 뒤에 새로운 공격 ID 추가

	return true; // 위 검사 결과 피격 처리가 되어야 함
}

bool Player::isHit(FloatCircle* circle, AttackInfo* info)
{
	// 2가지 검사를 함
	// 1. 이미 피격 처리를 한 공격인지에 대해 검사
	// 2. 공격 호과 Enemy 렉트의 충돌 여부

	// [1] 이미 피격 처리를 한 공격인지에 대해 검사
	bool alreadyAttacked = false;
	for (int i = 0; i < _attackedId.size(); i++)
	{
		if (_attackedId[i] == info->attackID)
		{
			alreadyAttacked = true;
			break;
		}
	}
	if (alreadyAttacked) return false; // 이미 피격처리한 공격이라면 피격 처리 안함

	// [2] 피격 판정이 이루어져야하는지 검사
	FloatRect playerRc = FloatRect(_position, _size, PIVOT::CENTER);
	FloatCircle attackCircle = FloatCircle(circle->origin, circle->size, circle->startRadian, circle->endRadian);

	if (!attackCircle.intersect(playerRc)) // 호와 사각형의 충돌 검사 함수
	{
		return false; // 피격 판정이 아니므로 피격 처리 안함
	}

	if (_attackedId.size() == 10) // 피격 처리를 해야 하는데 공격 ID 저장 벡터 사이즈가 10이라면
	{
		_attackedId.erase(_attackedId.begin()); // 맨 먼저 들어온 ID를 제거하고
	}
	_attackedId.push_back(info->attackID); // 맨 뒤에 새로운 공격 ID 추가

	return true; // 위 검사 결과 피격 처리가 되어야 함
}

bool Player::isHit(Projectile* projectile, bool isOnceCollision)
{
	// TODO : 먼저 악세사리들에 대해서 검사해준다.
	for (int i = 0; i < 4; i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			if (isOnceCollision)
			{
				if (_equippedAcc[i]->isHit(projectile))
				{
					return true;
				}
			}
		}
	}
	// 2가지 검사를 함
	// 1. 이미 피격 처리를 한 공격인지에 대해 검사
	// 2. 공격 호과 Enemy 렉트의 충돌 여부

	// [1] 이미 피격 처리를 한 공격인지에 대해 검사
	AttackInfo* info = projectile->getAttackInfo();
	bool alreadyAttacked = false;
	for (int i = 0; i < _attackedId.size(); i++)
	{
		if (_attackedId[i] == info->attackID)
		{
			alreadyAttacked = true;
			break;
		}
	}
	if (alreadyAttacked) return false; // 이미 피격처리한 공격이라면 피격 처리 안함

	// [2] 피격 판정이 이루어져야하는지 검사
	FloatRect enemyRc = FloatRect(_position, _size, PIVOT::CENTER);
	FloatRect attackRc = FloatRect(projectile->getPosition(), projectile->getSize(), PIVOT::CENTER);

	if (!FloatRect::intersect(enemyRc, attackRc)) // 사각형과 사각형의 충돌 검사 함수
	{
		return false; // 피격 판정이 아니므로 피격 처리 안함
	}

	if (_attackedId.size() == 10) // 피격 처리를 해야 하는데 공격 ID 저장 벡터 사이즈가 10이라면
	{
		_attackedId.erase(_attackedId.begin()); // 맨 먼저 들어온 ID를 제거하고
	}
	_attackedId.push_back(info->attackID); // 맨 뒤에 새로운 공격 ID 추가

	return hitEffect(projectile); // 위 검사 결과 피격 처리가 되어야 함
}

bool Player::hitEffect(FloatRect* rc, AttackInfo* info)
{
	DamageInfo damageInfo = info->getDamageInfo(_adjustStat);
	if (damageInfo.damage > 0 || damageInfo.trueDamage > 0)
	{
		_currHp = max(0, _currHp - (damageInfo.damage + damageInfo.trueDamage));
		_currHitTime = 0.5;
		CAMERA->pushShakeEvent(info->knockBack, 0.25);
	}
	Vector2 renderPos;
	renderPos.x = RANDOM->getFromFloatTo(_position.x - _size.x, _position.x + _size.x);
	renderPos.y = RANDOM->getFromFloatTo(_position.y - _size.y, _position.y);
	_gameScene->showDamage(damageInfo, renderPos);

	return true;
}

bool Player::hitEffect(FloatCircle* circle, AttackInfo* info)
{
	DamageInfo damageInfo = info->getDamageInfo(_adjustStat);
	if (damageInfo.damage > 0 || damageInfo.trueDamage > 0)
	{
		_currHp = max(0, _currHp - (damageInfo.damage + damageInfo.trueDamage));
		_currHitTime = 0.5;
		CAMERA->pushShakeEvent(info->knockBack, 0.25);
	}
	Vector2 renderPos;
	renderPos.x = RANDOM->getFromFloatTo(_position.x - _size.x, _position.x + _size.x);
	renderPos.y = RANDOM->getFromFloatTo(_position.y - _size.y, _position.y);
	_gameScene->showDamage(damageInfo, renderPos);

	return false;
}

bool Player::hitEffect(Projectile* projectile)
{
	AttackInfo* info = projectile->getAttackInfo();
	DamageInfo damageInfo = info->getDamageInfo(_adjustStat);
	if (damageInfo.damage > 0 || damageInfo.trueDamage > 0)
	{
		_currHp = max(0, _currHp - (damageInfo.damage + damageInfo.trueDamage));
		_currHitTime = 0.5;
		CAMERA->pushShakeEvent(info->knockBack, 0.25);
	}
	Vector2 renderPos;
	renderPos.x = RANDOM->getFromFloatTo(_position.x - _size.x, _position.x + _size.x);
	renderPos.y = RANDOM->getFromFloatTo(_position.y - _size.y, _position.y);
	_gameScene->showDamage(damageInfo, renderPos);

	return true;
}

Image* Player::getWeaponImg(int index) const
{
	if (_equippedWeapon[index] != nullptr)
	{
		return _equippedWeapon[index]->getIconImg();
	}
	else
	{
		return nullptr;
	}
}

void Player::equipItem(int index)
{
	if (_inventory[index] == nullptr) return;
	if ((_inventory[index]->getItemCode() & static_cast<int>(ITEM_TYPE::ACC)) == static_cast<int>(ITEM_TYPE::ACC)) // 악세사리의 경우
	{
		for (int i = 0; i < 4; i++)
		{
			if (_equippedAcc[i] == nullptr)
			{
				swap(_inventory[index], _equippedAcc[i]);
				_equippedAcc[i]->equip(this);
				break;
			}
		}
	}
	else // 무기인 경우
	{
		swap(_inventory[index], _equippedWeapon[_currWeaponIndex]);
		_equippedWeapon[_currWeaponIndex]->equip(this);
	}
}

void Player::unequipWeapon(int index)
{
	if (_equippedWeapon[index] == nullptr) return;
	for (int i = 0; i < 15; i++)
	{
		if (_inventory[i] == nullptr)
		{
			swap(_inventory[i], _equippedWeapon[index]);
			break;
		}
	}

}

void Player::unequipAcc(int index)
{
	if (_equippedAcc[index] == nullptr) return;
	for (int i = 0; i < 15; i++)
	{
		if (_inventory[i] == nullptr)
		{
			swap(_inventory[i], _equippedAcc[index]);
			break;
		}
	}
}

void Player::swapItem(int indexA, int indexB) // 0 ~ 1 : weapon, 2 ~ 5 : Acc, 6 ~ 20 : inventory
{
	if (indexA <= 1) // A : Weapon
	{
		if (_equippedWeapon[indexA] == nullptr)
		{
		}
		else if (indexB <= 1) // B : Weapon
		{
			if (indexA == indexB) return;
			swap(_equippedWeapon[indexA], _equippedWeapon[indexB]);
		}
		else if (indexB <= 5) // B : Acc
		{
			return;
		}
		else // B : Inventory
		{
			if (_inventory[indexB - 6] == nullptr || (_inventory[indexB - 6]->getItemType() != ITEM_TYPE::ACC))
			{
				swap(_equippedWeapon[indexA], _inventory[indexB - 6]);
				if (_equippedWeapon[indexA] != nullptr)
				{
					_equippedWeapon[indexA]->equip(this);
				}
			}
		}
	}
	else if (indexA <= 5) // A : Acc
	{
		if (_equippedAcc[indexA - 2] == nullptr)
		{
		}
		else if (indexB <= 1) // B : Weapon
		{
			return;
			
		}
		else if (indexB <= 5) // B : Acc
		{
			if (indexA == indexB) return;
			swap(_equippedAcc[indexA - 2], _equippedAcc[indexB - 2]);
		}
		else // B : Inventory
		{
			if (_inventory[indexB - 6] == nullptr || (_inventory[indexB - 6]->getItemType() == ITEM_TYPE::ACC))
			{
				swap(_equippedAcc[indexA - 2], _inventory[indexB - 6]);
				if (_equippedAcc[indexA - 2])
				{
					_equippedAcc[indexA - 2]->equip(this);
				}
			}
		}
	}
	else // A : Inventory
	{
		if (_inventory[indexA - 6] == nullptr)
		{
		}
		else if (indexB <= 1) // B : Weapon
		{
			if ((_inventory[indexA - 6]->getItemType() == ITEM_TYPE::WEAPON_ONE_HAND) ||
				(_inventory[indexA - 6]->getItemType() == ITEM_TYPE::WEAPON_TWO_HAND))
			{
				swap(_inventory[indexA - 6], _equippedWeapon[indexB]);
				_equippedWeapon[indexB]->equip(this);
			}

		}
		else if (indexB <= 5) // B : Acc
		{
			if ((_inventory[indexA - 6]->getItemType() == ITEM_TYPE::ACC))
			{
				swap(_inventory[indexA - 6], _equippedAcc[indexB - 2]);
				_equippedAcc[indexB - 2]->equip(this);
			}
		}
		else // B : Inventory
		{
			if (indexA == indexB) return;
			swap(_inventory[indexA - 6], _inventory[indexB - 6]);
		}
	}
}

bool Player::ateFood(Food * food)
{
	// 플레이어의 현재 골드와 포만감을 비교하여 먹을 수 있다면
	// 먹고, TRUE 반환 (골드 빼주고, 포만감 더해주고)
	PlayerStat foodOneceStat = food->getOnceStat();
	if (_currGold >= food->getPrice() && (getMaxSatiety() - _currSatiety) >= foodOneceStat.currSatiety)
	{
		
		_ateFood.push_back(food);
		updateAdjustStat();
		_currGold -= food->getPrice();
		_currSatiety += foodOneceStat.currSatiety;
		_currHp = min(_adjustStat.maxHp, _currHp + foodOneceStat.currHp);
		
		return true;
	}
	// 못먹으면 FALSE 반한
	else
	{
		return false;
	}
	
}

void Player::setSpecialAbility(vector<Item*> specialAbility)
{
	_specialAbility = specialAbility;
}

void Player::setCurrCostume(Costume* costume)
{
	 _costume = costume;
	 setSpecialAbility(costume->getSpecialAbility()); 
	 updateAdjustStat();
	 _currHp = _adjustStat.maxHp;
}

float Player::getAttackSpeed()
{
	if (_equippedWeapon[_currWeaponIndex] == nullptr)
	{
		return _hand->getAttackSpeed();
	}
	else
	{
		return _equippedWeapon[_currWeaponIndex]->getAttackSpeed();
	}
}

float Player::getReloadSpeed()
{
	if (_equippedWeapon[_currWeaponIndex] == nullptr)
	{
		return _hand->getReloadSpeed();
	}
	else
	{
		return _equippedWeapon[_currWeaponIndex]->getReloadSpeed();
	}
}

float Player::getMinDamage()
{
	if (_equippedWeapon[_currWeaponIndex] == nullptr)
	{
		return _hand->getMinDamage();
	}
	else
	{
		return _equippedWeapon[_currWeaponIndex]->getMinDamage();
	}
}

float Player::getMaxDamage()
{
	if (_equippedWeapon[_currWeaponIndex] == nullptr)
	{
		return _hand->getMaxDamage();
	}
	else
	{
		return _equippedWeapon[_currWeaponIndex]->getMaxDamage();
	}
}

Vector2 Player::getEnemyPos(Vector2 pos)
{
	return _gameScene->getEnemyPos(pos);
}


vector<FloatRect> Player::getEnemyRects()
{
	return _gameScene->getEnemyRects();
}

void Player::moveRoom(Vector2 dir)
{
	_gameScene->moveRoom(dir);
}
