#include "stdafx.h"
#include "PowerKatana.h"
void PowerKatana::init()
{
	_iconImg = IMAGE_MANAGER->findImage("PowerKatana");
	_img = IMAGE_MANAGER->findImage("PowerKatanaHUD");
	_price = 600;
	_itemName = L"���� '����'";
	_displayText = L"\"������ �Ǿ� �ֱ���. ���� ���� ���� �� �� �ְ� �Ǿ� ������, �� �� �̻��� ������ ������.. -����-\"";
	_itemCode = 0x02301; //��� ��� 01;
	// �⺻ �����ɼ�
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);

	_addStat.minDamage = 25;
	_addStat.maxDamage = 28;
	_addStat.attackSpeed = 1.18;
	//�����ɼ�

	// private ���� ����
	_attackMove = Vector2(0, 0);
	_baseAttackDelay = 0.1;
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_angleOffset = 0;
	_width = _img->getWidth();
	_height = _img->getHeight();
}

void PowerKatana::release()
{

}

void PowerKatana::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (1 / _addStat.attackSpeed / 2);

	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void PowerKatana::backRender(Player* player)
{

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
	//renderPosWeapon.x += (isLeft) ? (-width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4) : (width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4);
	//renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4;

	_img->setScale(4); // �̹��� ũ�� 
	_img->setAngle(weaponDegree /*+ _angleOffset*/); // �̹��� ���� 
	_img->setAnglePos(Vector2(0.7f * _width, 0.5f * _height)); // �̹��� ȸ����ų ����
	_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// �׸���
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
			//degree = degree + 180;
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_EXKATANAFX", effectPos, Vector2(250, 300), degree , isLeft);
		}
		else
		{

			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_EXKATANAFX", effectPos, Vector2(250, 300), -degree+ 180 , isLeft);
		}

	}

}

void PowerKatana::displayInfo()
{
}

void PowerKatana::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	
	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x));
	_drawEffect = true;
	_currAttackDelay = _baseAttackDelay;
}

void PowerKatana::attack(FloatRect* rect, AttackInfo* info)
{
}

void PowerKatana::attack(FloatCircle* circle, AttackInfo* info)
{
}

void PowerKatana::attack(Projectile* projectile, AttackInfo* info)
{
}

void PowerKatana::getHit(Vector2 const position)
{
}

PlayerStat PowerKatana::equip()
{
	return PlayerStat();
}