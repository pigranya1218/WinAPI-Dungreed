#include "stdafx.h"
#include "Punch.h"

void Punch::init()
{
	_type = ITEM_TYPE::WEAPON_ONE_HAND;	//보조무기는 장착 가능
	_rank = ITEM_RANK::NORMAL;
	//주먹 이미지
	//가격 없음
	_price = 0;
	//보조 옵션 없음
	
	_attackMove = Vector2(0, 0);
	_minDamage = 1;
	_maxDamage = 4;
	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_reverseMove = false;

	//손 표현할 렉트
	_handSize = Vector2(7, 7);
}

void Punch::release()
{
}

void Punch::update(Player* player, float const elapsedTime)
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
		}
	}

	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void Punch::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	if (isLeft)
	{
		Vector2 renderPosLeft = Vector2(pos.x - 20, pos.y + 20);
		float angle = atan2f(-(_ptMouse.y - renderPosLeft.y), (_ptMouse.x - renderPosLeft.x)) * (180 / PI) + 360;
		if (angle > 360)
		{
			angle -= 360;
		}
		renderPosLeft.x += -_attackMove.x;
		renderPosLeft.y += ((angle >= 180)?(_attackMove.y):(-_attackMove.y));

		_leftHand = rectMakePivot(renderPosLeft, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_leftHand, D2DRenderer::DefaultBrush::Black, 4.f, angle, _leftHand.getCenter());
		D2D_RENDERER->fillRectangle(_leftHand, 251, 206, 177, 1, angle, _leftHand.getCenter());
	}
	else
	{
		Vector2 renderPosRight = Vector2(pos.x + 20, pos.y + 20);
		float angle = atan2f(-(_ptMouse.y - renderPosRight.y), (_ptMouse.x - renderPosRight.x)) * (180 / PI) + 360;
		if (angle > 360)
		{
			angle -= 360;
		}
		renderPosRight.x += _attackMove.x;
		renderPosRight.y += ((angle >= 180) ? (_attackMove.y) : (-_attackMove.y));

		_rightHand = rectMakePivot(renderPosRight, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_rightHand, D2DRenderer::DefaultBrush::Black, 4.f, angle, _rightHand.getCenter());
		D2D_RENDERER->fillRectangle(_rightHand, 251, 206, 177, 1, angle, _rightHand.getCenter());
	}
}

void Punch::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	if (isLeft)
	{
		Vector2 renderPosRight = Vector2(pos.x + 20, pos.y + 20);
		_rightHand = rectMakePivot(renderPosRight, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_rightHand, D2DRenderer::DefaultBrush::Black, 4.f);
		D2D_RENDERER->fillRectangle(_rightHand, 251, 206, 177, 1);
	}
	else
	{
		Vector2 renderPosLeft = Vector2(pos.x - 20, pos.y + 20);
		_leftHand = rectMakePivot(renderPosLeft, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_leftHand, D2DRenderer::DefaultBrush::Black, 4.f);
		D2D_RENDERER->fillRectangle(_leftHand, 251, 206, 177, 1);
	}
}

void Punch::displayInfo()
{
	//장비를 착용하지 않음
}

void Punch::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos; // 손의 위치
	renderPosHand.x += ((isLeft) ? (-20) : (20)); 
	renderPosHand.y += 20; 
	// 손으로부터 마우스 에임까지의 각도
	float angle = atan2f(-(_ptMouse.y - renderPosHand.y), (_ptMouse.x - renderPosHand.x)) + PI2;
	if (angle > PI2)
	{
		angle -= PI2;
	}

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _baseAttackDelay;
}

void Punch::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void Punch::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void Punch::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void Punch::getHit(Vector2 const position)
{
}
