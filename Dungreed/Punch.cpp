#include "stdafx.h"
#include "Punch.h"

void Punch::init()
{
	//주먹 이미지
	//가격 없음
	_price = 0;
	//보조 옵션 없음
	_addStat.minDamage = 1;
	_addStat.maxDamage = 2;
	_addStat.attackSpeed = 0.4;

	_itemCode = 0x01100; // 한손 노말 00
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;

	//손 표현할 렉트
	_handSize = Vector2(5, 5);

}


void Punch::update(Player* player, float const elapsedTime)
{
	if (_currAttackDelay == 0) return;

	float ratio = elapsedTime / (_adjustStat.attackSpeed * 0.08);
	if (_reverseMove)
	{
		_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 30 * ratio));
		_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 30 * ratio));
	}
	else
	{
		_attackMove.x = min(abs(cosf(_attackAngle) * 30), _attackMove.x + abs(cosf(_attackAngle) * 30 * ratio));
		_attackMove.y = min(abs(-sinf(_attackAngle) * 30), _attackMove.y + abs((-sinf(_attackAngle)) * 30 * ratio));

		// 찌르는 모션동안 계속 공격판정
		player->attack(_attackCircle, _attackInfo);

		if (_currAttackDelay <= _adjustStat.attackSpeed * 0.88)
		{
			_reverseMove = true;
			delete _attackCircle;
			delete _attackInfo;
		}
	}

	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void Punch::backRender(Player* player)
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
		renderPosLeft.y += ((angle >= 180)?(_attackMove.y):(-_attackMove.y));

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

	if (_attackCircle != nullptr)
	{
		_attackCircle->render(true);
	}
}

void Punch::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	if (isLeft)
	{
		Vector2 renderPosRight = Vector2(pos.x + 20, pos.y + 18);
		_rightHand = rectMakePivot(renderPosRight, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_rightHand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_rightHand), 40, 36, 58, 1, 2.f);
	}
	else
	{
		Vector2 renderPosLeft = Vector2(pos.x - 20, pos.y + 18);
		_leftHand = rectMakePivot(renderPosLeft, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_leftHand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_leftHand), 40, 36, 58, 1, 2.f);
	}
}



void Punch::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos; // 손의 위치
	renderPosHand.x += ((isLeft) ? (-20) : (20)); 
	renderPosHand.y += 20; 
	// 손으로부터 마우스 에임까지의 각도
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angle > PI2)
	{
		angle -= PI2;
	}

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _adjustStat.attackSpeed;

	Vector2 originPos = player->getPosition();
	originPos.x += ((isLeft) ? (-20) : (20));
	originPos.y += 20; // 플레이어의 중점으로부터 무기를 들고 있는 높이
	float attackRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x));
	if (attackRadian < 0)
	{
		attackRadian += PI2;
	}
	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함

	_attackCircle = new FloatCircle;
	_attackCircle->origin = originPos;
	_attackCircle->size = 35;
	_attackCircle->startRadian = attackRadian - PI * 0.03;
	_attackCircle->endRadian = attackRadian + PI * 0.03;

	_attackInfo = new AttackInfo;
	_attackInfo->team = OBJECT_TEAM::PLAYER;
	_attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	_attackInfo->critical = 0;
	_attackInfo->criticalDamage = 0;
	_attackInfo->minDamage = _addStat.minDamage;
	_attackInfo->maxDamage = _addStat.maxDamage;
	_attackInfo->knockBack = 5;
}



void Punch::equip(Player * player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}
