#include "Player.h"
#include "GameScene.h"
#include "Costume.h"
#include "Item.h"

#include "ShortSpear.h"
#include "Punch.h"
#include "ShortSword.h"
#include "CosmosSword.h"

#include "OakBow.h"
#include "MatchLockGun.h"
#include "Boomerang.h"

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


// 장착 아이템 및 스킬에 따른 스탯 변화주기
void Player::updateAdjustStat()
{
	_adjustStat = _costume->getBaseStat();
}

void Player::swap(Item *& a, Item *& b)
{
	Item* temp = a;
	a = b;
	b = temp;
}

void Player::attack(FloatRect* rect, AttackInfo* info)
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

void Player::attack(FloatCircle* circle, AttackInfo* info)
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

void Player::attack(Projectile* projectile, AttackInfo* info)
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

	_gameScene->attack(projectile, info);
}

void Player::init()
{
	setSize(Vector2(40, 80));
	setPosition(Vector2(500, WINSIZEY - 250));
	_direction = DIRECTION::RIGHT;
	
	//최초에 장착하는 코스튬
	_costume = DATA_MANAGER->getCostume(COSTUME_TYPE::ALICE);
	_costume->init();

	updateAdjustStat();
	_level = 1;
	_currJumpCount = _adjustStat.maxJumpCount;
	_currDashCount = _adjustStat.maxDashCount;
	_currDashCoolTime = 0;
	//_currHp = _adjustStat.maxHp;
	_currHp = 40;
	_currSatiety = 30;
	_currGold = 1000;
	_force = Vector2(0, 0);

	// TEST ITEM
	_equippedWeapon.resize(2);
	_equippedAcc.resize(4);
	_inventory.resize(15);

	babyGreenBat* testAcc1 = new babyGreenBat;
	testAcc1->init();
	_inventory[0] = testAcc1;

	GreenBat* testAcc2 = new GreenBat;
	testAcc2->init();
	_inventory[1] = testAcc2;


	GreenDadBat* testAcc3 = new GreenDadBat;
	testAcc3->init();
	_inventory[2] = testAcc3;

	
	GreenMomBat* testAcc4 = new GreenMomBat;
	testAcc4->init();
	_inventory[3] = testAcc4;


	SpikeBall* testAcc9 = new SpikeBall;
	testAcc9->init();
	_inventory[4] = testAcc9;


	bombPouch* testAcc5 = new bombPouch;
	testAcc5->init();
	_inventory[5] = testAcc5;


	IceBall* testAcc6 = new IceBall;
	testAcc6->init();
	_inventory[6] = testAcc6;


	miniEarth* testAcc7 = new miniEarth;
	testAcc7->init();
	_inventory[7] = testAcc7;


	watCher* testAcc8 = new watCher;
	testAcc8->init();
	_inventory[8] = testAcc8;

	
	MagnifyingGlass* testAcc10 = new MagnifyingGlass;
	testAcc10->init();
	_inventory[9] = testAcc10;

	CosmosSword* testAcc11 = new CosmosSword;
	testAcc11->init();
	_inventory[10] = testAcc11;

	MatchLockGun* testWeapon1 = new MatchLockGun;
	testWeapon1->init();
	_inventory[11] = testWeapon1;
	
	/*ShortSpear* testWeapon2 = new ShortSpear;
	testWeapon2->init();
	_inventory[11] = testWeapon2;*/

	ShortSword* testWeapon3 = new ShortSword;
	testWeapon3->init();
	_inventory[12] = testWeapon3;

	OakBow* testWeapon4 = new OakBow;
	testWeapon4->init();
	_inventory[13] = testWeapon4;

	Boomerang* testWeapon5 = new Boomerang;
	testWeapon5->init();
	_inventory[14] = testWeapon5;

	_hand = new Punch;
	_hand->init();

	_currWeaponIndex = 0;
	_currWeaponChangeCoolTime = 0;
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
	
	if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_LEFT)) || KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_RIGHT))) // 좌우 이동중
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
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::JUMP)))
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
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::DASH)) && _currDashCount > 0)
	{
		_currDashCount -= 1;
		float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - _position.y), (CAMERA->getAbsoluteX(_ptMouse.x) - _position.x));
		_force.x = cosf(angle) * _adjustStat.dashXPower;
		_force.y = -sinf(angle) * _adjustStat.dashYPower;

		for (int i = 0; i < 4; i++) 
		{
			if (_equippedAcc[i] != nullptr)
			{
				_equippedAcc[i]->dash(this);
			}
		}
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
	if (_isStand && _force.y == 0)
	{
		_position.y -= 15;
		moveDir.y += 25;
	}
	
	_force.y += _adjustStat.yGravity * elapsedTime;
	moveDir.y += _force.y * elapsedTime;


	_gameScene->moveTo(this, moveDir);
	//착지
	if (_isStand)
	{
		_force.y = 0;
		_currJumpCount = _adjustStat.maxJumpCount;
	}

	// 점프 처리
	if (!_isStand)
	{
		_costume->setSprite(PLAYER_STATE::JUMP, false);
	}

	// 재장전 키를 눌렀을 때
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::RELOAD)))
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
}

void Player::render()
{
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Black, 1);

	// 캐릭터 뒤에 그리기
	for(int i = 0; i < 4; i++)
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

	// 캐릭터 그리기
	// _costume->render(CAMERA->getRelativeV2(_position), _direction);

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

	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, Vector2(10, 10), PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 1, 5);
}

Image* Player::getWeaponImg(int index) const noexcept
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
	if (_inventory[index]->getType() == ITEM_TYPE::ACC) // 악세사리의 경우
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
			if (_inventory[indexB - 6] == nullptr || _inventory[indexB - 6]->getType() != ITEM_TYPE::ACC)
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
			if (_inventory[indexB - 6] == nullptr || _inventory[indexB - 6]->getType() == ITEM_TYPE::ACC)
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
			if (_inventory[indexA - 6]->getType() != ITEM_TYPE::ACC)
			{
				swap(_inventory[indexA - 6], _equippedWeapon[indexB]);
				_equippedWeapon[indexB]->equip(this);
			}

		}
		else if (indexB <= 5) // B : Acc
		{
			if (_inventory[indexA - 6]->getType() == ITEM_TYPE::ACC)
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
