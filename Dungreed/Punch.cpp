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
	_minDamage = 0;
	_maxDamage = 4;
	_baseAttackDelay = 0.5;
	_currAttackDelay = 0;
	_reverseMove = false;

	//손 표현할 렉트
	_handSize = Vector2(7, 7);
}

void Punch::release()
{
}

void Punch::update(float const elapsedTime)
{
	if (_currAttackDelay == 0) return;

	float ratio = elapsedTime / (_baseAttackDelay * 0.08);
	if (_reverseMove)
	{
		_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 40 * ratio));
	}
	else
	{
		_attackMove.x = min(abs(cosf(_attackAngle) * 40), _attackMove.x + abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = min(abs(-sinf(_attackAngle) * 40), _attackMove.y + abs((-sinf(_attackAngle)) * 40 * ratio));

		if (_currAttackDelay <= _baseAttackDelay * 0.88)
		{
			_reverseMove = true;
		}
	}

	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void Punch::render(Vector2 pos, float angle)
{
	Vector2 renderPosLeft = Vector2(pos.x - 25, pos.y + 20);
	Vector2 renderPosRight = Vector2(pos.x + 25, pos.y + 20);
	bool isLeft = false;
	if (angle >= 90 && angle <= 270) // 왼쪽을 보고 있음
	{
		isLeft = true;
		angle = fmod((180 - angle) + 360, 360);
	}

	renderPosLeft.x += ((isLeft) ? (-_attackMove.x) : 0);
	renderPosLeft.y += ((isLeft && angle < 180) ? (-_attackMove.y) : 0);
	renderPosLeft.y += ((isLeft && angle >= 180) ? (_attackMove.y) : 0);
	renderPosRight.x += ((isLeft) ? 0 : (_attackMove.x));
	renderPosRight.y += ((!isLeft && angle < 90) ? 0 : (_attackMove.y));
	renderPosRight.y += ((!isLeft && angle >= 270) ? 0 : (-_attackMove.y));

	//_img->setScale(4);
	//_img->setAngle(angle);
	//_img->setAnglePos(Vector2(_img->getWidth() * 0.3f, _img->getHeight() * 0.5f));
	//_img->render(renderPos, isLeft);
	_leftHand = rectMakePivot(renderPosLeft, Vector2(_handSize), PIVOT::CENTER);
	_rightHand = rectMakePivot(renderPosRight, Vector2(_handSize), PIVOT::CENTER);
	D2D_RENDERER->drawRectangle(_leftHand, D2DRenderer::DefaultBrush::Black, 4.f);
	D2D_RENDERER->drawRectangle(_rightHand, D2DRenderer::DefaultBrush::Black, 4.f);
	D2D_RENDERER->fillRectangle(_leftHand, 251, 206, 177, 1);
	D2D_RENDERER->fillRectangle(_rightHand, 251, 206, 177, 1);
}

void Punch::displayInfo()
{
	//장비를 착용하지 않음
}

void Punch::attack(Vector2 const position, float const angle)
{
	if (_currAttackDelay > 0) return;

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
