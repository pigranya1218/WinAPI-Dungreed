#include "stdafx.h"
#include "CosmosSword.h"

void CosmosSword::init()
{
	_img = IMAGE_MANAGER->findImage("CosmosSword");
	width = _img->getFrameSize().x;
	height = _img->getFrameSize().y;

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(),_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();

	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	
	_price = 600;

	// 기본 보조옵션
	_addStat.dashDamage = 20;

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

	if (FLOAT_EQUAL(_currAttackDelay, _baseAttackDelay))
	{


		if (_oneAttack)
		{
			_angleOffset += 155;
			_oneAttack = false;

		}
		else
		{
			_angleOffset -= 155;
			_oneAttack = true;
		}



	}
	float ratio = elapsedTime / (_baseAttackDelay * 0.15);
	if (_reverseMove)
	{
		//_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 40 * ratio));  // 이건 무기가 직접움직일때 사용
		//_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 40 * ratio));

	}
	else
	{
		//_attackMove.x = min(abs(cosf(_attackAngle) * 40), _attackMove.x + abs(cosf(_attackAngle) * 40 * ratio));
		//_attackMove.y = min(abs(-sinf(_attackAngle) * 40), _attackMove.y + abs((-sinf(_attackAngle)) * 40 * ratio));

		if (_currAttackDelay <= _baseAttackDelay * 0.8)
		{
			_reverseMove = true;
			_drawEffect = true;
		}
	}
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
		// 플레이어 중점
		originPos.x += ((isLeft) ? -75 : 20);
		originPos.y += (35);


		// 손으로부터 마우스 에임까지의 각도

		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x)) * (180 / PI);
		


		if (degree > 360)
		{
			degree -= 360;
		}

		float renderDegree = degree + ((isLeft)?-90:90);
		if (isLeft)
		{
			renderDegree = 180 - renderDegree;
		}

		// 손 의 각도 
		Vector2 renderPosHand = originPos;
		Vector2 renderPosWeapon = originPos;

		if (isLeft) // 왼쪽을 보고 있음
		{

			renderPosWeapon.x +=  (cosf(renderDegree * (PI / 180)) );//*-(width * 0.1f * 4))
			renderPosWeapon.y += (-sinf(renderDegree * (PI / 180)* 0.5));// *(height * 0.2f * 4);
			renderPosHand.x += (-cosf(renderDegree * (PI / 180))*-(width * 0.2f * 4));
			renderPosHand.y += 20 + (sinf(renderDegree * (PI / 180))) * (height * 0.4f * 4);
		}
		else
		{
			renderPosWeapon.x += 22 + (-cosf(renderDegree * (PI / 180))*-(width * 0.4f * 4));
			renderPosWeapon.y += 20 + (-sinf(renderDegree * (PI / 180))) * (height * 0.8f * 4);
			renderPosHand.x += -cosf(renderDegree * (PI / 180))*-(width * 0.4f * 4);
			renderPosHand.y += 20 + (-sinf(renderDegree * (PI / 180))) * (height * 0.8f * 4);
		}
		// float renderDegree = degreeOffsetangle;

		//if (isLeft) // 왼쪽을 보고 있음
		//{
		//	renderDegree = 360 - degreeOffsetangle;
		//	if (renderDegree < 0) renderDegree += 360;
		//}

		renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		 // 무기의 x좌표
		renderPosWeapon.y += ((renderDegree >= 180) ? (_attackMove.y) : (-_attackMove.y)); // 무기의 y좌표
		renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			 // 손의 x좌표
		renderPosHand.y += ((renderDegree >= 180) ? (_attackMove.y) : (-_attackMove.y));	 // 손의 y좌표

		_img->setScale(4); // 이미지 크기 
		_img->setAngle(renderDegree + _angleOffset); // 이미지 각도 
		if (isLeft) // 왼쪽을 보고 있음
		{
			_img->setAnglePos(Vector2(0.2f * width, 0.5f * height)); // 이미지 회전시킬 중점
		}
		else
		{
			_img->setAnglePos(Vector2(0.3f * width, 0.5f *height)); // 이미지 회전시킬 중점

		}
		 
		_img->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _ani, isLeft);// 그린다
		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		Vector2 last = renderPosHand;

		if (isLeft) // 왼쪽을 보고 있음
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, -(renderDegree), CAMERA->getRelativeV2(last));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, -(renderDegree ), CAMERA->getRelativeV2(last)); // 손의 렉트를 그린다
		}
		else
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (renderDegree), CAMERA->getRelativeV2(last));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (renderDegree ), CAMERA->getRelativeV2(last)); // 손의 렉트를 그린다
		}
		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = pos; // 손의 위치로부터
			float length = width * 4 * 1.3; // 무기 길이만큼
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("CosmosSwordFx", effectPos, Vector2(120, 180), degree);
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
		// 플레이어 중점
		originPos.x += ((isLeft) ? -40 : 20);



		// 손으로부터 마우스 에임까지의 각도

		
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x)) * (180 / PI);
		float degreeOffsetangle = atan2f(-(_ptMouse.y - pos.y), (_ptMouse.x - pos.x)) * (180 / PI) + 90;


		if (degree > 360)
		{
			degree -= 360;
		}
		if (degreeOffsetangle > 360)
		{
			degreeOffsetangle -= 360;
		}
		// 손 의 각도 
		Vector2 renderPosHand = originPos;
		Vector2 renderPosWeapon = originPos;

		if (isLeft) // 왼쪽을 보고 있음
		{

			renderPosWeapon.x +=  (-cosf(degreeOffsetangle * (PI / 180)) * -(width  * 0.1f * 4) ) - 35;
			renderPosWeapon.y +=  (-sinf(degreeOffsetangle * (PI / 180)) *  (height * 0.2f * 4)) + 30 ;
			renderPosHand.x   += 52 + (-cosf(degreeOffsetangle * (PI / 180)) * -(width  * 0.1f * 4)) - 23;
			renderPosHand.y   += 5 + (-sinf(degreeOffsetangle * (PI / 180)) *  (height * 0.4f * 4));
		}
		else
		{
			renderPosWeapon.x -=  (cosf(degreeOffsetangle * (PI / 180)) * -(width  * 0.1f * 4)) -35;
			renderPosWeapon.y += (-sinf(degreeOffsetangle * (PI / 180)) *  (height * 0.4f * 4)) + 30;
			renderPosHand.x -= 42 + (cosf(degreeOffsetangle * (PI / 180)) * -(width  * 0.1f * 4)) - 23;
			renderPosHand.y += 25 + (-sinf(degreeOffsetangle * (PI / 180)) *  (height * 0.4f * 4));
		}
		float renderDegree = degreeOffsetangle;

		if (isLeft) // 왼쪽을 보고 있음
		{
			renderDegree = 360 - degreeOffsetangle;
			if (renderDegree < 0) renderDegree += 360;
		}

		renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		 // 무기의 x좌표
		renderPosWeapon.y += ((degreeOffsetangle >= 180) ? (_attackMove.y) : (-_attackMove.y)); // 무기의 y좌표
		renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			 // 손의 x좌표
		renderPosHand.y += ((degreeOffsetangle >= 180) ? (_attackMove.y) : (-_attackMove.y));	 // 손의 y좌표
		_img->setScale(4); // 이미지 크기 
		_img->setAngle(renderDegree + _angleOffset); // 이미지 각도 
		if (isLeft) // 왼쪽을 보고 있음
		{
			_img->setAnglePos(Vector2(0.2f * width, 0.5f *height)); // 이미지 회전시킬 중점
		}
		else
		{
			_img->setAnglePos(Vector2(0.2f * width, 0.5f *height)); // 이미지 회전시킬 중점

		}
		_img->aniRender(renderPosWeapon, _ani, isLeft);// 그린다 // 그린다

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);

		if (isLeft) // 왼쪽을 보고 있음
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand)); // 손의 렉트를 그린다
		}
		else
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand)); // 손의 렉트를 그린다
		}
		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = pos; // 손의 위치로부터
			float length = width * 4 * 1.3; // 무기 길이만큼
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("CosmosSwordFx", effectPos, Vector2(120, 180), degree);
		}
	}
}

void CosmosSword::displayInfo()
{
}

void CosmosSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;

	// 손으로부터 마우스 에임까지의 각도
	float angle = atan2f(-(_ptMouse.y - renderPosHand.y), (_ptMouse.x - renderPosHand.x));
	_reverseMove = false;
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

PlayerStat CosmosSword::equip()
{
	return PlayerStat();
}
