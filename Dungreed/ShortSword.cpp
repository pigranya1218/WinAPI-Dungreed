#include "stdafx.h"
#include "ShortSword.h"

void ShortSword::init()
{

	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("ShortSword");
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
	_angleOffset = 105;
}

void ShortSword::release()
{
}

void ShortSword::update(Player* player, float const elapsedTime)
{

	if (_currAttackDelay == 0) return;

	if (FLOAT_EQUAL(_currAttackDelay, _baseAttackDelay))
	{
		

		if (_oneAttack)
		{
			_angleOffset += 155;
			_oneAttack = false;

		}
		else 
		{
			_angleOffset -= 155;
			_oneAttack = true;
		}
		


	}
	

	// ���� ������ ���
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void ShortSword::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	if (_oneAttack)
	{
		originPos.x += ((isLeft) ? -20 : 20);
		originPos.y += 0;
	
	
	float degree = atan2f(-(_ptMouse.y - originPos.y), (_ptMouse.x - originPos.x)) * (180 / PI) + 360;
	// �����κ��� ���콺 ���ӱ����� ����
	if (degree > 360)
	{
		degree -= 360;
	} 
	Vector2 renderPosHand = originPos;
	
	renderPosHand.x += cosf(degree * (PI / 180)) * (_img->getWidth() * 0.2f * 4);
	renderPosHand.y += -sinf(degree * (PI / 180)) * (_img->getWidth() * 0.2f * 4);

	// ���⸦ ����ִ� ���� ��ġ
	Vector2 renderPosWeapon = renderPosHand;
	renderPosWeapon.x -= ((isLeft) ? (_img->getWidth() * 0.4f * 4) : -(_img->getWidth() * 0.4f * 4));
	
	// renderPosWeapon.x -= ((isLeft) ? (35) : (-35));
	
	float renderDegree = degree;
	if (isLeft) // ������ ���� ����
	{
		renderDegree = 180 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}
	renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));
	renderPosWeapon.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));
	renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));
	renderPosHand.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));

	_img->setScale(4);
	_img->setAngle(renderDegree + _angleOffset);
	
	_img->setAnglePos(Vector2(0.1f * _img->getWidth(), 0.5f * _img->getHeight()));
	_img->render(renderPosWeapon, isLeft);

	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);

	D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, degree, renderPosHand);
	D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, degree, renderPosHand);

	if (_drawEffect) // ����Ʈ�� �׸���
	{
		_drawEffect = false;
		Vector2 effectPos = renderPosHand; // ���� ��ġ�κ���
		float length = _img->getWidth() * 4 * 0.7; // ���� ���̸�ŭ
		effectPos.x += cosf(degree * (PI / 180)) * length;
		effectPos.y += -sinf(degree * (PI / 180)) * length;	
		EFFECT_MANAGER->play("EFFECT_SWING", effectPos, Vector2(35, 35), degree);
	}
	}
}

void ShortSword::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	if (isLeft)
	{
		Vector2 renderPos = Vector2(originPos.x + 25, originPos.y + 20);

		_hand = rectMakePivot(renderPos, _handSize, PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1, 6.f);
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1);
	}
	else
	{
		Vector2 renderPos = Vector2(originPos.x - 25, originPos.y + 20);

		_hand = rectMakePivot(renderPos, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1, 6.f);
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1);
	}
	
		if (!_oneAttack)
		{
			originPos.x += ((isLeft) ? -2 : 2);
			originPos.y += 20;


			float degree = atan2f(-(_ptMouse.y - originPos.y), (_ptMouse.x - originPos.x)) * (180 / PI) + 360;
			// �����κ��� ���콺 ���ӱ����� ����
			if (degree > 360)
			{
				degree -= 360;
			}
			Vector2 renderPosHand = originPos;

			renderPosHand.x += cosf(degree * (PI / 180)) * (_img->getWidth() * 0.2f * 4);
			renderPosHand.y += -sinf(degree * (PI / 180)) * (_img->getWidth() * 0.2f * 4);

			// ���⸦ ����ִ� ���� ��ġ
			Vector2 renderPosWeapon = renderPosHand;
			renderPosWeapon.x -= ((isLeft) ? (_img->getWidth() * 0.4f * 4) : -(_img->getWidth() * 0.4f * 4));

			// renderPosWeapon.x -= ((isLeft) ? (35) : (-35));

			float renderDegree = degree;
			if (isLeft) // ������ ���� ����
			{
				renderDegree = 180 - degree;
				if (renderDegree < 0) renderDegree += 360;
			}
			renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));
			renderPosWeapon.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));
			renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));
			renderPosHand.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));

			_img->setScale(4);
			_img->setAngle(renderDegree + _angleOffset);

			_img->setAnglePos(Vector2(0.1f * _img->getWidth(), 0.5f * _img->getHeight()));
			
			_img->render(renderPosWeapon, isLeft);

			_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);

			Vector2 anglePosHand = renderPosWeapon;
			anglePosHand.x -= 0.4f * _img->getWidth() * 4;
			Vector2 lastAnglePosHand = anglePosHand;
			D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, degree + _angleOffset, lastAnglePosHand);
			D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, degree + _angleOffset, lastAnglePosHand);
			if (_drawEffect) // ����Ʈ�� �׸���
			{
				_drawEffect = false;
				Vector2 effectPos = renderPosHand; // ���� ��ġ�κ���
				float length = _img->getWidth() * 4 * 0.7; // ���� ���̸�ŭ
				effectPos.x += cosf(degree * (PI / 180)) * length;
				effectPos.y += -sinf(degree * (PI / 180)) * length;
				EFFECT_MANAGER->play("EFFECT_SWING", effectPos, Vector2(35, 35), degree);
			}
		}
}

void ShortSword::displayInfo()
{
}

void ShortSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? -(_img->getWidth() * 0.15f * 4) : (_img->getWidth() * 0.15f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 20; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����
	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(_ptMouse.y - renderPosHand.y), (_ptMouse.x - renderPosHand.x)) + PI2;
	if (angle > PI2)
	{
		angle -= PI2;
	}

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _baseAttackDelay;
}

void ShortSword::attack(FloatRect* rect, tagAttackInfo* info)
{
}

void ShortSword::attack(FloatCircle* circle, tagAttackInfo* info)
{
}

void ShortSword::attack(Projectile* projectile, tagAttackInfo* info)
{
}

void ShortSword::getHit(Vector2 const position)
{
}

PlayerStat ShortSword::equip()
{
	return PlayerStat();
}
