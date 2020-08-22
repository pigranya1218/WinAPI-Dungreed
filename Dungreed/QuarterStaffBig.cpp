#include "stdafx.h"
#include "QuarterStaffBig.h"
void QuarterStaffBig::init()
{
	_iconImg = IMAGE_MANAGER->findImage("QuarterStaffBig");
	_img = IMAGE_MANAGER->findImage("QuarterStaffBig");
	_price = 600;
	_itemName = L"�ڴ޳��� �ִܺ�'";
	_displayText = L"\"������ ������ �ֿ��ϴ� �ִܺ�. ������ �ſ� ������.\"";
	_itemCode = 0x02201; //��� ��� 01;
	// �⺻ �����ɼ�
	_handSize = Vector2(5, 5);
	_addStat.minDamage = 4;
	_addStat.maxDamage = 6;
	_addStat.defense = 5;
	_addStat.attackSpeed = 0.26;
	//�����ɼ�

	// private ���� ����
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = false;
	_attackAngle = 0;
	_angleOffset = 0;
	_width = _img->getWidth();
	_height = _img->getHeight();
}

void QuarterStaffBig::update(Player* player, float const elapsedTime)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	float ratio = 180 / ((0.33 * 0.4));
	if (_oneAttack)
	{
		

		_img->setAlpha(0.8f);
			_angleOffset = max(-720, ((_angleOffset)-(elapsedTime * ratio)));
		if (_angleOffset == -720)
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

void QuarterStaffBig::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	// ȸ���� ����
	originPos.x += ((isLeft) ? -20 :20 ); // �ٶ󺸴� ������ ���
	//originPos.y += 0;

	// ȸ�������κ��� ���콺������ ������
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

	float handDegree = degree;

	// �¿� ��Ī�� ���� ���
	float weaponDegree = handDegree;
	
	
	// ���� ��ġ 
	Vector2 renderPosHand = originPos;
	
	//renderPosHand.x += (_width * 0.1 * 4);
	
	renderPosHand.y +=  -sinf(weaponDegree * (PI / 180)* 1.4 * 4) - 10;

	// ���� ��ġ
	Vector2 renderPosWeapon = originPos;
	if (_oneAttack)
	{
		if (!isLeft)
		{
		_img->setAngle(_angleOffset); // �̹��� ���� 
		}
		else
		{
			_img->setAngle(-_angleOffset); // �̹��� ���� 
		}
		_img->setScale(4); // �̹��� ũ�� 
		_img->setAnglePos(Vector2(0.5f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (_angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, ( _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.y += 20;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, ( _angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, ( _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���



	}
	else
	{
		if (!isLeft)
		{
			_img->setAngle(weaponDegree - _angleOffset); // �̹��� ���� 
		}
		else
		{
			_img->setAngle(-weaponDegree + _angleOffset); // �̹��� ���� 
		}
		_img->setScale(4); // �̹��� ũ�� 
		_img->setAnglePos(Vector2(0.5f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���



		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.y += 20;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���


	}
	
	
	
	
	
	_attackDebug.render(true);
}

void QuarterStaffBig::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	CAMERA->pushShakeEvent(3, 0.1f);

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	_oneAttack = true;
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
	attackCircle->startRadian = 0.01  ;
	attackCircle->endRadian = PI2 ;

	_attackDebug = FloatCircle(originPos, 120, 0.01 , PI2); // forDEBUG
	
		SOUND_MANAGER->stop("SOUND_generalAttack");
		SOUND_MANAGER->play("SOUND_generalAttack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
		SOUND_MANAGER->isPlaySound("SOUND_generalAttack");
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = _addStat.minDamage;
	attackInfo->maxDamage = _addStat.maxDamage;
	attackInfo->knockBack = 0.1;
	player->attack(attackCircle, attackInfo);
	delete attackCircle;
	delete attackInfo;
}
void QuarterStaffBig::equip(Player * player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}

