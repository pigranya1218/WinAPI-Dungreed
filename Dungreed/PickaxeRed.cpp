#include "stdafx.h"
#include "PickaxeRed.h"

void PickaxeRed::init()
{
	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	_iconImg = _img = IMAGE_MANAGER->findImage("PickaxeRed");
	_price = 600;

	// �⺻ �����ɼ�
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);


	// private ���� ����
	_attackMove = Vector2(0, 0);
	_minDamage = 7;
	_maxDamage = 10;
	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_angleOffset = 15;

}

void PickaxeRed::release()
{

}

void PickaxeRed::update(Player* player, float const elapsedTime)
{

	if (_currAttackDelay == 0) return;

	if (FLOAT_EQUAL(_currAttackDelay, _baseAttackDelay))
	{

	}
	float ratio = elapsedTime / (_baseAttackDelay * 0.15);
	if (_reverseMove)
	{
		//_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 40 * ratio));
		//_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 40 * ratio));

	}
	else
	{
		//_attackMove.x = min(abs(cosf(_attackAngle) * 40), _attackMove.x + abs(cosf(_attackAngle) * 40 * ratio));
		//_attackMove.y = min(abs(-sinf(_attackAngle) * 40), _attackMove.y + abs((-sinf(_attackAngle)) * 40 * ratio));

		if (_currAttackDelay <= _baseAttackDelay * 0.8)
		{
			_reverseMove = true;
			_drawEffect = true;
		}
	}

	// ���� ������ ���
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void PickaxeRed::backRender(Player* player)
{

}

void PickaxeRed::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	if (isLeft)
	{
		Vector2 renderPos = Vector2(originPos.x + 25, originPos.y + 20);

		_hand = rectMakePivot(renderPos, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1, 2.f);
	}
	else
	{
		Vector2 renderPos = Vector2(originPos.x - 25, originPos.y + 20);

		_hand = rectMakePivot(renderPos, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1, 2.f);
	}
	
		// �÷��̾� ����
		originPos.x += ((isLeft) ? -40 : 20);



		// �����κ��� ���콺 ���ӱ����� ����

		//float degree = atan2f(-(_ptMouse.y - Pos.y), (_ptMouse.x - Pos.x)) * (180 / PI) + 90;
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x)) * (180 / PI);
		float degreeOffsetangle = degree + 90;


		if (degree > 360)
		{
			degree -= 360;
		}
		if (degreeOffsetangle > 360)
		{
			degreeOffsetangle -= 360;
		}
		// �� �� ���� 
		Vector2 renderPosHand = originPos;
		Vector2 renderPosWeapon = originPos;

		if (isLeft) // ������ ���� ����
		{

			renderPosWeapon.x += 5 + (-cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4));
			renderPosWeapon.y += 5 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
			renderPosHand.x += 52 + (-cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4)) - 23;
			renderPosHand.y += 5 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
		}
		else
		{
			renderPosWeapon.x -= -5 + (cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4));
			renderPosWeapon.y += 25 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
			renderPosHand.x -= 42 + (cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4)) - 23;
			renderPosHand.y += 25 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
		}
		float renderDegree = degreeOffsetangle;

		if (isLeft) // ������ ���� ����
		{
			renderDegree = 360 - degreeOffsetangle;
			if (renderDegree < 0) renderDegree += 360;
		}

		renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		 // ������ x��ǥ
		renderPosWeapon.y += ((degreeOffsetangle >= 180) ? (_attackMove.y) : (-_attackMove.y)); // ������ y��ǥ
		renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			 // ���� x��ǥ
		renderPosHand.y += ((degreeOffsetangle >= 180) ? (_attackMove.y) : (-_attackMove.y));	 // ���� y��ǥ
		_img->setScale(4); // �̹��� ũ�� 
		_img->setAngle(renderDegree + _angleOffset); // �̹��� ���� 
		if (isLeft) // ������ ���� ����
		{
			_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight())); // �̹��� ȸ����ų ����
		}
		else
		{
			_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight())); // �̹��� ȸ����ų ����

		}
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft); // �׸���

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);

		if (isLeft) // ������ ���� ����
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand)); // ���� ��Ʈ�� �׸���
		}
		else
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand)); // ���� ��Ʈ�� �׸���
		}
		if (_drawEffect) // ����Ʈ�� �׸���
		{
			_drawEffect = false;
			Vector2 effectPos = pos; // ���� ��ġ�κ���
			float length = _img->getWidth() * 4 * 1.3; // ���� ���̸�ŭ
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_REDPICKAXESWING", effectPos, Vector2(120, 180), degree);
		}
	
}

void PickaxeRed::displayInfo()
{
}

void PickaxeRed::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;

	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x));
	_reverseMove = false;
	_currAttackDelay = _baseAttackDelay;
}

void PickaxeRed::attack(FloatRect* rect, AttackInfo* info)
{
}

void PickaxeRed::attack(FloatCircle* circle, AttackInfo* info)
{
}

void PickaxeRed::attack(Projectile* projectile, AttackInfo* info)
{
}

void PickaxeRed::getHit(Vector2 const position)
{
}

PlayerStat PickaxeRed::equip()
{
	return PlayerStat();
}