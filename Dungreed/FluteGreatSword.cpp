#include "stdafx.h"
#include "FluteGreatSword.h"

void FluteGreatSword::init()
{
	_iconImg = IMAGE_MANAGER->findImage("FluteGreatSword");
	_img = IMAGE_MANAGER->findImage("FluteGreatSword");
	_price = 3600;
	_itemName = L"�����Į";
	_displayText = L"\"�ֹ��� �ʼ�ǰ�� �ٽ� ���ƿԽ��ϴ�.\"";
	_itemCode = 0x02203; //��� ��� 01;
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
	_oneAttack = false;
	_twoAttack = false;
	_angleOffset = 0;
	_width = _img->getWidth();
	_height = _img->getHeight();
}

void FluteGreatSword::release()
{

}

void FluteGreatSword::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (_adjustStat.attackSpeed * 0.4) / 2;

	if (_oneAttack)
	{



		abs(_angleOffset += -(elapsedTime * ratio));

		
		if (_angleOffset <-180)
		{
			_oneAttack = false;
		}
		//if (_angleOffset = max(-180, (_angleOffset)-(elapsedTime * ratio)))
		//{
		//	_angleOffset = max(0, (_angleOffset)-(elapsedTime * ratio));
		//
		//}
	}
	else
	{
		//_img->setAngle(+180);
		//if (_angleOffset < 0)
		//{
		//	_angleOffset = min(180, (_angleOffset)+(elapsedTime * ratio));
		//}
		//_oneAttack = true;
	}
	if (_twoAttack)
	{

	}

	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void FluteGreatSword::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	
		// ȸ���� ����
		originPos.x += ((isLeft) ? -15 : 15); // �ٶ󺸴� ������ ���
		originPos.y += 5;

		// ȸ�������κ��� ���콺������ ������
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

		float handDegree = degree + ((isLeft) ? -110 : 110);

		// �¿� ��Ī�� ���� ���
		float weaponDegree = handDegree;
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;
		}

		// ���� ��ġ 
		Vector2 renderPosHand = originPos;
		renderPosHand.x += (_width * 0.1 * 4);
		// ���� ��ġ
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft) ? (-_width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4) : (_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * _width * 0.15 * 4;
		if (_oneAttack)
		{
		_img->setScale(4); // �̹��� ũ�� 
		_img->setAngle(weaponDegree+ _angleOffset); // �̹��� ���� 
		_img->setAnglePos(Vector2(0.15f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft); // �׸���
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += _width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		}

	
}

void FluteGreatSword::frontRender(Player* player)
{

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	
		// ȸ���� ����
		originPos.x += ((isLeft) ? -15 : 15); // �ٶ󺸴� ������ ���
		originPos.y += 10;

		// ȸ�������κ��� ���콺������ ������
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

		float handDegree = degree + ((isLeft) ? (-110 - _angleOffset) : (110 + _angleOffset));

		// �¿� ��Ī�� ���� ���
		float weaponDegree = handDegree;
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;
		}

		// ���� ��ġ 
		Vector2 renderPosHand = originPos;
		renderPosHand.x += (_width * 0.1 * 4);
		// ���� ��ġ
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft) ? (-_width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4) : (_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * _width * 0.15 * 4;
		if (!_oneAttack)
		{
		_img->setScale(4); // �̹��� ũ�� 
		_img->setAngle(weaponDegree +_angleOffset); // �̹��� ���� 
		_img->setAnglePos(Vector2(0.15f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft); // �׸���
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += _width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���

		}
	

	//_attackDebug.render(true);
}

void FluteGreatSword::displayInfo()
{
}

void FluteGreatSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	//if (_oneAttack)
	//{
	//	_angleOffset += 95;
	//}
	//else
	//{
	//	_angleOffset -= 95;
	//}
	//_oneAttack = !_oneAttack;
	_oneAttack = true;
	_drawEffect = true;
	_currAttackDelay = _addStat.attackSpeed;

	Vector2 originPos = player->getPosition();
	originPos.x += ((player->getDirection() == DIRECTION::LEFT) ? -15 : 15); // �ٶ󺸴� ������ ���
	originPos.y += 10;
	//float attackRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x));
	//if (attackRadian < 0)
	//{
	//	attackRadian += PI2;
	//}
	//string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // ������ �ڵ�� ���� �ð��� Concat�Ͽ� ���� ���̵� ���ϱ� ���� ���� �ڵ带 ������

	//FloatCircle* attackCircle = new FloatCircle;
	//attackCircle->origin = originPos;
	//attackCircle->size = 240;
	//attackCircle->startRadian = attackRadian - PI * 0.28;
	//attackCircle->endRadian = attackRadian + PI * 0.28;

	////_attackDebug = FloatCircle(originPos, 240, attackRadian - PI * 0.28, attackRadian + PI * 0.28); // forDEBUG

	//AttackInfo* attackInfo = new AttackInfo;
	//attackInfo->team = OBJECT_TEAM::PLAYER;
	//attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	//attackInfo->critical = 0;
	//attackInfo->criticalDamage = 0;
	//attackInfo->minDamage = _addStat.minDamage;
	//attackInfo->maxDamage = _addStat.maxDamage;
	//attackInfo->knockBack = 15;

	//player->attack(attackCircle, attackInfo);

	//delete attackCircle;
	//delete attackInfo;
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
