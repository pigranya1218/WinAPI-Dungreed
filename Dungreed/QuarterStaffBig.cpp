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
	_handSize = Vector2(5, 5);
	_addStat.minDamage = 4;
	_addStat.maxDamage = 6;
	_addStat.defense = 5;
	_addStat.attackSpeed = 0.26;
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

	// 회전축 중점
	originPos.x += ((isLeft) ? -20 :20 ); // 바라보는 방향의 어깨
	//originPos.y += 0;

	// 회전축으로부터 마우스까지의 각도값
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

	float handDegree = degree;

	// 좌우 대칭을 위한 계산
	float weaponDegree = handDegree;
	
	
	// 손의 위치 
	Vector2 renderPosHand = originPos;
	
	//renderPosHand.x += (_width * 0.1 * 4);
	
	renderPosHand.y +=  -sinf(weaponDegree * (PI / 180)* 1.4 * 4) - 10;

	// 무기 위치
	Vector2 renderPosWeapon = originPos;
	if (_oneAttack)
	{
		if (!isLeft)
		{
		_img->setAngle(_angleOffset); // 이미지 각도 
		}
		else
		{
			_img->setAngle(-_angleOffset); // 이미지 각도 
		}
		_img->setScale(4); // 이미지 크기 
		_img->setAnglePos(Vector2(0.5f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (_angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, ( _angleOffset), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.y += 20;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, ( _angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, ( _angleOffset), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다



	}
	else
	{
		if (!isLeft)
		{
			_img->setAngle(weaponDegree - _angleOffset); // 이미지 각도 
		}
		else
		{
			_img->setAngle(-weaponDegree + _angleOffset); // 이미지 각도 
		}
		_img->setScale(4); // 이미지 크기 
		_img->setAnglePos(Vector2(0.5f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다



		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.y += 20;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree + _angleOffset), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다


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
	originPos.x += ((player->getDirection() == DIRECTION::LEFT) ? -15 : 15); // 바라보는 방향의 어깨
	originPos.y += 10;
	float attackRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x));
	if (attackRadian < 0)
	{
		attackRadian += PI2;
	}

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함

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
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}

