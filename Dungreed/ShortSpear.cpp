#include "stdafx.h"
#include "ShortSpear.h"

void ShortSpear::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("ShortSpear");
	_price = 600;
	
	_itemName = L"단창";
	_displayText = L"\"던질 수 있게 제작된 짧은 창\"";
	_itemCode = 0x02101; // 양손 일반

	// 기본 보조옵션
	_addStat.dashDamage = 20;
	_addStat.minDamage = 7;
	_addStat.maxDamage = 10;
	_addStat.attackSpeed = 0.4;

	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
}



void ShortSpear::update(Player* player, float const elapsedTime)
{
	if (_currAttackDelay == 0) return;

	float ratio = elapsedTime / (_adjustStat.attackSpeed * 0.15);
	if (_reverseMove)
	{
		_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 40 * ratio));
	}
	else
	{
		_attackMove.x = min(abs(cosf(_attackAngle) * 40), _attackMove.x + abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = min(abs(-sinf(_attackAngle) * 40), _attackMove.y + abs((-sinf(_attackAngle)) * 40 * ratio));

		// 찌르는 모션동안 계속 공격판정
		player->attack(_attackCircle, _attackInfo);

		if (_currAttackDelay <= _adjustStat.attackSpeed * 0.8)
		{
			_reverseMove = true;
			_drawEffect = true;
			delete _attackCircle;
			delete _attackInfo;
		}
	}

	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void ShortSpear::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	Vector2 renderPos = Vector2(pos.x + ((isLeft) ? (-22) : (22)), pos.y + 20);
	FloatRect handRc = rectMakePivot(renderPos, Vector2(5, 5), PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1);
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1, 2.f);
}

void ShortSpear::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	
	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 20; // 플레이어의 중점으로부터 무기를 들고 있는 높이
	// 손으로부터 마우스 에임까지의 각도
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	Vector2 renderPosWeapon = renderPosHand;
	renderPosWeapon.x -= ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4));
	
	float renderDegree = degree;
	if (isLeft) // 왼쪽을 보고 있음
	{
		renderDegree = 180 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}
	renderPosWeapon.x += ((isLeft)?(-_attackMove.x):(_attackMove.x));
	renderPosWeapon.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));
	renderPosHand.x += ((isLeft)?(-_attackMove.x):(_attackMove.x));
	renderPosHand.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));

	_img->setScale(4);
	_img->setAngle(renderDegree);
	_img->setAnglePos(Vector2(0.35f * _img->getWidth(), 0.5f * _img->getHeight()));
	_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));
	
	if (_drawEffect) // 이펙트를 그린다
	{
		_drawEffect = false;
		Vector2 effectPos = renderPosHand; // 손의 위치로부터
		float length = _img->getWidth() * 4 * 0.7; // 무기 길이만큼
		effectPos.x += cosf(degree * (PI / 180)) * length;
		effectPos.y += -sinf(degree * (PI / 180)) * length;
		// D2D_RENDERER->drawRectangle(FloatRect(effectPos, Vector2(10, 10), PIVOT::CENTER), D2DRenderer::DefaultBrush::Black, 1, angle, effectPos);
		EFFECT_MANAGER->play("EFFECT_STAB", effectPos, Vector2(35, 35), degree);
	}
	if (_attackCircle != nullptr)
	{
		_attackCircle->render(true);
	}
}


void ShortSpear::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	CAMERA->pushShakeEvent(10, 0.1f);

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);

	Vector2 pos = player->getPosition();
	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 20; // 플레이어의 중점으로부터 무기를 들고 있는 높이
	// 손으로부터 마우스 에임까지의 각도
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angle > PI2)
	{
		angle -= PI2;
	}
	_attackAngle = angle;

	_reverseMove = false;
	_currAttackDelay = _adjustStat.attackSpeed;
	Vector2 originPos = player->getPosition();
	originPos.x += ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4)); // 손의 위치는 무기의 회전 중심점
	originPos.y += 20; // 플레이어의 중점으로부터 무기를 들고 있는 높이
	float attackRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x));
	if (attackRadian < 0)
	{
		attackRadian += PI2;
	}
	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함

	SOUND_MANAGER->stop("SOUND_generalAttack");
	SOUND_MANAGER->play("SOUND_generalAttack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

	_attackCircle = new FloatCircle;
	_attackCircle->origin = originPos;
	_attackCircle->size = 150;
	_attackCircle->startRadian = attackRadian - PI * 0.05;
	_attackCircle->endRadian = attackRadian + PI * 0.05;
	_attackInfo = new AttackInfo;
	_attackInfo->team = OBJECT_TEAM::PLAYER;
	_attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	_attackInfo->critical = 0;
	_attackInfo->criticalDamage = 0;
	_attackInfo->minDamage = _addStat.minDamage;
	_attackInfo->maxDamage = _addStat.maxDamage;
	_attackInfo->knockBack = 5;
}



void ShortSpear::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}
