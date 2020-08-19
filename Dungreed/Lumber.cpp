#include "stdafx.h"
#include "Lumber.h"
void Lumber::init()
{
	_img = IMAGE_MANAGER->findImage("Lumber");
	_iconImg = IMAGE_MANAGER->findImage("Lumber");

	_width = _img->getFrameSize().x;
	_height = _img->getFrameSize().y;

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();
	_ani->isPlay();
	_itemName = L"����";
	_displayText = L"\"������ü�� ������ ���� ����\"";
	_itemCode = 0x01104; // �Ѽ� �Ϲ�

	_price = 600;

	// �⺻ �����ɼ�

	_addStat.minDamage = 95;
	_addStat.maxDamage = 100;
	_addStat.attackSpeed = 1.0;

	_handSize = Vector2(5, 5);



	// private ���� ����
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_isBroken = false;
	_angleOffset = 15;
	
}

void Lumber::release()
{

}

void Lumber::update(Player* player, float const elapsedTime)
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

	if (_currAttackDelay <= _addStat.attackSpeed * 0.8)
	{
		if (_isBroken)
		{
			_img = IMAGE_MANAGER->findImage("Lumber1");
			_iconImg = IMAGE_MANAGER->findImage("Lumber1");

			_itemName = L"�η��� ����";
			_displayText = L"\"��Ÿ���Ե� ���µ��� ������ �ִ� �� ����.\"";
			_addStat.minDamage = 4;
			_addStat.maxDamage = 11;
			_addStat.attackSpeed = 0.33;
		}
	}



	// ���� ������ ���
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void Lumber::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	if (_oneAttack)
	{
		// �÷��̾� ����
		originPos.x += ((isLeft) ? -20 : 20);



		// �����κ��� ���콺 ���ӱ����� ����

			//float degree = atan2f(-(_ptMouse.y - Pos.y), (_ptMouse.x - Pos.x)) * (180 / PI) +90;
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x - pos.x))) * (180 / PI);
		float degreeOffsetangle = degree + 90;



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

			renderPosWeapon.x -= 19 - (cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
			renderPosWeapon.y += 20 + (sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
			renderPosHand.x -= (-cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
			renderPosHand.y += 20 + (sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
		}
		else
		{
			renderPosWeapon.x += 19 + (-cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
			renderPosWeapon.y += 20 + (-sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
			renderPosHand.x += -cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4);
			renderPosHand.y += 20 + (-sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
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
		Vector2 last = renderPosHand;

		if (isLeft) // ������ ���� ����
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(last));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(last)); // ���� ��Ʈ�� �׸���
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

void Lumber::frontRender(Player* player)
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

		//float degree = atan2f(-(_ptMouse.y - Pos.y), (_ptMouse.x - Pos.x)) * (180 / PI) + 90;
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x)) * (180 / PI);
		float degreeOffsetangle = degree + 90;


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

			renderPosWeapon.x += 5 + (-cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4));
			renderPosWeapon.y += 5 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
			renderPosHand.x += 47 + (-cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4)) - 23;
			renderPosHand.y += 5 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
		}
		else
		{
			renderPosWeapon.x -= -5 + (cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4));
			renderPosWeapon.y += 25 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
			renderPosHand.x -= 37 + (cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4)) - 23;
			renderPosHand.y += 25 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
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

void Lumber::displayInfo()
{
}

void Lumber::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	_isBroken = true;
	Vector2 renderPosHand = pos;

	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x));
	_reverseMove = false;
	_currAttackDelay = _addStat.attackSpeed;
}

void Lumber::attack(FloatRect* rect, AttackInfo* info)
{
}

void Lumber::attack(FloatCircle* circle, AttackInfo* info)
{
}

void Lumber::attack(Projectile* projectile, AttackInfo* info)
{
}

void Lumber::getHit(Vector2 const position)
{
}

void Lumber::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}