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
	
	_handSize = Vector2(5, 5);
	_addStat.minDamage = 10;
	_addStat.maxDamage = 22;
	_addStat.attackSpeed = 0.33;
	// private ���� ����
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
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


void MartialArtOfTiger::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	CAMERA->pushShakeEvent(15, 0.1f);
			_reverseMove = false;
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
	attackCircle->size = 140;
	attackCircle->startRadian = attackRadian - PI * 0.28;
	attackCircle->endRadian = attackRadian + PI * 0.28;

	_attackDebug = FloatCircle(originPos, 140, attackRadian - PI * 0.32, attackRadian + PI * 0.32); // forDEBUG
	SOUND_MANAGER->stop("SOUND_TigerRoar");
	SOUND_MANAGER->play("SOUND_TigerRoar", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
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



void MartialArtOfTiger::equip(Player * player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}


