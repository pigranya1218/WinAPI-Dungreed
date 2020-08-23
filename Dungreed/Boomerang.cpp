#include "Boomerang.h"

void Boomerang::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("MetalBoomerang");
	_itemCode = 0x02262;
	
	_itemName = L"부메랑";
	_displayText = L"\"부메랑은 돌아오지만 사랑은 돌아오지 않는다.\"";

	_addStat.minDamage = 16;
	_addStat.maxDamage = 19;
	_addStat.attackSpeed = 0.5;

	_price = 550;

	_isAttack = false;
	_effectCount = 0;

	// private 변수 설정
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
				_effectCount++;
				_projectile->setActive(false);
				_projectile = nullptr;
				_returnCount = 0;
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
	if (_projectile == nullptr)
	{
		Vector2 _centerPos = Vector2(_img->getSize().x / 2, _img->getSize().y / 2);
		_img->setScale(4);
		_img->setAnglePos(_centerPos);

		_img->setAngle(_renderDegree);
		_img->render(CAMERA->getRelativeV2(_gunPos), _isLeft);
	}
}

void Boomerang::frontRender(Player * player)
{
	if (_effectCount == 1)
	{
		Image* effectImg = IMAGE_MANAGER->findImage("BoomerangEffect");
		Vector2 effectSize = Vector2(effectImg->getFrameSize().x * 4, effectImg->getFrameSize().y * 4);
		EFFECT_MANAGER->play("L_Effect_Boomerang", _pos, effectSize, _isLeft);
		_effectCount = 0;
	}

	//D2D_RENDERER->renderText(CAMERA->getRelativeX(_pos.x), CAMERA->getRelativeY(_pos.y - 50), to_wstring(_returnCount), 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.f);
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

	Image* effectImg02 = IMAGE_MANAGER->findImage("BoomerangEffect");
	Vector2 effectSize02 = Vector2(effectImg02->getFrameSize().x * 4, effectImg02->getFrameSize().y * 4);

	SOUND_MANAGER->stop("boomerang_attack_sound");
	SOUND_MANAGER->play("boomerang_attack_sound", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
	EFFECT_MANAGER->play("L_Effect_Boomerang", _pos, effectSize02, _isLeft);

	_projectile = new BoomerangProjectile;
	_projectile->setPosition(_gunPos);
	_projectile->setSize(Vector2(_img->getFrameSize().x * 4, _img->getFrameSize().y * 4));
	_projectile->setTeam(OBJECT_TEAM::PLAYER);
	_projectile->init("Boomerang_Moving", _angleRadian, 30 * 15, true, true, 20, true, "", Vector2(effectSize02), Vector2(30 * 10, 30 * 10), 1.5);

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->madeByWeapon = true;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = _addStat.minDamage;
	attackInfo->maxDamage = _addStat.maxDamage;
	attackInfo->knockBack = 30;

	player->attack(_projectile, attackInfo);
	_currBullet -= 1;						// 탄환 1 줄임
	_effectCount = 0;
}

void Boomerang::attack(Player* player, FloatRect * rect, AttackInfo * info)
{
}

void Boomerang::attack(Player* player, FloatCircle * circle, AttackInfo * info)
{
}

void Boomerang::attack(Player* player, Projectile * projectile, AttackInfo * info)
{
}

void Boomerang::getHit(Vector2 const position)
{
}

void Boomerang::equip(Player* player)
{
}
