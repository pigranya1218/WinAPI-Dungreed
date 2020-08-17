#include "stdafx.h"
#include "PickaxeRed.h"

void PickaxeRed::init()
{
	_iconImg = IMAGE_MANAGER->findImage("PickaxeRedIcon");
		_img = IMAGE_MANAGER->findImage("PickaxeRed");
	_price = 600;
	_itemName = L"붉은 곡괭이";
	_displayText = L"\"신이 가장 싫어하는 색이 입혀진 곡괭이\"";
	_itemCode = 0x02300; //양손 에픽 00;
	// 기본 보조옵션
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);

	_addStat.minDamage = 5;
	_addStat.maxDamage = 15;
	_addStat.attackSpeed = 10;
	//_addStat.attackSpeed = 5.56;
	//보조옵션
	_addStat.defense = -30;
	_addStat.power = -30;
	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_baseAttackDelay = 0.1;
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_angleOffset = 0;
	width =  _img->getWidth();
	height =  _img->getHeight();
}

void PickaxeRed::release()
{

}

void PickaxeRed::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (1 / _addStat.attackSpeed / 2);

	if (_oneAttack)
	{	
		_angleOffset = max(-180, (_angleOffset) - (elapsedTime * ratio));
		if (_angleOffset == -180)
		{
			_oneAttack = false;
		}
	}
	else
	{
		if (_angleOffset < 0)
		{
			_angleOffset = min(0, (_angleOffset) + (elapsedTime * ratio));
		}
	}
	
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void PickaxeRed::backRender(Player* player)
{

}

void PickaxeRed::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	
	// 회전축 중점
	originPos.x += ((isLeft) ? -20 : 20); // 바라보는 방향의 어깨
	originPos.y += 0;

	// 회전축으로부터 마우스까지의 각도값
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

	float handDegree = degree +((isLeft) ? -180 : 180);

	// 좌우 대칭을 위한 계산
	float weaponDegree = handDegree;
	
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;

		}
	
	//renderPosHand.x += (width * 0.1 * 4);
	// 손의 위치 
	Vector2 renderPosHand = originPos;
	// 무기 위치
	Vector2 renderPosWeapon = originPos;
	 
		renderPosHand.x += (isLeft) ? ( -cosf(handDegree * (PI / 180)) * width * 0.15 * 4) : ( cosf(handDegree * (PI / 180)) * width * 0.15 * 4);
		//renderPosHand.y += (isLeft) ? (+20) : (-20);
		renderPosHand.x += (isLeft) ? (-60): (60);
		renderPosHand.y += (isLeft) ? (20) : (-20);
	//renderPosWeapon.y +=  (-sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4);
	
	

		if (_oneAttack)
		{
			_img->setScale(4); // 이미지 크기 
			
			_img->setAngle(weaponDegree + _angleOffset);//*+ _angleOffset*/); // 이미지 각도 
			_img->setAnglePos(Vector2(0.35f * width, 0.5f * height)); // 이미지 회전시킬 중점
			_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다
		}
		else
		{

			_img->setScale(4); // 이미지 크기 
			_img->setAngle(weaponDegree + _angleOffset);//*+ _angleOffset*/); // 이미지 각도 
			_img->setAnglePos(Vector2(0.35f * width, 0.5f * height)); // 이미지 회전시킬 중점
			_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다
		}
		


	
	
	


	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
	Vector2 renderPosHand2 = renderPosHand;
	renderPosHand2.x += width * 0.06f * 4;
	FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree+ _angleOffset), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다

	if (_drawEffect) // 이펙트를 그린다
	{
		Vector2 effectPos = originPos; // 회전축의 위치로부터
		float length = width * 4 * 0.5; // 무기 길이만큼
		_drawEffect = false;
		bool isLeft = (player->getDirection() == DIRECTION::LEFT);
		if (!isLeft)
		{
			//degree = degree + 180;
			effectPos.x +=  cosf(degree * (PI / 180)) * length;
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
	
}

void PickaxeRed::displayInfo()
{
}

void PickaxeRed::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	_oneAttack = true;
	// 손으로부터 마우스 에임까지의 각도
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x));
	_drawEffect = true;
	_currAttackDelay = _baseAttackDelay;
}

void PickaxeRed::attack(FloatRect* rect, AttackInfo* info)
{
}

void PickaxeRed::attack(FloatCircle* circle, AttackInfo* info)
{
}

void PickaxeRed::attack(Projectile* projectile, AttackInfo* info)
{
}

void PickaxeRed::getHit(Vector2 const position)
{
}

PlayerStat PickaxeRed::equip()
{
	return PlayerStat();
}