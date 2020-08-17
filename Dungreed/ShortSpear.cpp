#include "stdafx.h"
#include "ShortSpear.h"

void ShortSpear::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("ShortSpear");
	_price = 600;
	
	_itemName = L"단창";
	_itemCode = 0x02101; // 양손 일반
	_displayInfos.push_back(L"\"테스트를 위해 제작됨\"");
	_displayText = L"\"던질 수 있게 제작된 짧은 창\"";

	// 기본 보조옵션
	_addStat.dashDamage = 20;
	_addStat.minDamage = 7;
	_addStat.maxDamage = 10;
	_addStat.attackSpeed = 0.4;

	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_minDamage = 7;
	_maxDamage = 10;
	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
}

void ShortSpear::release()
{
}

void ShortSpear::update(Player* player, float const elapsedTime)
{
	if (_currAttackDelay == 0) return;

	float ratio = elapsedTime / (_baseAttackDelay * 0.15);
	if (_reverseMove)
	{
		_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 40 * ratio));
	}
	else
	{
		_attackMove.x = min(abs(cosf(_attackAngle) * 40), _attackMove.x + abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = min(abs(-sinf(_attackAngle) * 40), _attackMove.y + abs((-sinf(_attackAngle)) * 40 * ratio));

		if (_currAttackDelay <= _baseAttackDelay * 0.8)
		{
			_reverseMove = true;
			_drawEffect = true;
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
}

void ShortSpear::displayInfo()
{
}

void ShortSpear::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

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

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _baseAttackDelay;
}

void ShortSpear::attack(FloatRect * rect, AttackInfo* info)
{
}

void ShortSpear::attack(FloatCircle * circle, AttackInfo* info)
{
}

void ShortSpear::attack(Projectile * projectile, AttackInfo* info)
{
}

void ShortSpear::getHit(Vector2 const position)
{
}

void ShortSpear::equip(Player* player)
{
}
