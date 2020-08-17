#include "stdafx.h"
#include "PickaxeRed.h"

void PickaxeRed::init()
{
	_iconImg = IMAGE_MANAGER->findImage("PickaxeRedIcon");
		_img = IMAGE_MANAGER->findImage("PickaxeRed");
	_price = 600;
	_itemName = L"���� ���";
	_displayText = L"\"���� ���� �Ⱦ��ϴ� ���� ������ ���\"";
	_itemCode = 0x02300; //��� ���� 00;
	// �⺻ �����ɼ�
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);

	_addStat.minDamage = 5;
	_addStat.maxDamage = 15;
	_addStat.attackSpeed = 10;
	//_addStat.attackSpeed = 5.56;
	//�����ɼ�
	_addStat.defense = -30;
	_addStat.power = -30;
	// private ���� ����
	_attackMove = Vector2(0, 0);
	_baseAttackDelay = 0.1;
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_angleOffset = 0;
	width =  _img->getWidth();
	height =  _img->getHeight();
}

void PickaxeRed::release()
{

}

void PickaxeRed::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (1 / _addStat.attackSpeed / 2);

	if (_oneAttack)
	{	
		_angleOffset = max(-180, (_angleOffset) - (elapsedTime * ratio));
		if (_angleOffset == -180)
		{
			_oneAttack = false;
		}
	}
	else
	{
		if (_angleOffset < 0)
		{
			_angleOffset = min(0, (_angleOffset) + (elapsedTime * ratio));
		}
	}
	
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
	
	// ȸ���� ����
	originPos.x += ((isLeft) ? -20 : 20); // �ٶ󺸴� ������ ���
	originPos.y += 0;
	pos.x += ((isLeft) ? 0 : -40);
	pos.y += 20;
	// ȸ�������κ��� ���콺������ ������
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

	float handDegree = degree;// +((isLeft) ? -180 : 180);

	// �¿� ��Ī�� ���� ���
	float weaponDegree = handDegree;
	weaponDegree += ((isLeft) ? -180 : 180);
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;

		}
	
	//renderPosHand.x += (width * 0.1 * 4);
	// ���� ��ġ 
	Vector2 renderPosHand = originPos;
	// ���� ��ġ
	Vector2 renderPosWeapon = originPos;
	 
		
		renderPosHand.x += (isLeft) ? 40+ ( -cosf(handDegree * (PI / 180)) * width * 0.15f*4) : 80 - ( -cosf(handDegree * (PI / 180)) * width * 0.15f*4);
		renderPosHand.y += 20+ (-sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4);
		//renderPosHand.y += (isLeft) ? (+20) : (-20);
		//renderPosHand.y += (isLeft) ? (20) : (-20);
	//renderPosWeapon.y +=  (-sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4);
	
	

		if (_oneAttack)
		{
			_img->setScale(4); // �̹��� ũ�� 
			
			_img->setAngle(weaponDegree + _angleOffset);//*+ _angleOffset*/); // �̹��� ���� 
			_img->setAnglePos(Vector2(0.35f * width, 0.5f * height)); // �̹��� ȸ����ų ����
			_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���
		}
		else
		{

			_img->setScale(4); // �̹��� ũ�� 
			_img->setAngle(weaponDegree + _angleOffset);//*+ _angleOffset*/); // �̹��� ���� 
			_img->setAnglePos(Vector2(0.35f * width, 0.5f * height)); // �̹��� ȸ����ų ����
			_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���
		}
		


	
	FloatRect testHand = FloatRect(renderPosHand, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(testHand), 0, 0,0, 1, (0), CAMERA->getRelativeV2(originPos));


	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
	Vector2 renderPosHand2 = renderPosHand;
	renderPosHand2.x += width * 0.06f * 4;
	FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���

	if (_drawEffect) // ����Ʈ�� �׸���
	{
		Vector2 effectPos = originPos; // ȸ������ ��ġ�κ���
		float length = width * 4 * 0.5; // ���� ���̸�ŭ
		_drawEffect = false;
		bool isLeft = (player->getDirection() == DIRECTION::LEFT);
		if (!isLeft)
		{
			//degree = degree + 180;
			effectPos.x +=  cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_REDPICKAXESWING", effectPos, Vector2(100, 200), -degree + 180, !isLeft);
		}
		else
		{

		effectPos.x += cosf(degree * (PI / 180)) * length;
		effectPos.y += -sinf(degree * (PI / 180)) * length;
		EFFECT_MANAGER->play("EFFECT_REDPICKAXESWING", effectPos, Vector2(100, 200), degree, !isLeft);
		}
		
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
	_oneAttack = true;
	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x));
	_drawEffect = true;
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