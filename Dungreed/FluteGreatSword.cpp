#include "stdafx.h"
#include "FluteGreatSword.h"

void FluteGreatSword::init()
{
	_iconImg = IMAGE_MANAGER->findImage("FluteGreatSword");
	_img = IMAGE_MANAGER->findImage("FluteGreatSword");
	_price = 3600;
	_itemName = L"�����Į";
	_displayText = L"\"�ֹ��� �ʼ�ǰ�� �ٽ� ���ƿԽ��ϴ�.\"";
	_itemCode = 0x02202; //��� ��� 01;
	// �⺻ �����ɼ�
	

	_handSize = Vector2(5, 5);

	_addStat.minDamage = 5;
	_addStat.maxDamage = 8;
	_addStat.attackSpeed = 0.5;
	//�����ɼ�

	// private ���� ����
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = false;
	_back = true;
	_angleOffset = 0;
	_width = _img->getWidth();
	_height = _img->getHeight();
}



void FluteGreatSword::update(Player* player, float const elapsedTime)
{
	if (_currAttackDelay == 0) return;
	float time = elapsedTime * 0.5;
	float ratio = 180 / 3.1*0.4 ;
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	if (_back)
	{
		if(!_oneAttack)
		{ 
			if (isLeft)
			{
				_angleOffset = max(-180, abs((_angleOffset)-(elapsedTime * ratio)));
				if (_angleOffset == -180)
				{
					_back = false;
				}
			}
			else
			{
				_angleOffset = max(-180, (_angleOffset)-(elapsedTime * ratio));
				if (_angleOffset == -180)
				{
					_back = false;
				}
			}
		}
		else
		{

		}
		
	}
	else
	{
		if (_oneAttack)
		{
			if (isLeft)
			{

			}
			else
			{
			
			}
		}
		else
		{
			
		}
	}
	_currAttackDelay = max(0, _currAttackDelay - time);
}

void FluteGreatSword::backRender(Player* player)
{
	
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
		// ȸ���� ����
		originPos.x += ((isLeft) ? -25 : 25); // �ٶ󺸴� ������ ���
		
		// ȸ�������κ��� ���콺������ ������
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);
		float handDegree = degree + ((isLeft) ? -180 : 180);
		// �¿� ��Ī�� ���� ���
		float weaponDegree = handDegree;
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;
		}
		// ���� ��ġ 
		Vector2 renderPosHand = originPos;
		
		renderPosHand.x += (isLeft) ? (_width * 0.1 * 4):(_width * 0.1 * 4);
		// ���� ��ġ
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft) ? (-_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * -_width * 0.15 * 4) : (_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * _width * 0.15 * 4;

		
		if (isLeft)
		{
			_img->setAngle(weaponDegree + _angleOffset); // �̹��� ���� 
		}
		else
		{
			_img->setAngle(weaponDegree + _angleOffset); // �̹��� ���� 
		}
		_img->setScale(4); // �̹��� ũ�� 
		_img->setAnglePos(Vector2(0.15f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);

		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += _width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);

		if (_back)
		{
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft); // �׸���
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
	
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		
		_attackDebug.render(true);
	}
}

void FluteGreatSword::frontRender(Player* player)
{



	
	
		bool isLeft = (player->getDirection() == DIRECTION::LEFT);
		Vector2 originPos = player->getPosition();
		Vector2 pos = player->getPosition();
		// ȸ���� ����
		originPos.x += ((isLeft) ? -25 : 25); // �ٶ󺸴� ������ ���

		// ȸ�������κ��� ���콺������ ������
		float degree;
		if (isLeft)
		{
			degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);
		}
		else
		{
			degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);
		}
		
		float handDegree = degree + ((isLeft) ? -180 : 180);
		// �¿� ��Ī�� ���� ���
		float weaponDegree = -handDegree ;
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree; 
		}
		// ���� ��ġ 
		Vector2 renderPosHand = originPos;

		renderPosHand.x += (isLeft) ? (-_width * 0.1 * 4) : (-_width * 0.1 * 4);
		// ���� ��ġ
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft) ? (_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4) : (-_width * 0.35 * 4 + -cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
		renderPosWeapon.y += (-sinf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
		//renderPosWeapon.y += -20;

		if (isLeft)
		{
			_img->setAngle(weaponDegree + _angleOffset); // �̹��� ���� 
		}
		else
		{
			_img->setAngle(weaponDegree + _angleOffset); // �̹��� ���� 
		}
		_img->setScale(4); // �̹��� ũ�� 

		
			_img->setAnglePos(Vector2(0.15f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
			_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
			Vector2 renderPosHand2 = renderPosHand;
			renderPosHand2.x += _width * 0.06f * 4;
			FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);

		if (!_back)
		{
		if (isLeft)
		{
			
			_img->render(CAMERA->getRelativeV2(renderPosWeapon), !isLeft); // �׸���			
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
			
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		}
		else
		{
			
			_img->render(CAMERA->getRelativeV2(renderPosWeapon), !isLeft); // �׸���
			
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
			
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		}
		_attackDebug.render(true);
	}
}



void FluteGreatSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;
	_drawEffect = true;
	_currAttackDelay = _addStat.attackSpeed;
	
	_back = !_back;
	_oneAttack = !_oneAttack;

	Vector2 originPos = player->getPosition();
	originPos.x += ((player->getDirection() == DIRECTION::LEFT) ? -15 : 15); // �ٶ󺸴� ������ ���
	originPos.y += 10;
	//==========================================================================

	
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

void FluteGreatSword::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}
