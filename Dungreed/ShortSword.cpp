#include "stdafx.h"
#include "ShortSword.h"

void ShortSword::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("ShortSword");
	_price = 600;

	_itemName = L"���ҵ�";
	
	_displayText = L"\"������ �ֵθ��� ���� ��\"";
	_itemCode = 0x01102; // �Ѽ� �Ϲ� 
	// �⺻ �����ɼ�
	_addStat.minDamage = 8;
	_addStat.maxDamage = 10;
	_addStat.attackSpeed = 0.6;
	_handSize = Vector2(5, 5);

	// private ���� ����
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_angleOffset = 15;

}


void ShortSword::update(Player* player, float const elapsedTime)
{

	if (_currAttackDelay == 0) return;

	if (FLOAT_EQUAL(_currAttackDelay, _addStat.attackSpeed))
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
	float ratio = elapsedTime / (_addStat.attackSpeed * 0.15);
	if (_reverseMove)
	{
	}
	else
	{	
		if (_currAttackDelay <= _addStat.attackSpeed * 0.8)
		{
			_reverseMove = true;
			_drawEffect = true;
		}
	}

	// ���� ������ ���
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void ShortSword::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	if (_oneAttack)
	{	
		// �÷��̾� ����
		originPos.x += ((isLeft) ? -20 : 20); 
	// �����κ��� ���콺 ���ӱ����� ����
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x - pos.x))) * (180 / PI);
		float degreeOffsetangle = degree + 90;
		if (degree >360)
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

			renderPosWeapon.x -= 22 -  ( cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
			renderPosWeapon.y += 20 + (sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
			renderPosHand.x -=    (-cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
			renderPosHand.y +=  20 +  ( sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
		}
		else
		{
			renderPosWeapon.x += 22 + (-cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
			renderPosWeapon.y += 20 +  (-sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
			renderPosHand.x += -cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4);
			renderPosHand.y += 20 +  (-sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
		}
		float renderDegree = degreeOffsetangle;

		if (isLeft) // ������ ���� ����
		{
			renderDegree =360 - degreeOffsetangle;
			if (renderDegree < 0) renderDegree += 360;
		}

		renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		 // ������ x��ǥ
		renderPosWeapon.y += ((degreeOffsetangle >= 180) ? (_attackMove.y) : (-_attackMove.y)); // ������ y��ǥ
		renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			 // ���� x��ǥ
		renderPosHand.y += ((degreeOffsetangle >=180) ? (_attackMove.y) : (-_attackMove.y));	 // ���� y��ǥ

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
		Vector2 last = renderPosHand;
	
		if (isLeft) // ������ ���� ����
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(last));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(last)) ; // ���� ��Ʈ�� �׸���
		}
		else
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (renderDegree + _angleOffset), CAMERA->getRelativeV2(last));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (renderDegree + _angleOffset), CAMERA->getRelativeV2(last)); // ���� ��Ʈ�� �׸���
		}
		if (_drawEffect) // ����Ʈ�� �׸���
		{
			_drawEffect = false;
			Vector2 effectPos = pos; // ���� ��ġ�κ���
			float length = _img->getWidth() * 4 * 1.3; // ���� ���̸�ŭ
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_SWING", effectPos, Vector2(120, 180), degree);
		}
	}




}

void ShortSword::frontRender(Player* player)
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
	if (!_oneAttack)
	{
		// �÷��̾� ����
		originPos.x += ((isLeft) ? -40 : 20);
		// �����κ��� ���콺 ���ӱ����� ����
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x)) * (180 / PI) ;
		float degreeOffsetangle = degree + 90 ;
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

			renderPosWeapon.x +=	5+	  (-cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4))   ;
			renderPosWeapon.y +=    5+    (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4))   ;
			renderPosHand.x   +=   52+    (-cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4))-23 ;
			renderPosHand.y   +=    5+    (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4))   ;
		}
		else
		{
			renderPosWeapon.x -=  -5 +  (cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4) );
			renderPosWeapon.y +=   25+   (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
			renderPosHand.x -=     42 + (cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4)) -23 ;
			renderPosHand.y +=     25+  (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
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
			EFFECT_MANAGER->play("EFFECT_SWING", effectPos, Vector2(120, 180), degree);
		}
	}
}


void ShortSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	CAMERA->pushShakeEvent(10, 0.1f);
	
	_reverseMove = false;	
	_currAttackDelay = _addStat.attackSpeed;
	//==========================================================================

	Vector2 originPos = player->getPosition();
	originPos.x += ((player->getDirection() == DIRECTION::LEFT) ? -15 : 15); // �ٶ󺸴� ������ ���
	originPos.y += 10;
	float attackRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x));
	if (attackRadian < 0)
	{
		attackRadian += PI2;
	}

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // ������ �ڵ�� ���� �ð��� Concat�Ͽ� ���� ���̵� ���ϱ� ���� ���� �ڵ带 ������

	FloatCircle* attackCircle = new FloatCircle;
	attackCircle->origin = originPos;
	attackCircle->size = 120;
	attackCircle->startRadian = attackRadian - PI * 0.28;
	attackCircle->endRadian = attackRadian + PI * 0.28;


	SOUND_MANAGER->stop("SOUND_generalAttack");
	SOUND_MANAGER->play("SOUND_generalAttack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));


	_attackDebug = FloatCircle(originPos, 120, attackRadian - PI * 0.28, attackRadian + PI * 0.28); // forDEBUG

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = _addStat.minDamage;
	attackInfo->maxDamage = _addStat.maxDamage;
	attackInfo->knockBack = 15;
	player->attack(attackCircle, attackInfo);
	delete attackCircle;
	delete attackInfo;
}



void ShortSword::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}
