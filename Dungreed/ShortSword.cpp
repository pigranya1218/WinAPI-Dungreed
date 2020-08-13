#include "stdafx.h"
#include "ShortSword.h"

void ShortSword::init()
{

	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	_iconImg = _img = IMAGE_MANAGER->findImage("ShortSword");
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
			_angleOffset += 180;
			_oneAttack = false;

		}
		else 
		{
			_angleOffset -= 180;
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
	Vector2 Pos = player->getPosition();
	if (_oneAttack)
	{	
		// �÷��̾� ����
		originPos.x += ((isLeft) ? -20 : 20); 
		
		
	
	// �����κ��� ���콺 ���ӱ����� ����
		
			float degree = atan2f(-(_ptMouse.y - Pos.y), (_ptMouse.x - Pos.x)) * (180 / PI) +90;
		
		
	if (degree >360)
	{
		degree -= 360;
	} 
	// �� �� ���� 
	Vector2 renderPosHand = originPos;
	Vector2 renderPosWeapon = originPos;

	if (isLeft) // ������ ���� ����
	{

		renderPosWeapon.x -= 22 -  ( cosf(degree * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
		renderPosWeapon.y += 20 + (sinf(degree * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
		renderPosHand.x -=    (-cosf(degree * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
		renderPosHand.y +=  20 +  ( sinf(degree * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
	}
	else
	{
		renderPosWeapon.x += 22 + (-cosf(degree * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
		renderPosWeapon.y += 20 +  (-sinf(degree * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
		renderPosHand.x += -cosf(degree * (PI / 180))*-(_img->getWidth() * 0.4f * 4);
		renderPosHand.y += 20 +  (-sinf(degree * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
	}
	float renderDegree = degree;

	if (isLeft) // ������ ���� ����
	{
		renderDegree =360 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}

	renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		 // ������ x��ǥ
	renderPosWeapon.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y)); // ������ y��ǥ
	renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			 // ���� x��ǥ
	renderPosHand.y += ((degree >=180) ? (_attackMove.y) : (-_attackMove.y));	 // ���� y��ǥ

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
	_img->render(renderPosWeapon, isLeft); // �׸���
	
	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
	Vector2 last = renderPosHand;
	if (isLeft) // ������ ���� ����
	{
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, -(renderDegree + _angleOffset), last) ; // ���� ��Ʈ�� �׸���
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, -(renderDegree + _angleOffset), last);
	}
	else
	{
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, (renderDegree + _angleOffset), last); // ���� ��Ʈ�� �׸���
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, (renderDegree + _angleOffset), last);
	}
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
	Vector2 Pos = player->getPosition();
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
		// �÷��̾� ����
		originPos.x += ((isLeft) ? -40 : 20);



		// �����κ��� ���콺 ���ӱ����� ����

		float degree = atan2f(-(_ptMouse.y - Pos.y), (_ptMouse.x - Pos.x)) * (180 / PI) + 90;


		if (degree > 360)
		{
			degree -= 360;
		}
		// �� �� ���� 
		Vector2 renderPosHand = originPos;
		Vector2 renderPosWeapon = originPos;

		if (isLeft) // ������ ���� ����
		{

			renderPosWeapon.x +=	5+	  (-cosf(degree * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4))   ;
			renderPosWeapon.y +=    5+    (-sinf(degree * (PI / 180)) *  (_img->getHeight() * 0.4f * 4))   ;
			renderPosHand.x   +=   52+    (-cosf(degree * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4))-23 ;
			renderPosHand.y   +=    5+    (-sinf(degree * (PI / 180)) *  (_img->getHeight() * 0.4f * 4))   ;
		}
		else
		{
			renderPosWeapon.x -=   5+  (cosf(degree * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4));
			renderPosWeapon.y +=   5+   (-sinf(degree * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
			renderPosHand.x -=     52 + (cosf(degree * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4)) -23 ;
			renderPosHand.y +=     5+  (-sinf(degree * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
		}
		float renderDegree = degree;

		if (isLeft) // ������ ���� ����
		{
			renderDegree = 360 - degree;
			if (renderDegree < 0) renderDegree += 360;
		}

		renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		 // ������ x��ǥ
		renderPosWeapon.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y)); // ������ y��ǥ
		renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			 // ���� x��ǥ
		renderPosHand.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));	 // ���� y��ǥ

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
		_img->render(renderPosWeapon, isLeft); // �׸���

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		Vector2 last = renderPosHand;
		if (isLeft) // ������ ���� ����
		{
			D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, -(renderDegree + _angleOffset), last); // ���� ��Ʈ�� �׸���
			D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, -(renderDegree + _angleOffset), last);
		}
		else
		{
			D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, (renderDegree + _angleOffset), last); // ���� ��Ʈ�� �׸���
			D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, (renderDegree + _angleOffset), last);
		}
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

void ShortSword::attack(FloatRect* rect, AttackInfo* info)
{
}

void ShortSword::attack(FloatCircle* circle, AttackInfo* info)
{
}

void ShortSword::attack(Projectile* projectile, AttackInfo* info)
{
}

void ShortSword::getHit(Vector2 const position)
{
}

PlayerStat ShortSword::equip()
{
	return PlayerStat();
}
