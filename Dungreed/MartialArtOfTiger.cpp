#include "stdafx.h"
#include "MartialArtOfTiger.h"

void MartialArtOfTiger::init()
{
	_effect = IMAGE_MANAGER->findImage("EFFECT_TIGERPUNCH");
	_iconImg =IMAGE_MANAGER->findImage("TigerPunchIcon");
	_price = 600;


	_itemName = L"ȣ���� �ǹ�";
	_displayText = L"\"�䳢�� ���߰� �ϰ� ���츦 ���̿ø� �Ѱ� �ϴ� ���¿��� �������� �ǹ�\"";
	_itemCode = 0x01300; //�Ѽ� ���� 00
	// �⺻ �����ɼ�
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);

	_addStat.minDamage = 10;
	_addStat.maxDamage = 22;
	_addStat.attackSpeed = 0.6;
	// private ���� ����
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	

}

void MartialArtOfTiger::release()
{

}

void MartialArtOfTiger::update(Player* player, float const elapsedTime)
{
	if (_currAttackDelay == 0) return;
	
	float ratio = elapsedTime / (_addStat.attackSpeed * 0.08);
	if (_reverseMove)
	{
		_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 30 * ratio));
		_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 30 * ratio));
	}
	else
	{
		_attackMove.x = min(abs(cosf(_attackAngle) * 30), _attackMove.x + abs(cosf(_attackAngle) * 30 * ratio));
		_attackMove.y = min(abs(-sinf(_attackAngle) * 30), _attackMove.y + abs((-sinf(_attackAngle)) * 30 * ratio));

		if (_currAttackDelay <= _addStat.attackSpeed * 0.88)
		{
			_reverseMove = true;
			_drawEffect = true;
		}
	}

	


	// ���� ������ ���
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);

}

void MartialArtOfTiger::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	if (isLeft)
	{
		Vector2 renderPosLeft = Vector2(pos.x - 20, pos.y + 18);
		float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosLeft.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosLeft.x)) * (180 / PI) + 360;
		if (angle > 360)
		{
			angle -= 360;
		}
		renderPosLeft.x += -_attackMove.x;
		renderPosLeft.y += ((angle >= 180) ? (_attackMove.y) : (-_attackMove.y));

		_leftHand = rectMakePivot(renderPosLeft, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_leftHand), 210, 188, 181, 1.f, angle, CAMERA->getRelativeV2(_leftHand.getCenter()));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_leftHand), 40, 36, 58, 1, 2.f, angle, CAMERA->getRelativeV2(_leftHand.getCenter()));
	}
	else
	{
		Vector2 renderPosRight = Vector2(pos.x + 20, pos.y + 18);
		float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosRight.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosRight.x)) * (180 / PI) + 360;
		if (angle > 360)
		{
			angle -= 360;
		}
		renderPosRight.x += _attackMove.x;
		renderPosRight.y += ((angle >= 180) ? (_attackMove.y) : (-_attackMove.y));

		_rightHand = rectMakePivot(renderPosRight, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_rightHand), 210, 188, 181, 1.f, angle, CAMERA->getRelativeV2(_rightHand.getCenter()));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rightHand), 40, 36, 58, 1, 2.f, angle, CAMERA->getRelativeV2(_rightHand.getCenter()));
	}
}

void MartialArtOfTiger::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x)) * (180 / PI);

	if (isLeft)
	{
		Vector2 renderPosRight = Vector2(pos.x + 20, pos.y + 18);
		_rightHand = rectMakePivot(renderPosRight, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_rightHand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rightHand), 40, 36, 58, 1, 2.f);
		if (_drawEffect) // ����Ʈ�� �׸���
		{
			_drawEffect = false;
			Vector2 effectPos = pos; // ȸ������ ��ġ�κ���
			float length = _iconImg->getWidth() * 4 * 1; // ���� ���̸�ŭ
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_TIGERPUNCH", effectPos, Vector2(200, 200), 0);
		}

	}
	else
	{
		Vector2 renderPosLeft = Vector2(pos.x - 20, pos.y + 18);
		_leftHand = rectMakePivot(renderPosLeft, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_leftHand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_leftHand), 40, 36, 58, 1, 2.f);
		if (_drawEffect) // ����Ʈ�� �׸���
		{
			_drawEffect = false;
			Vector2 effectPos = pos; // ȸ������ ��ġ�κ���
			float length = _iconImg->getWidth() * 4 * 1; // ���� ���̸�ŭ
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			
			
			EFFECT_MANAGER->play("EFFECT_TIGERPUNCH", effectPos, Vector2(200, 200), 0);
		}

	}
}

void MartialArtOfTiger::displayInfo()
{
}

void MartialArtOfTiger::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos; // ���� ��ġ
	renderPosHand.x += ((isLeft) ? (-20) : (20));
	renderPosHand.y += 20;
	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angle > PI2)
	{
		angle -= PI2;
	}

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _addStat.attackSpeed;
}

void MartialArtOfTiger::attack(FloatRect* rect, AttackInfo* info)
{
}

void MartialArtOfTiger::attack(FloatCircle* circle, AttackInfo* info)
{
}

void MartialArtOfTiger::attack(Projectile* projectile, AttackInfo* info)
{
}

void MartialArtOfTiger::getHit(Vector2 const position)
{
}

void MartialArtOfTiger::equip(Player * player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}


