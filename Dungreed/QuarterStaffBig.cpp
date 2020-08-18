#include "stdafx.h"
#include "QuarterStaffBig.h"
void QuarterStaffBig::init()
{
	_iconImg = IMAGE_MANAGER->findImage("QuarterStaffBig");
	_img = IMAGE_MANAGER->findImage("QuarterStaffBig");
	_price = 600;
	_itemName = L"�ڴ޳��� �ִܺ�'";
	_displayText = L"\"������ ������ �ֿ��ϴ� �ִܺ�. ������ �ſ� ������.\"";
	_itemCode = 0x02201; //��� ���� 01;
	// �⺻ �����ɼ�
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);

	_addStat.minDamage = 9;
	_addStat.maxDamage = 11;
	_addStat.defense = 5;
	_addStat.attackSpeed = 5.5;
	//�����ɼ�

	// private ���� ����
	_attackMove = Vector2(0, 0);
	_baseAttackDelay = 0.1;
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = false;
	_attackAngle = 0;
	_angleOffset = 0;
	_width = _img->getWidth();
	_height = _img->getHeight();
}

void QuarterStaffBig::release()
{

}   

void QuarterStaffBig::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (1 / _addStat.attackSpeed /2);
	if (_oneAttack)
	{
		_angleOffset = max(-360, ((_angleOffset)  - (elapsedTime * ratio)));
		if (_angleOffset == -360)
		{
			_angleOffset = 0;
			_oneAttack = false;
		}
		
	}
	else
	{

	}


	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void QuarterStaffBig::backRender(Player* player)
{

}

void QuarterStaffBig::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	// ȸ���� ����
	originPos.x += ((isLeft) ? 0 :0 ); // �ٶ󺸴� ������ ���
	originPos.y += 0;

	// ȸ�������κ��� ���콺������ ������
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

	float handDegree = degree;

	// �¿� ��Ī�� ���� ���
	float weaponDegree = handDegree;
	
	if (isLeft)
	{
		weaponDegree = 180 - weaponDegree;
	}
	// ���� ��ġ 
	Vector2 renderPosHand = originPos;
	renderPosHand.x += 0;
	//renderPosHand.x += (_width * 0.1 * 4);
	
	renderPosHand.y +=  -sinf(weaponDegree * (PI / 180)* 0.91 * 4) - 10;

	// ���� ��ġ
	Vector2 renderPosWeapon = originPos;
	//(isLeft) ? (renderPosWeapon.x -= -0.2*_width * 4) : (renderPosWeapon.x += -0.2*_width * 4);
	//renderPosWeapon.x += (isLeft) ? (-_width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4) : (_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
	//renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * _width * 0.15 * 4;
	if (_oneAttack)
	{
		
		
		_img->setAngle(_angleOffset); // �̹��� ���� 
		_img->setScale(4); // �̹��� ũ�� 
		_img->setAnglePos(Vector2(0.5f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���
	}
	else
	{
		
		_img->setAngle(weaponDegree + _angleOffset); // �̹��� ���� 
		_img->setScale(4); // �̹��� ũ�� 
		_img->setAnglePos(Vector2(0.5f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���

	}
	
	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
	Vector2 renderPosHand2 = renderPosHand;
	renderPosHand2.y += 20;
	FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
}

void QuarterStaffBig::displayInfo()
{
}

void QuarterStaffBig::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	_oneAttack = true;
	_currAttackDelay = _baseAttackDelay;
}

void QuarterStaffBig::attack(FloatRect* rect, AttackInfo* info)
{
}

void QuarterStaffBig::attack(FloatCircle* circle, AttackInfo* info)
{
}

void QuarterStaffBig::attack(Projectile* projectile, AttackInfo* info)
{
}

void QuarterStaffBig::getHit(Vector2 const position)
{
}

PlayerStat QuarterStaffBig::equip()
{
	return PlayerStat();
}