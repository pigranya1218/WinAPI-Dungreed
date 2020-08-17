#include "stdafx.h"
#include "MartialArtOfTiger.h"

void MartialArtOfTiger::init()
{
	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	_effect = IMAGE_MANAGER->findImage("EFFECT_TIGERPUNCH");
	_iconImg =IMAGE_MANAGER->findImage("TigerPunchIcon");
	_price = 600;
	
	// 기본 보조옵션
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);


	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_minDamage = 7;
	_maxDamage = 10;
	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	

}

void MartialArtOfTiger::release()
{

}

void MartialArtOfTiger::update(Player* player, float const elapsedTime)
{
	if (_currAttackDelay == 0) return;
	
	float ratio = elapsedTime / (_baseAttackDelay * 0.08);
	if (_reverseMove)
	{
		_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 30 * ratio));
		_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 30 * ratio));
	}
	else
	{
		_attackMove.x = min(abs(cosf(_attackAngle) * 30), _attackMove.x + abs(cosf(_attackAngle) * 30 * ratio));
		_attackMove.y = min(abs(-sinf(_attackAngle) * 30), _attackMove.y + abs((-sinf(_attackAngle)) * 30 * ratio));

		if (_currAttackDelay <= _baseAttackDelay * 0.88)
		{
			_reverseMove = true;
			_drawEffect = true;
		}
	}

	


	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);

}

void MartialArtOfTiger::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	if (isLeft)
	{
		Vector2 renderPosLeft = Vector2(pos.x - 20, pos.y + 18);
		float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosLeft.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosLeft.x)) * (180 / PI) + 360;
		if (angle > 360)
		{
			angle -= 360;
		}
		renderPosLeft.x += -_attackMove.x;
		renderPosLeft.y += ((angle >= 180) ? (_attackMove.y) : (-_attackMove.y));

		_leftHand = rectMakePivot(renderPosLeft, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_leftHand), 210, 188, 181, 1.f, angle, CAMERA->getRelativeV2(_leftHand.getCenter()));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_leftHand), 40, 36, 58, 1, 2.f, angle, CAMERA->getRelativeV2(_leftHand.getCenter()));
	}
	else
	{
		Vector2 renderPosRight = Vector2(pos.x + 20, pos.y + 18);
		float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosRight.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosRight.x)) * (180 / PI) + 360;
		if (angle > 360)
		{
			angle -= 360;
		}
		renderPosRight.x += _attackMove.x;
		renderPosRight.y += ((angle >= 180) ? (_attackMove.y) : (-_attackMove.y));

		_rightHand = rectMakePivot(renderPosRight, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_rightHand), 210, 188, 181, 1.f, angle, CAMERA->getRelativeV2(_rightHand.getCenter()));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rightHand), 40, 36, 58, 1, 2.f, angle, CAMERA->getRelativeV2(_rightHand.getCenter()));
	}
}

void MartialArtOfTiger::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x)) * (180 / PI);

	if (isLeft)
	{
		Vector2 renderPosRight = Vector2(pos.x + 20, pos.y + 18);
		_rightHand = rectMakePivot(renderPosRight, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_rightHand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rightHand), 40, 36, 58, 1, 2.f);
		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = pos; // 회전축의 위치로부터
			float length = _iconImg->getWidth() * 4 * 1; // 무기 길이만큼
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_TIGERPUNCH", effectPos, Vector2(200, 200), 0);
		}

	}
	else
	{
		Vector2 renderPosLeft = Vector2(pos.x - 20, pos.y + 18);
		_leftHand = rectMakePivot(renderPosLeft, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_leftHand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_leftHand), 40, 36, 58, 1, 2.f);
		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = pos; // 회전축의 위치로부터
			float length = _iconImg->getWidth() * 4 * 1; // 무기 길이만큼
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			
			
			EFFECT_MANAGER->play("EFFECT_TIGERPUNCH", effectPos, Vector2(200, 200), 0);
		}

	}
}

void MartialArtOfTiger::displayInfo()
{
}

void MartialArtOfTiger::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos; // 손의 위치
	renderPosHand.x += ((isLeft) ? (-20) : (20));
	renderPosHand.y += 20;
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

void MartialArtOfTiger::attack(FloatRect* rect, AttackInfo* info)
{
}

void MartialArtOfTiger::attack(FloatCircle* circle, AttackInfo* info)
{
}

void MartialArtOfTiger::attack(Projectile* projectile, AttackInfo* info)
{
}

void MartialArtOfTiger::getHit(Vector2 const position)
{
}

PlayerStat MartialArtOfTiger::equip()
{
	return PlayerStat();
}

