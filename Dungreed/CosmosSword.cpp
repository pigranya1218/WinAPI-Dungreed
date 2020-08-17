#include "stdafx.h"
#include "CosmosSword.h"

void CosmosSword::init()
{
	_img = IMAGE_MANAGER->findImage("CosmosSword");
	_iconImg = IMAGE_MANAGER->findImage("CosmosSwordIcon");

	width = _img->getFrameSize().x;
	height = _img->getFrameSize().y;

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();


	_itemCode = 0x02400;

	_price = 600;

	// 기본 보조옵션
	_addStat.dashDamage = 20;
	_addStat.minDamage = 7;
	_addStat.maxDamage = 10;
	_addStat.attackSpeed = 0.4;

	_handSize = Vector2(5, 5);


	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_minDamage = 7;
	_maxDamage = 10;
	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_angleOffset = 0;

}

void CosmosSword::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void CosmosSword::update(Player* player, float const elapsedTime)
{
	_ani->frameUpdate(elapsedTime);

	if (_currAttackDelay == 0) return;


	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);

}

void CosmosSword::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	if (_oneAttack)
	{
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
		renderPosHand.x += (width * 0.1 * 4);
		// 무기 위치
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft)?(-width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4): (width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4;

		_img->setScale(4); // 이미지 크기 
		_img->setAngle(weaponDegree /*+ _angleOffset*/); // 이미지 각도 
		_img->setAnglePos(Vector2(0.15f * width, 0.5f * height)); // 이미지 회전시킬 중점
		_img->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _ani, isLeft);// 그린다

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다

		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = originPos; // 회전축의 위치로부터
			float length = width * 4 * 1; // 무기 길이만큼
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_COSMOSSWING", effectPos, Vector2(250, 300), degree);
		}
	}
}

void CosmosSword::frontRender(Player* player)
{

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	if (!_oneAttack)
	{
		// 회전축 중점
		originPos.x += ((isLeft) ? -15 : 15); // 바라보는 방향의 어깨
		originPos.y += 10;

		// 회전축으로부터 마우스까지의 각도값
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

		float handDegree = degree + ((isLeft) ? (-110 - _angleOffset) : (110 + _angleOffset));

		// 좌우 대칭을 위한 계산
		float weaponDegree = handDegree;
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;
		}

		// 손의 위치 
		Vector2 renderPosHand = originPos;
		renderPosHand.x += (width * 0.1 * 4);
		// 무기 위치
		Vector2 renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft) ? (-width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4) : (width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * width * 0.15 * 4;

		_img->setScale(4); // 이미지 크기 
		_img->setAngle(weaponDegree /*+ _angleOffset*/); // 이미지 각도 
		_img->setAnglePos(Vector2(0.15f * width, 0.5f * height)); // 이미지 회전시킬 중점
		_img->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _ani, isLeft);// 그린다

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다

		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = originPos; // 회전축의 위치로부터
			float length = width * 4 * 1; // 무기 길이만큼
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_COSMOSSWING", effectPos, Vector2(250, 300), degree);
		}
	}
}

void CosmosSword::displayInfo()
{
}

void CosmosSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	if (_oneAttack)
	{
		_angleOffset += 95;
	}
	else
	{
		_angleOffset -= 95;
	}
	_oneAttack = !_oneAttack;
	
	_drawEffect = true;
	_currAttackDelay = _baseAttackDelay;
}

void CosmosSword::attack(FloatRect* rect, AttackInfo* info)
{
}

void CosmosSword::attack(FloatCircle* circle, AttackInfo* info)
{
}

void CosmosSword::attack(Projectile* projectile, AttackInfo* info)
{
}

void CosmosSword::getHit(Vector2 const position)
{
}

void CosmosSword::equip(Player* player)
{
}
