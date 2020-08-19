#include "stdafx.h"
#include "FluteGreatSword.h"

void FluteGreatSword::init()
{
	_iconImg = IMAGE_MANAGER->findImage("FluteGreatSword");
	_img = IMAGE_MANAGER->findImage("FluteGreatSword");
	_price = 3600;
	_itemName = L"�����Į";
	_displayText = L"\"�ֹ��� �ʼ�ǰ�� �ٽ� ���ƿԽ��ϴ�.\"";
	_itemCode = 0x02201; //��� ��� 01;
	// �⺻ �����ɼ�
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);

	_addStat.minDamage = 5;
	_addStat.maxDamage = 8;
	_addStat.attackSpeed = 0.5;
	//_addStat.attackSpeed = 5.56;
	//�����ɼ�
	
	// private ���� ����
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_angleOffset = 0;
	_width = _img->getWidth();
	_height = _img->getHeight();
}

void FluteGreatSword::release()
{

}

void FluteGreatSword::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (1 / _addStat.attackSpeed / 2);

	if (_oneAttack)
	{
		_angleOffset = max(0, (_angleOffset)-(elapsedTime * ratio));
		if (_angleOffset == -180)
		{
			_oneAttack = false;
		}
	}
	else
	{
		if (_angleOffset < 0)
		{
			_angleOffset = min(0, (_angleOffset)+(elapsedTime * ratio));
		}
	}

	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void FluteGreatSword::backRender(Player* player)
{

}

void FluteGreatSword::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	// ȸ���� ����
	originPos.x += ((isLeft) ? -20 : 20); // �ٶ󺸴� ������ ���
	originPos.y += 0;
	pos.x += ((isLeft) ? 0 : 0);
	//pos.y += 20;
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
	Vector2 renderPosHand = pos;
	// ���� ��ġ
	Vector2 renderPosWeapon = originPos;


	renderPosHand.x += 0;// (isLeft) ? (-cosf(handDegree * (PI / 180)) * width * 0.15f * 4) : (-cosf(handDegree* (PI / 180)) * width * 0.15f * 4);
	renderPosHand.y += (-sinf(weaponDegree * (PI / 180)) * 0.90 * 4);
	//renderPosHand.y += (isLeft) ? (+20) : (-20)
	//renderPosHand.y += (isLeft) ? (20) : (-20);
//renderPosWeapon.y +=  (-sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4);



	if (_oneAttack)
	{
		_img->setScale(4); // �̹��� ũ�� 

		_img->setAngle(weaponDegree + _angleOffset);//*+ _angleOffset*/); // �̹��� ���� 
		_img->setAnglePos(Vector2(0.35f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���
	}
	else
	{

		_img->setScale(4); // �̹��� ũ�� 
		_img->setAngle(weaponDegree + _angleOffset);//*+ _angleOffset*/); // �̹��� ���� 
		_img->setAnglePos(Vector2(0.35f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���
	}




	//FloatRect testHand = FloatRect(renderPosHand, _handSize, PIVOT::CENTER);
	//D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(testHand), 0, 0,0, 1, (0), CAMERA->getRelativeV2(originPos));
	if (isLeft)
	{
		renderPosHand.x += _width * 0.03f * 4;
		renderPosHand.x += cosf(handDegree * (PI / 180)) * _width * 0.03f * 4;
		renderPosHand.y += -20;
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, -(weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, -(weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos)); // ���� ��Ʈ�� �׸���
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x -= 20;
		renderPosHand2.x += cosf(handDegree * (PI / 180)) * _width * 0.03f * 4;// width * 0.01f * 4;

		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, -(weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, -(weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos)); // ���� ��Ʈ�� �׸���

	}
	else
	{

		renderPosHand.x += _width * 0.03f * 4;
		renderPosHand.x += -cosf(handDegree * (PI / 180)) * _width * 0.03f * 4;
		renderPosHand.y += -20;
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos)); // ���� ��Ʈ�� �׸���
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x -= 20;
		renderPosHand2.x += -cosf(handDegree * (PI / 180)) * _width * 0.03f * 4;// width * 0.01f * 4;

		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos)); // ���� ��Ʈ�� �׸���

	}


	if (_drawEffect) // ����Ʈ�� �׸���
	{
		Vector2 effectPos = originPos; // ȸ������ ��ġ�κ���
		float length = _width * 4 * 0.5; // ���� ���̸�ŭ
		_drawEffect = false;
		bool isLeft = (player->getDirection() == DIRECTION::LEFT);
		if (!isLeft)
		{
			//degree = degree + 180;
			effectPos.x += cosf(degree * (PI / 180)) * length;
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

void FluteGreatSword::displayInfo()
{
}

void FluteGreatSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	_oneAttack = true;
	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x));
	_drawEffect = true;
	_currAttackDelay = _addStat.attackSpeed;
}

void FluteGreatSword::attack(FloatRect* rect, AttackInfo* info)
{
}

void FluteGreatSword::attack(FloatCircle* circle, AttackInfo* info)
{
}

void FluteGreatSword::attack(Projectile* projectile, AttackInfo* info)
{
}

void FluteGreatSword::getHit(Vector2 const position)
{
}

void FluteGreatSword::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}