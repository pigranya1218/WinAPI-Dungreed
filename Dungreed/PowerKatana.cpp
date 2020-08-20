#include "stdafx.h"
#include "PowerKatana.h"
void PowerKatana::init()
{
	_iconImg = IMAGE_MANAGER->findImage("PowerKatana");
	_img = IMAGE_MANAGER->findImage("PowerKatanaHUD");
	_imgAttack = IMAGE_MANAGER->findImage("KatanaWhite");
	_price = 600;
	_itemName = L"육도 '가이'";
	_displayText = L"\"봉인이 되어 있군요. 여덟 개의 문을 열 수 있게 되어 있지만, 네 개 이상은 저희의 힘으론.. -로젠-\"";
	_itemCode = 0x02301; //양손 희귀 01;
	// 기본 보조옵션
	_addStat.dashDamage = 20;

	_handSize = Vector2(5, 5);

	_addStat.minDamage = 25;
	_addStat.maxDamage = 28;
	_addStat.attackSpeed = 0.8;
	//보조옵션

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



void PowerKatana::update(Player* player, float const elapsedTime)
{
	float ratio = 180 / (1 / _addStat.attackSpeed / 2);
	float ratio2 = elapsedTime / (_addStat.attackSpeed * 0.08);
	if (_oneAttack)
	{
	
	}
	else
	{
		_imgAttack->setAlpha(0.7);
		if (_currAttackDelay <= _addStat.attackSpeed * 0.88)
		{
			_oneAttack = true;
		}
	}
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}


void PowerKatana::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	// 회전축 중점
	originPos.x += ((isLeft) ? 15 : -15); // 바라보는 방향의 어깨
	originPos.y += 25;

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
	renderPosHand.x += (_width * 0.1 * 4);
	renderPosHand.y += (isLeft) ? ( -4) : ( 4);
	
	// 무기 위치
	Vector2 renderPosWeapon = originPos;
	(isLeft) ? (renderPosWeapon.x -= -0.2*_width * 4) : (renderPosWeapon.x += -0.2*_width * 4);
	//renderPosWeapon.x += (isLeft) ? (-width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4) : (width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4);
	//renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4;
	if (_oneAttack)
	{
		_img->setScale(4); // 이미지 크기 
		_img->setAngle(weaponDegree /*+ _angleOffset*/); // 이미지 각도 
		_img->setAnglePos(Vector2(0.7f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다
		
	}
	else
	{
	
	_imgAttack->setScale(4); // 이미지 크기 
	_imgAttack->setAngle(weaponDegree /*+ _angleOffset*/); // 이미지 각도 
	_imgAttack->setAnglePos(Vector2(0.7f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
	_imgAttack->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);// 그린다
	
	}




	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
	Vector2 renderPosHand2 = renderPosHand;
	renderPosHand2.x -= _width * 0.16f * 4;
	FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다


	if (_drawEffect) // 이펙트를 그린다
	{
		Vector2 effectPos = originPos; // 회전축의 위치로부터
		float length = _width * 4 * 0.5; // 무기 길이만큼
		_drawEffect = false;
		bool isLeft = (player->getDirection() == DIRECTION::LEFT);
		if (!isLeft)
		{
			//degree = degree + 180;
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_EXKATANAFX", effectPos, Vector2(250, 300), degree , isLeft);
		}
		else
		{

			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_EXKATANAFX", effectPos, Vector2(250, 300), -degree+ 180 , isLeft);
		}

	}

}


void PowerKatana::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	_oneAttack = false;
	// 손으로부터 마우스 에임까지의 각도
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x));
	_drawEffect = true;
	_currAttackDelay = _addStat.attackSpeed;
}


void PowerKatana::equip(Player * player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}

