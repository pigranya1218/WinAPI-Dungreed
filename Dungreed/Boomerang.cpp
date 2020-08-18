#include "Boomerang.h"

void Boomerang::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("MetalBoomerang");
	//_type = ITEM_TYPE::WEAPON_TWO_HAND;
	//_rank = ITEM_RANK::RARE;

	_itemCode = 0x02262;
	
	_itemName = L"부메랑";
	//_displayInfos.push_back(L"\"테스트를 위해 제작됨\"");
	_displayText = L"\"부메랑은 돌아오지만 사랑은 돌아오지 않는다.\"";

	_addStat.minDamage = 16;
	_addStat.maxDamage = 19;
	_addStat.attackSpeed = 0.5;

	_price = 550;

	_isAttack = false;

	// private 변수 설정
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
	//if (_currAttackDelay > 0) // 공격 딜레이 대기 중
	//{
	//	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	//}
	//else if (_currReloadDelay > 0) // 재장전 중
	//{
	//	_currReloadDelay = max(0, _currReloadDelay - elapsedTime);

	//	if (_currReloadDelay == 0) // 장전이 끝난 경우
	//	{
	//		_currBullet = _maxBullet;
	//	}
	//}

	_isLeft = (player->getDirection() == DIRECTION::LEFT);

	Vector2 renderPosHand = _pos;
	renderPosHand.x += ((_isLeft) ? (_img->getFrameSize().x * 0.1f * 4) : -(_img->getFrameSize().y * 0.1f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 15;

	// 손으로부터 마우스 에임까지의 각도
	_degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (_degree > 360)
	{
		_degree -= 360;
	}

	_renderDegree = _degree;
	if (_isLeft) // 왼쪽을 보고 있음
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

	//D2D_RENDERER->renderText(CAMERA->getRelativeX(player->getPosition().x), CAMERA->getRelativeY(player->getPosition().y - 100), to_wstring(_degree), 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
}

void Boomerang::displayInfo()
{
}

void Boomerang::attack(Player * player)
{
	//if (_currAttackDelay > 0) return; // 공격 쿨타임인 경우 공격을 하지 않음
	//if (_currReloadDelay > 0) return; // 장전 중엔 공격을 하지 않음
	//if (_currBullet == 0) // 총알이 없다면
	//{
	//	if (_currReloadDelay == 0) // 재장전 중이 아니라면
	//	{
	//		_currReloadDelay = _baseReloadDelay; // 재장전 함
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
	_currAttackDelay = _baseAttackDelay;	// 공격 쿨타임 설정
	_currBullet -= 1;						// 탄환 1 줄임
	
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
