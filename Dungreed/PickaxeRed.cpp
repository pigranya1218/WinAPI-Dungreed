#include "stdafx.h"
#include "PickaxeRed.h"

void PickaxeRed::init()
{
	_iconImg = IMAGE_MANAGER->findImage("PickaxeRedIcon");
	_img = IMAGE_MANAGER->findImage("PickaxeRed");
	_price = 2600;
	_itemName = L"붉은 곡괭이";
	_displayText = L"\"신이 가장 싫어하는 색이 입혀진 곡괭이\"";
	_itemCode = 0x02300; //양손 에픽 00;
	// 기본 보조옵션
	
	_handSize = Vector2(5, 5);
	_addStat.minDamage = 5;
	_addStat.maxDamage = 15;
	_addStat.attackSpeed = 0.17;
	//보조옵션
	_addStat.defense = -30;
	_addStat.power = -30;
	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = false;
	_angleOffset = 0;
	_width = _img->getWidth();
	_height = _img->getHeight();
}


void PickaxeRed::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (0.05 * 0.4) / 2;

	if (_oneAttack)
	{
		_angleOffset = max(-180, (_angleOffset)-(elapsedTime * ratio));
		if (_angleOffset == -180)
		{
			SOUND_MANAGER->stop("SOUND_PickaxeRed");
			SOUND_MANAGER->play("SOUND_PickaxeRed", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
			_oneAttack = false;
		}
	}
	else
	{
		if (_angleOffset < 0)
		{
			_angleOffset = min(0, (_angleOffset)+(elapsedTime * ratio));
		}
	}


	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);
	if (_drawEffect) // 이펙트를 그린다
	{
		Vector2 effectPos = originPos; // 회전축의 위치로부터
		float length = _width * 4 * 0.5; // 무기 길이만큼
		_drawEffect = false;
		bool isLeft = (player->getDirection() == DIRECTION::LEFT);
		if (!isLeft)
		{
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_REDPICKAXESWING", effectPos, Vector2(100, 200), -degree + 180, !isLeft);
		}
		else
		{
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_REDPICKAXESWING", effectPos, Vector2(100, 200), degree, !isLeft);
		}
	}
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}



void PickaxeRed::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	// 회전축 중점
	originPos.x += ((isLeft) ? -20 : 20); // 바라보는 방향의 어깨
	originPos.y += 0;
	pos.x += ((isLeft) ? 0 : 0);
	// 회전축으로부터 마우스까지의 각도값
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);
	float handDegree = degree;
	// 좌우 대칭을 위한 계산
	float weaponDegree = handDegree;
	weaponDegree += ((isLeft) ? -180 : 180);
	if (isLeft)
	{
		weaponDegree = 180 - weaponDegree;
	}
	// 손의 위치 
	Vector2 renderPosHand = pos;
	// 무기 위치
	Vector2 renderPosWeapon = originPos;
	renderPosHand.x += 0;
	renderPosHand.y += (-sinf(weaponDegree * (PI / 180)) * 0.90 * 4);
	if (_oneAttack)
	{
		_img->setScale(4); // 이미지 크기 
		_img->setAngle(weaponDegree + _angleOffset); // 이미지 각도 
		_img->setAnglePos(Vector2(0.35f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다
	}
	else
	{
		_img->setScale(4); // 이미지 크기 
		_img->setAngle(weaponDegree + _angleOffset); // 이미지 각도 
		_img->setAnglePos(Vector2(0.35f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다
	}
	if (isLeft)
	{
		renderPosHand.x += 20 + _width * 0.03f * 4;
		renderPosHand.x += cosf(handDegree * (PI / 180)) * _width * 0.03f * 4;
		renderPosHand.y += -20;
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, -(weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, -(weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x -= 40;
		renderPosHand2.x += cosf(handDegree * (PI / 180)) * _width * 0.03f * 4;// width * 0.01f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, -(weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, -(weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos)); // 손의 렉트를 그린다

	}
	else
	{
		renderPosHand.x += 35 - _width * 0.03f * 4;
		renderPosHand.x += -cosf(handDegree * (PI / 180)) * _width * 0.03f * 4;
		renderPosHand.y += -20;
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x -= 40;
		renderPosHand2.x += -cosf(handDegree * (PI / 180)) * _width * 0.03f * 4;// width * 0.01f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (weaponDegree + _angleOffset), CAMERA->getRelativeV2(pos)); // 손의 렉트를 그린다
	}


}


void PickaxeRed::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	CAMERA->pushShakeEvent(10, 0.1f);
	
	_oneAttack = true;
	_drawEffect = true;
	_currAttackDelay = _adjustStat.attackSpeed;
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
	attackCircle->startRadian = attackRadian - PI * 0.28;
	attackCircle->endRadian = attackRadian + PI * 0.28;

	_attackDebug = FloatCircle(originPos, 120, attackRadian - PI * 0.28, attackRadian + PI * 0.28); // forDEBUG
	/*SOUND_MANAGER->stop("SOUND_PickaxeRed");
	SOUND_MANAGER->play("SOUND_PickaxeRed", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));*/
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

void PickaxeRed::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}