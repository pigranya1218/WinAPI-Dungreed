#include "Boomerang.h"

void Boomerang::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("MetalBoomerang");
	//_type = ITEM_TYPE::WEAPON_TWO_HAND;
	//_rank = ITEM_RANK::RARE;

	_itemCode = 0x02262;
	
	_itemName = L"�θ޶�";
	//_displayInfos.push_back(L"\"�׽�Ʈ�� ���� ���۵�\"");
	_displayText = L"\"�θ޶��� ���ƿ����� ����� ���ƿ��� �ʴ´�.\"";

	_addStat.minDamage = 16;
	_addStat.maxDamage = 19;
	_addStat.attackSpeed = 0.5;

	_price = 550;

	_isAttack = false;

	// private ���� ����
	_minDamage = 12;
	_maxDamage = 18;
	_baseAttackDelay = 1;
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_baseReloadDelay = 2;
	_currReloadDelay = 0;
	_returnCount = 0;

	//_aniImg = IMAGE_MANAGER->findImage("Boomerang_Moving");
	//_ani = new Animation;
	//_ani->init(_aniImg->getWidth(), _aniImg->getHeight(), 2, 1);
	//_ani->setPlayFrame(0, 2, false, true);
	//_ani->setFPS(15);

	_projectile = nullptr;
}

void Boomerang::release()
{
}

void Boomerang::update(Player * player, float const elapsedTime)
{
	//if (_currAttackDelay > 0) // ���� ������ ��� ��
	//{
	//	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	//}
	//else if (_currReloadDelay > 0) // ������ ��
	//{
	//	_currReloadDelay = max(0, _currReloadDelay - elapsedTime);

	//	if (_currReloadDelay == 0) // ������ ���� ���
	//	{
	//		_currBullet = _maxBullet;
	//	}
	//}

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

			else if (_returnCount > 2.5)
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

	//D2D_RENDERER->renderText(CAMERA->getRelativeX(player->getPosition().x), CAMERA->getRelativeY(player->getPosition().y - 100), to_wstring(_degree), 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.0f);
}

void Boomerang::displayInfo()
{
}

void Boomerang::attack(Player * player)
{
	//if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
	//if (_currReloadDelay > 0) return; // ���� �߿� ������ ���� ����
	//if (_currBullet == 0) // �Ѿ��� ���ٸ�
	//{
	//	if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
	//	{
	//		_currReloadDelay = _baseReloadDelay; // ������ ��
	//	}
	//	return;
	//}

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
	_projectile->init("Boomerang_Moving", _angleRadian, 30 * 15, true, true, 20, "", Vector2(), 1);

	/*NormalProjectile* _projectile = new NormalProjectile;
	_projectile->setPosition(_gunPos);
	_projectile->setSize(Vector2(_img->getFrameSize().x * 4, _img->getFrameSize().y * 4));
	_projectile->setTeam(OBJECT_TEAM::PLAYER);
	_projectile->init("Boomerang_Moving", _angleRadian, 30 * 10, true, true, 20, false, "", Vector2(), 1000);*/

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	player->attack(_projectile, attackInfo);
	_currAttackDelay = _baseAttackDelay;	// ���� ��Ÿ�� ����
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
