#include "stdafx.h"
#include "ShortSpear.h"

void ShortSpear::init()
{
	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("ShortSpear");
	_price = 600;

	// �⺻ �����ɼ�
	_addStat.dashDamage = 20;

	_handSize = Vector2(7, 7);


	// private ���� ����
	_attackMove = Vector2(0, 0);
	_minDamage = 7;
	_maxDamage = 10;
	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_reverseMove = false;
}

void ShortSpear::release()
{
}

void ShortSpear::update(float const elapsedTime)
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
		}
	}

	// ���� ������ ���
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void ShortSpear::backRender(Vector2 pos, float angle)
{
	bool isLeft = false;
	if (angle >= 90 && angle <= 270) // ������ ���� ����
	{
		isLeft = true;
	}
	if (isLeft)
	{
		Vector2 renderPos = Vector2(pos.x - 22, pos.y + 20);

		_hand = rectMakePivot(renderPos, _handSize, PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_hand, D2DRenderer::DefaultBrush::Black, 4.f);
		D2D_RENDERER->fillRectangle(_hand, 251, 206, 177, 1);
	}
	else
	{
		Vector2 renderPos = Vector2(pos.x + 22, pos.y + 20);

		_hand = rectMakePivot(renderPos, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_hand, D2DRenderer::DefaultBrush::Black, 4.f);
		D2D_RENDERER->fillRectangle(_hand, 251, 206, 177, 1);
	}
}

void ShortSpear::frontRender(Vector2 pos, float angle)
{
	Vector2 renderPos = pos;
	float renderAngle = angle;
	bool isLeft = false;
	if (angle >= 90 && angle <= 270) // ������ ���� ����
	{
		isLeft = true;
		renderAngle = fmod((180 - angle) + 360, 360);
	}

	renderPos.x += ((isLeft)?(-10 - _attackMove.x):(10 + _attackMove.x));
	renderPos.y += 15 + ((renderAngle >= 180) ? (_attackMove.y) : (-_attackMove.y));

	_img->setScale(4);
	_img->setAngle(renderAngle);
	_img->setAnglePos(Vector2(0.3f * _img->getWidth(), 0.5f * _img->getHeight()));
	_img->render(renderPos, isLeft);

	Vector2 renderPosHand = Vector2(renderPos.x, renderPos.y);
	if (isLeft)
	{
		renderPosHand.x += 25;
	}
	else
	{
		renderPosHand.x -= 25;
	}
	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);

	D2D_RENDERER->drawRectangle(_hand, D2DRenderer::DefaultBrush::Black, 4.f, angle, renderPosHand);
	D2D_RENDERER->fillRectangle(_hand, 251, 206, 177, 1, angle, renderPosHand);
}

void ShortSpear::displayInfo()
{
}

void ShortSpear::attack(Vector2 const position, float const angle)
{
	if (_currAttackDelay > 0) return;

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _baseAttackDelay;
}

void ShortSpear::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void ShortSpear::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void ShortSpear::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void ShortSpear::getHit(Vector2 const position)
{
}

PlayerStat ShortSpear::equip()
{
	return PlayerStat();
}
