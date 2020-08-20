#include "stdafx.h"
#include "QuarterStaffBig.h"
void QuarterStaffBig::init()
{
	_iconImg = IMAGE_MANAGER->findImage("QuarterStaffBig");
	_img = IMAGE_MANAGER->findImage("QuarterStaffBig");
	_price = 600;
	_itemName = L"박달나무 쌍단봉'";
	_displayText = L"\"무술의 달인이 애용하던 쌍단봉. 맞으면 매우 아프다.\"";
	_itemCode = 0x02201; //양손 고급 01;
	// 기본 보조옵션
	_addStat.dashDamage = 20;
	_handSize = Vector2(5, 5);
	_addStat.minDamage = 9;
	_addStat.maxDamage = 11;
	_addStat.defense = 5;
	_addStat.attackSpeed = 0.2;
	//보조옵션

	// private 변수 설정
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
	float ratio = 180 / (1 / _addStat.attackSpeed /2);
	if (_oneAttack)
	{
		_angleOffset = max(-360, ((_angleOffset)  - (elapsedTime * ratio)));
		if (_angleOffset == -360)
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

	// 회전축 중점
	originPos.x += ((isLeft) ? 0 :0 ); // 바라보는 방향의 어깨
	originPos.y += 0;

	// 회전축으로부터 마우스까지의 각도값
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

	float handDegree = degree;

	// 좌우 대칭을 위한 계산
	float weaponDegree = handDegree;
	
	if (isLeft)
	{
		weaponDegree = 180 - weaponDegree;
	}
	// 손의 위치 
	Vector2 renderPosHand = originPos;
	renderPosHand.x += 0;
	//renderPosHand.x += (_width * 0.1 * 4);
	
	renderPosHand.y +=  -sinf(weaponDegree * (PI / 180)* 0.91 * 4) - 10;

	// 무기 위치
	Vector2 renderPosWeapon = originPos;
	if (_oneAttack)
	{
		_img->setAngle(_angleOffset); // 이미지 각도 
		_img->setScale(4); // 이미지 크기 
		_img->setAnglePos(Vector2(0.5f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다
	}
	else
	{
		_img->setAngle(weaponDegree + _angleOffset); // 이미지 각도 
		_img->setScale(4); // 이미지 크기 
		_img->setAnglePos(Vector2(0.5f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다
	}
	
	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
	Vector2 renderPosHand2 = renderPosHand;
	renderPosHand2.y += 20;
	FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
}
void QuarterStaffBig::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	_oneAttack = true;
	_currAttackDelay = _addStat.attackSpeed;
}
void QuarterStaffBig::equip(Player * player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}

