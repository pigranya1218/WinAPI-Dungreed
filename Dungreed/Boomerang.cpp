#include "Boomerang.h"

void Boomerang::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("MetalBoomerang");
	_itemCode = 0x02262;
	
	_itemName = L"�θ޶�";
	_displayText = L"\"�θ޶��� ���ƿ����� ����� ���ƿ��� �ʴ´�.\"";

	_addStat.minDamage = 16;
	_addStat.maxDamage = 19;
	_addStat.attackSpeed = 0.5;

	_price = 550;

	_isAttack = false;

	// private ���� ����
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_baseReloadDelay = 2;
	_currReloadDelay = 0;
	_returnCount = 0;

	attackInfo02 = new AttackInfo;

	_projectile = nullptr;
}

void Boomerang::release()
{
}

void Boomerang::update(Player * player, float const elapsedTime)
{
	_isLeft = (player->getDirection() == DIRECTION::LEFT);

	Vector2 renderPosHand = _pos;
	renderPosHand.x += ((_isLeft) ? (_img->getFrameSize().x * 0.1f * 4) : -(_img->getFrameSize().y * 0.1f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 15;

	// �����κ��� ���콺 ���ӱ����� ����
	_degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (_degree > 360)
	{
		_degree -= 360;
	}

	_renderDegree = _degree;
	if (_isLeft) // ������ ���� ����
	{
		_renderDegree = 180 - _degree;
		if (_renderDegree < 0) _renderDegree += 360;
	}

	_pos = player->getPosition();
	_gunPos = _isLeft ? Vector2(_pos.x - 20, _pos.y + 15) : Vector2(_pos.x + 20, _pos.y + 15);

	if (_projectile != nullptr)
	{
		if (_projectile->getReturn())
		{
			_returnCount += elapsedTime;
			FloatRect projectileRc = FloatRect(_projectile->getPosition(), _projectile->getSize(), PIVOT::CENTER);
			FloatRect playerRc = FloatRect(player->getPosition(), player->getSize(), PIVOT::CENTER);
			if (FloatRect::intersect(projectileRc, playerRc))
			{
				_projectile->setActive(false);
				_projectile = nullptr;
			}

			else if (_returnCount > 2.5f)
			{
				_returnCount = 0;
				_projectile->setActive(false);
				_projectile = nullptr;
			}
		}
	}
}

void Boomerang::backRender(Player * player)
{
}

void Boomerang::frontRender(Player * player)
{
	if (_projectile == nullptr)
	{
		Vector2 _centerPos = Vector2(_img->getSize().x / 2, _img->getSize().y / 2);
		_img->setScale(4);
		_img->setAnglePos(_centerPos);

		_img->setAngle(_renderDegree);
		_img->render(CAMERA->getRelativeV2(_gunPos), _isLeft);
	}
}

void Boomerang::displayInfo()
{
}

void Boomerang::attack(Player * player)
{
	if (_projectile != nullptr) return;

	float _angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - _gunPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - _gunPos.x)) + PI2;
	if (_angleRadian > PI2)
	{
		_angleRadian -= PI2;
	}

	_projectile = new BoomerangProjectile;
	_projectile->setPosition(_gunPos);
	_projectile->setSize(Vector2(_img->getFrameSize().x * 4, _img->getFrameSize().y * 4));
	_projectile->setTeam(OBJECT_TEAM::PLAYER);
	_projectile->init("Boomerang_Moving", _angleRadian, 30 * 15, true, true, 20, true, "", Vector2(), 1);

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // ������ �ڵ�� ���� �ð��� Concat�Ͽ� ���� ���̵� ���ϱ� ���� ���� �ڵ带 ������

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = _addStat.minDamage;
	attackInfo->maxDamage = _addStat.maxDamage;
	attackInfo->knockBack = 30;

	player->attack(_projectile, attackInfo);
	_currBullet -= 1;						// źȯ 1 ����
	
}

void Boomerang::attack(FloatRect * rect, AttackInfo * info)
{
}

void Boomerang::attack(FloatCircle * circle, AttackInfo * info)
{
}

void Boomerang::attack(Projectile * projectile, AttackInfo * info)
{
}

void Boomerang::getHit(Vector2 const position)
{
}

void Boomerang::equip(Player* player)
{
}
