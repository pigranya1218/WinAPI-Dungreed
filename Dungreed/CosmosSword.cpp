#include "stdafx.h"
#include "CosmosSword.h"

void CosmosSword::init()
{
	_img = IMAGE_MANAGER->findImage("CosmosSword");
	_iconImg = IMAGE_MANAGER->findImage("CosmosSwordIcon");

	width = _img->getFrameSize().x;
	height = _img->getFrameSize().y;

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();


	_itemCode = 0x02400;

	_price = 600;

	// �⺻ �����ɼ�
	_addStat.dashDamage = 20;
	_addStat.minDamage = 7;
	_addStat.maxDamage = 10;
	_addStat.attackSpeed = 0.4;

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
	_angleOffset = 0;

}

void CosmosSword::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void CosmosSword::update(Player* player, float const elapsedTime)
{
	_ani->frameUpdate(elapsedTime);

	if (_currAttackDelay == 0) return;


	// ���� ������ ���
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);

}

void CosmosSword::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	if (_oneAttack)
	{
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
		renderPosHand.x += (width * 0.1 * 4);
		// ���� ��ġ
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft)?(-width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4): (width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4;

		_img->setScale(4); // �̹��� ũ�� 
		_img->setAngle(weaponDegree /*+ _angleOffset*/); // �̹��� ���� 
		_img->setAnglePos(Vector2(0.15f * width, 0.5f * height)); // �̹��� ȸ����ų ����
		_img->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _ani, isLeft);// �׸���

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���

		if (_drawEffect) // ����Ʈ�� �׸���
		{
			_drawEffect = false;
			Vector2 effectPos = originPos; // ȸ������ ��ġ�κ���
			float length = width * 4 * 1; // ���� ���̸�ŭ
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_COSMOSSWING", effectPos, Vector2(250, 300), degree);
		}
	}
}

void CosmosSword::frontRender(Player* player)
{

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	if (!_oneAttack)
	{
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
		renderPosHand.x += (width * 0.1 * 4);
		// ���� ��ġ
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft) ? (-width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4) : (width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4;

		_img->setScale(4); // �̹��� ũ�� 
		_img->setAngle(weaponDegree /*+ _angleOffset*/); // �̹��� ���� 
		_img->setAnglePos(Vector2(0.15f * width, 0.5f * height)); // �̹��� ȸ����ų ����
		_img->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _ani, isLeft);// �׸���

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // ���� ��Ʈ�� �׸���

		if (_drawEffect) // ����Ʈ�� �׸���
		{
			_drawEffect = false;
			Vector2 effectPos = originPos; // ȸ������ ��ġ�κ���
			float length = width * 4 * 1; // ���� ���̸�ŭ
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_COSMOSSWING", effectPos, Vector2(250, 300), degree);
		}
	}
}

void CosmosSword::displayInfo()
{
}

void CosmosSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	if (_oneAttack)
	{
		_angleOffset += 95;
	}
	else
	{
		_angleOffset -= 95;
	}
	_oneAttack = !_oneAttack;
	
	_drawEffect = true;
	_currAttackDelay = _baseAttackDelay;
}

void CosmosSword::attack(FloatRect* rect, AttackInfo* info)
{
}

void CosmosSword::attack(FloatCircle* circle, AttackInfo* info)
{
}

void CosmosSword::attack(Projectile* projectile, AttackInfo* info)
{
}

void CosmosSword::getHit(Vector2 const position)
{
}

void CosmosSword::equip(Player* player)
{
}
