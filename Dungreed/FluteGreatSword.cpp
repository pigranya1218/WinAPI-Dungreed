#include "stdafx.h"
#include "FluteGreatSword.h"

void FluteGreatSword::init()
{
	_iconImg = IMAGE_MANAGER->findImage("FluteGreatSword");
	_img = IMAGE_MANAGER->findImage("FluteGreatSword");
	_price = 3600;
	_itemName = L"흑장미칼";
	_displayText = L"\"주방의 필수품이 다시 돌아왔습니다.\"";
	_itemCode = 0x02202; //양손 고급 01;
	// 기본 보조옵션
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);

	_addStat.minDamage = 5;
	_addStat.maxDamage = 8;
	_addStat.attackSpeed = 0.5;
	//보조옵션

	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = false;
	_twoAttack = false;
	_angleOffset = 0;
	_width = _img->getWidth();
	_height = _img->getHeight();
}



void FluteGreatSword::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (_adjustStat.attackSpeed * 0.4) / 2;
	//if (_angleOffset > 360)
	//{
	//	_angleOffset = 0;
	//}
	//if (_angleOffset < -360)
	//{
	//	_angleOffset = 0;
	//}



	if (_oneAttack)
	{
		//abs(_angleOffset += -(elapsedTime * ratio));
		
		if (_angleOffset <-180)
		{
			_oneAttack = false;
		}
	}
	else
	{
	}
	if (_twoAttack)
	{

	}

	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void FluteGreatSword::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
		// 회전축 중점
		originPos.x += ((isLeft) ? -15 : 15); // 바라보는 방향의 어깨
		originPos.y += 5;
		// 회전축으로부터 마우스까지의 각도값
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);
		float handDegree = degree + ((isLeft) ? -110 : 110);
		// 좌우 대칭을 위한 계산
		float weaponDegree = handDegree;
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;
		}
		// 손의 위치 
		Vector2 renderPosHand = originPos;
		renderPosHand.x += (_width * 0.1 * 4);
		// 무기 위치
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft) ? (-_width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4) : (_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * _width * 0.15 * 4;
		if (!_oneAttack)
		{
		_img->setScale(4); // 이미지 크기 
		_img->setAngle(weaponDegree+ _angleOffset); // 이미지 각도 
		_img->setAnglePos(Vector2(0.15f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft); // 그린다
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += _width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
		}

	
}

void FluteGreatSword::frontRender(Player* player)
{

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	
		// 회전축 중점
		originPos.x += ((isLeft) ? -15 : 15); // 바라보는 방향의 어깨
		originPos.y += 0;

		// 회전축으로부터 마우스까지의 각도값
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);
		degree += -180;
		float handDegree = degree +((isLeft) ? (-110 - _angleOffset) : (110 + _angleOffset));

		// 좌우 대칭을 위한 계산
		float weaponDegree = handDegree;
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;
		}

		// 손의 위치 
		Vector2 renderPosHand = originPos;
		renderPosHand.x += (_width * 0.1 * 4);
		// 무기 위치
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft) ? (_width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4) : (-_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * -_width * 0.15 * 4;
		if (_oneAttack)
		{
		_img->setScale(4); // 이미지 크기 
		_img->setAngle(-weaponDegree + _angleOffset); // 이미지 각도 
		_img->setAnglePos(Vector2(0.15f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), !isLeft); // 그린다
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += _width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다

		}
}



void FluteGreatSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;
	_oneAttack = true;
	_drawEffect = true;
	_currAttackDelay = _addStat.attackSpeed;

	Vector2 originPos = player->getPosition();
	originPos.x += ((player->getDirection() == DIRECTION::LEFT) ? -15 : 15); // 바라보는 방향의 어깨
	originPos.y += 10;

}

void FluteGreatSword::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}
