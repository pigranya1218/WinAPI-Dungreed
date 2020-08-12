#include "Player.h"
#include "GameScene.h"
#include "Costume.h"
#include "Item.h"

#include "ShortSpear.h"
#include "Punch.h"
#include "MatchLockGun.h"
#include "Boomerang.h"
#include "ShortSword.h"

#include "SpikeBall.h"
#include "IceBall.h"
#include "miniEarth.h"
#include "watCher.h"
#include "babyGreenBat.h"
#include "bombPouch.h"
#include "Matchlock.h"


// ���� ������ �� ��ų�� ���� ���� ��ȭ�ֱ�
void Player::updateAdjustStat()
{
	_adjustStat = _costume->getBaseStat();
}

void Player::attack(FloatRect* rect, tagAttackInfo* info)
{
	// ������ ȿ�� ����
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->attack(rect, info);
		}
	}

	// �÷��̾� ���� ����
}

void Player::attack(FloatCircle* circle, tagAttackInfo* info)
{
	// ������ ȿ�� ����
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->attack(circle, info);
		}
	}

	// �÷��̾� ���� ����
}

void Player::attack(Projectile* projectile, tagAttackInfo* info)
{
	// ������ ȿ�� ����
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		if (_equippedAcc[i] != nullptr)
		{
			_equippedAcc[i]->attack(projectile, info);
		}
	}

	// �÷��̾� ���� ����

	_gameScene->attack(projectile, info);
}

void Player::init()
{
	setSize(Vector2(40, 90));
	setPosition(Vector2(200, WINSIZEY - 250));
	_direction = DIRECTION::RIGHT;
	
	_costume = DATA_MANAGER->getCostume(COSTUME_TYPE::METAL_PLATE);
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
	SpikeBall* testAcc1 = new SpikeBall;
	testAcc1->init();
	_equippedAcc.push_back(testAcc1);
	
	babyGreenBat* testAcc2 = new babyGreenBat;
	testAcc2->init();
	_equippedAcc.push_back(testAcc2);

	bombPouch* testAcc3 = new bombPouch;
	testAcc3->init();
	_equippedAcc.push_back(testAcc3);

	IceBall* testAcc4 = new IceBall;
	testAcc4->init();
	_equippedAcc.push_back(testAcc4);

	miniEarth* testAcc5 = new miniEarth;
	testAcc5->init();
	_equippedAcc.push_back(testAcc5);

	watCher* testAcc6 = new watCher;
	testAcc6->init();
	_equippedAcc.push_back(testAcc6);

	MatchLockGun* testWeapon1 = new MatchLockGun;
	testWeapon1->init();
	_equippedWeapon.push_back(testWeapon1);
	
	ShortSpear* testWeapon2 = new ShortSpear;
	testWeapon2->init();
	_equippedWeapon.push_back(testWeapon2);

	_currWeaponIndex = 0;
	_currWeaponChangeCoolTime = 0;
}

void Player::release()
{
	for (int i = 0; i < _inventory.size(); i++)
	{
		_inventory[i]->release();
		delete _inventory[i];
	}
	for (int i = 0; i < _equippedWeapon.size(); i++)
	{
		_equippedWeapon[i]->release();
		delete _equippedWeapon[i];
	}
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		_equippedAcc[i]->release();
		delete _equippedAcc[i];
	}
	_inventory.clear();
	_equippedWeapon.clear();
	_equippedAcc.clear();
}

void Player::update(float const elapsedTime)
{
	// ������, ��ų�� ���� ���� ���� (������ ���� ��)
	// updateAdjustStat();

	//���� ����
	if (_ptMouse.x < _position.x)
	{
		_direction = DIRECTION::LEFT;
	}
	else
	{
		_direction = DIRECTION::RIGHT;
	}

	// ��� ��ü
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::CHANGE_WEAPON)) && _currWeaponChangeCoolTime == 0)
	{
		_currWeaponIndex = !_currWeaponIndex;
		_currWeaponChangeCoolTime = 1;
	}

	// ��� ��ü �ð� ������
	if (_currWeaponChangeCoolTime > 0)
	{
		_currWeaponChangeCoolTime -= elapsedTime;
		if (_currWeaponChangeCoolTime < 0) _currWeaponChangeCoolTime = 0;
	}

	// ����
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
	{
		_equippedWeapon[_currWeaponIndex]->attack(this);
		for (int i = 0; i < _equippedAcc.size(); i++)
		{
			if (_equippedAcc[i] != nullptr)
			{
				_equippedAcc[i]->attack(this);
			}
		}
	}

	//�̵�
	Vector2 moveDir(0, 0);
	
	if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_LEFT)) || KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MOVE_RIGHT))) // �¿� �̵���
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
	else // �̵� ���ϴ� �� 
	{
		_costume->setSprite(PLAYER_STATE::IDLE, false);
	}

	// ����
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

	// �뽬
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::DASH)) && _currDashCount > 0)
	{
		_currDashCount -= 1;
		float angle = atan2f(-(_ptMouse.y - _position.y), (_ptMouse.x - _position.x));
		_force.x = cosf(angle) * _adjustStat.dashXPower;
		_force.y = -sinf(angle) * _adjustStat.dashYPower;
	}
	
	if (_force.x != 0) // �뽬 ���¶��
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

	//�뽬 ��Ÿ��
	if (_currDashCount < _adjustStat.maxDashCount)
	{
		_currDashCoolTime += elapsedTime;
		if (_currDashCoolTime > _adjustStat.dashCoolTime)
		{
			_currDashCount += 1;
			_currDashCoolTime = 0;
		}
	}

	//�ϰ���
	if (_isStand && _force.y == 0)
	{
		_position.y -= 15;
		moveDir.y += 25;
	}
	
	_force.y += _adjustStat.yGravity * elapsedTime;
	moveDir.y += _force.y * elapsedTime;


	_gameScene->moveTo(this, moveDir);
	//����
	if (_isStand)
	{
		_force.y = 0;
		_currJumpCount = _adjustStat.maxJumpCount;
	}

	//���� ó��
	if (!_isStand)
	{
		_costume->setSprite(PLAYER_STATE::JUMP, false);
	}

	// �ڽ�Ƭ �ִϸ��̼� ������Ʈ
	_costume->update(elapsedTime);

	// ���� ������Ʈ
	for (int i = 0; i < _equippedWeapon.size(); i++) 
	{
		_equippedWeapon[i]->update(this, elapsedTime);
	}
	
	// �Ǽ��縮 ������Ʈ
	for (int i = 0; i < _equippedAcc.size(); i++) 
	{
		_equippedAcc[i]->update(this, elapsedTime);
	}
}

void Player::render()
{
	D2D_RENDERER->drawRectangle(FloatRect(_position, _size, PIVOT::CENTER), D2D1::ColorF::Enum::Black, 1);

	// ĳ���� �ڿ� �׸���
	for(int i = 0; i < _equippedAcc.size(); i++)
	{
		_equippedAcc[i]->backRender(this);	
	}
	_equippedWeapon[_currWeaponIndex]->backRender(this);

	// ĳ���� �׸���
	_costume->render(_position, _direction);

	// ĳ���� �տ� �׸���
	for (int i = 0; i < _equippedAcc.size(); i++)
	{
		_equippedAcc[i]->frontRender(this);
	}
	_equippedWeapon[_currWeaponIndex]->frontRender(this);
}

Image* Player::getWeaponImg(int index) const noexcept
{
	return _equippedWeapon[index]->getImg();
}
