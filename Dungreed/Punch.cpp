#include "stdafx.h"
#include "Punch.h"

void Punch::init()
{
	_type = ITEM_TYPE::WEAPON_ONE_HAND;	//��������� ���� ����
	_rank = ITEM_RANK::NORMAL;
	//�ָ� �̹���
	//���� ����
	_price = 0;
	//���� �ɼ� ����
	
	_attackMove = Vector2(0, 0);
	_minDamage = 1;
	_maxDamage = 4;
	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_reverseMove = false;

	//�� ǥ���� ��Ʈ
	_handSize = Vector2(5, 5);

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

	// ���� ������ ���
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void Punch::backRender(Player* player)
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
		renderPosLeft.y += ((angle >= 180)?(_attackMove.y):(-_attackMove.y));

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

void Punch::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	if (isLeft)
	{
		Vector2 renderPosRight = Vector2(pos.x + 20, pos.y + 18);
		_rightHand = rectMakePivot(renderPosRight, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_rightHand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rightHand), 40, 36, 58, 1, 2.f);
	}
	else
	{
		Vector2 renderPosLeft = Vector2(pos.x - 20, pos.y + 18);
		_leftHand = rectMakePivot(renderPosLeft, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_leftHand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_leftHand), 40, 36, 58, 1, 2.f);
	}
}

void Punch::displayInfo()
{
	//��� �������� ����
}

void Punch::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos; // ���� ��ġ
	renderPosHand.x += ((isLeft) ? (-20) : (20)); 
	renderPosHand.y += 20; 
	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angle > PI2)
	{
		angle -= PI2;
	}

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _baseAttackDelay;
}

void Punch::attack(FloatRect * rect, AttackInfo * info)
{
}

void Punch::attack(FloatCircle * circle, AttackInfo * info)
{
}

void Punch::attack(Projectile * projectile, AttackInfo * info)
{
}

void Punch::getHit(Vector2 const position)
{
}
