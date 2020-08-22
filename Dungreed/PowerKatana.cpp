#include "stdafx.h"
#include "PowerKatana.h"

void PowerKatana::init()
{
	_iconImg = IMAGE_MANAGER->findImage("PowerKatana");
	_img = IMAGE_MANAGER->findImage("PowerKatanaHUD");
	_imgAttack = IMAGE_MANAGER->findImage("KatanaWhite");
	_price = 600;
	_itemName = L"���� '����'";
	_displayText = L"\"������ �Ǿ� �ֱ���. ���� ���� ���� �� �� �ְ� �Ǿ� ������, �� �� �̻��� ������ ������.. -����-\"";
	_itemCode = 0x02301; //��� ��� 01;
	// �⺻ �����ɼ�
	
	_handSize = Vector2(5, 5);

	_addStat.minDamage = 25;
	_addStat.maxDamage = 28;
	_addStat.attackSpeed = 0.8;
	//�����ɼ�

	// private ���� ����
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = false;
	_angleOffset = 0;
	_width = _img->getWidth();
	_height = _img->getHeight();
}



void PowerKatana::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (1 / _addStat.attackSpeed / 2);
	float ratio2 = elapsedTime / (_addStat.attackSpeed * 0.08);
	
	if (_oneAttack)
	{
	
	}
	else
	{
		_imgAttack->setAlpha(0.7);
		if (_currAttackDelay <= _addStat.attackSpeed * 0.88)
		{
			_oneAttack = true;
		}
	}
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}


void PowerKatana::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	// ȸ���� ����
	originPos.x += ((isLeft) ? 15 : -15); // �ٶ󺸴� ������ ���
	originPos.y += 25;
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
	renderPosHand.x += (_width * 0.1 * 4);
	renderPosHand.y += (isLeft) ? ( -4) : ( 4);
	// ���� ��ġ
	Vector2 renderPosWeapon = originPos;
	(isLeft) ? (renderPosWeapon.x -= -0.2*_width * 4) : (renderPosWeapon.x += -0.2*_width * 4);
	if (_oneAttack)
	{
		_img->setScale(4); // �̹��� ũ�� 
		_img->setAngle(weaponDegree /*+ _angleOffset*/); // �̹��� ���� 
		_img->setAnglePos(Vector2(0.7f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���
		
	}
	else
	{
	_imgAttack->setScale(4); // �̹��� ũ�� 
	_imgAttack->setAngle(weaponDegree /*+ _angleOffset*/); // �̹��� ���� 
	_imgAttack->setAnglePos(Vector2(0.7f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
	_imgAttack->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���
	
	}
	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
	Vector2 renderPosHand2 = renderPosHand;
	renderPosHand2.x -= _width * 0.16f * 4;
	FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���

	if (_drawEffect) // ����Ʈ�� �׸���
	{
		Vector2 effectPos = originPos; // ȸ������ ��ġ�κ���
		float length = _width * 4 * 0.5; // ���� ���̸�ŭ
		_drawEffect = false;
		bool isLeft = (player->getDirection() == DIRECTION::LEFT);
		if (!isLeft)
		{
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			DamageInfo* damageinfo;
			EFFECT_MANAGER->play("EFFECT_EXKATANAFX", effectPos, Vector2(250, 300), degree , isLeft);
			
			
		}
		else
		{

			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_EXKATANAFX", effectPos, Vector2(250, 300), -degree+ 180 , isLeft);
		}
	}
	_attackDebug.render(true);
}

void PowerKatana::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	CAMERA->pushShakeEvent(10, 0.1f);

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	Vector2 renderPosHand = pos;
	_oneAttack = false;
	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x));
	_drawEffect = true;
	_currAttackDelay = _addStat.attackSpeed;

	Vector2 originPos = player->getPosition();
	originPos.x += ((player->getDirection() == DIRECTION::LEFT) ? -15 : 15); // �ٶ󺸴� ������ ���
	originPos.y += 10;
	float attackRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x));
	if (attackRadian < 0)
	{
		attackRadian += PI2;
	}
	
		int k = RANDOM->getFromIntTo(0,2);
		SOUND_MANAGER->stop(_sounds[k]);
		SOUND_MANAGER->play(_sounds[k], CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
	
	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // ������ �ڵ�� ���� �ð��� Concat�Ͽ� ���� ���̵� ���ϱ� ���� ���� �ڵ带 ������

	FloatCircle* attackCircle = new FloatCircle;
	attackCircle->origin = originPos;
	attackCircle->size = 160;
	attackCircle->startRadian = attackRadian - PI * 0.28;
	attackCircle->endRadian = attackRadian + PI * 0.28;

	_attackDebug = FloatCircle(originPos, 160, attackRadian - PI* 0.56, attackRadian + PI *0.56); // forDEBUG

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

void PowerKatana::equip(Player * player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}

