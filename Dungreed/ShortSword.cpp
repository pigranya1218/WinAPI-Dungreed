#include "stdafx.h"
#include "ShortSword.h"

void ShortSword::init()
{

	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	_iconImg = _img = IMAGE_MANAGER->findImage("ShortSword");
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
	_angleOffset = 15;

}

void ShortSword::release()
{
}

void ShortSword::update(Player* player, float const elapsedTime)
{

	if (_currAttackDelay == 0) return;

	if (FLOAT_EQUAL(_currAttackDelay, _baseAttackDelay))
	{
		

		if (_oneAttack)
		{
			_angleOffset += 180;
			_oneAttack = false;

		}
		else 
		{
			_angleOffset -= 180;
			_oneAttack = true;
		}
		


	}
	

	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void ShortSword::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 Pos = player->getPosition();
	if (_oneAttack)
	{	
		// 플레이어 중점
		originPos.x += ((isLeft) ? -20 : 20); 
		
		
	
	// 손으로부터 마우스 에임까지의 각도
		
			float degree = atan2f(-(_ptMouse.y - Pos.y), (_ptMouse.x - Pos.x)) * (180 / PI) +90;
		
		
	if (degree >360)
	{
		degree -= 360;
	} 
	// 손 의 각도 
	Vector2 renderPosHand = originPos;
	Vector2 renderPosWeapon = originPos;

	if (isLeft) // 왼쪽을 보고 있음
	{

		renderPosWeapon.x -= 22 -  ( cosf(degree * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
		renderPosWeapon.y += 20 + (sinf(degree * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
		renderPosHand.x -=    (-cosf(degree * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
		renderPosHand.y +=  20 +  ( sinf(degree * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
	}
	else
	{
		renderPosWeapon.x += 22 + (-cosf(degree * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
		renderPosWeapon.y += 20 +  (-sinf(degree * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
		renderPosHand.x += -cosf(degree * (PI / 180))*-(_img->getWidth() * 0.4f * 4);
		renderPosHand.y += 20 +  (-sinf(degree * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
	}
	float renderDegree = degree;

	if (isLeft) // 왼쪽을 보고 있음
	{
		renderDegree =360 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}

	renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		 // 무기의 x좌표
	renderPosWeapon.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y)); // 무기의 y좌표
	renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			 // 손의 x좌표
	renderPosHand.y += ((degree >=180) ? (_attackMove.y) : (-_attackMove.y));	 // 손의 y좌표

	_img->setScale(4); // 이미지 크기 
	_img->setAngle(renderDegree + _angleOffset); // 이미지 각도 
	if (isLeft) // 왼쪽을 보고 있음
	{
		_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight())); // 이미지 회전시킬 중점
	}
	else
	{
		_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight())); // 이미지 회전시킬 중점

	}
	_img->render(renderPosWeapon, isLeft); // 그린다
	
	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
	Vector2 last = renderPosHand;
	if (isLeft) // 왼쪽을 보고 있음
	{
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, -(renderDegree + _angleOffset), last) ; // 손의 렉트를 그린다
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, -(renderDegree + _angleOffset), last);
	}
	else
	{
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, (renderDegree + _angleOffset), last); // 손의 렉트를 그린다
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, (renderDegree + _angleOffset), last);
	}
	if (_drawEffect) // 이펙트를 그린다
	{
		_drawEffect = false;
		Vector2 effectPos = renderPosHand; // 손의 위치로부터
		float length = _img->getWidth() * 4 * 0.7; // 무기 길이만큼
		effectPos.x += cosf(degree * (PI / 180)) * length;
		effectPos.y += -sinf(degree * (PI / 180)) * length;	
		EFFECT_MANAGER->play("EFFECT_SWING", effectPos, Vector2(35, 35), degree);
	}
	}
}

void ShortSword::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 Pos = player->getPosition();
	if (isLeft)
	{
		Vector2 renderPos = Vector2(originPos.x + 25, originPos.y + 20);

		_hand = rectMakePivot(renderPos, _handSize, PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1, 6.f);
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1);
	}
	else
	{
		Vector2 renderPos = Vector2(originPos.x - 25, originPos.y + 20);

		_hand = rectMakePivot(renderPos, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1, 6.f);
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1);
	}
	if (!_oneAttack)
	{
		// 플레이어 중점
		originPos.x += ((isLeft) ? -40 : 20);



		// 손으로부터 마우스 에임까지의 각도

		float degree = atan2f(-(_ptMouse.y - Pos.y), (_ptMouse.x - Pos.x)) * (180 / PI) + 90;


		if (degree > 360)
		{
			degree -= 360;
		}
		// 손 의 각도 
		Vector2 renderPosHand = originPos;
		Vector2 renderPosWeapon = originPos;

		if (isLeft) // 왼쪽을 보고 있음
		{

			renderPosWeapon.x +=	5+	  (-cosf(degree * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4))   ;
			renderPosWeapon.y +=    5+    (-sinf(degree * (PI / 180)) *  (_img->getHeight() * 0.4f * 4))   ;
			renderPosHand.x   +=   52+    (-cosf(degree * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4))-23 ;
			renderPosHand.y   +=    5+    (-sinf(degree * (PI / 180)) *  (_img->getHeight() * 0.4f * 4))   ;
		}
		else
		{
			renderPosWeapon.x -=   5+  (cosf(degree * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4));
			renderPosWeapon.y +=   5+   (-sinf(degree * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
			renderPosHand.x -=     52 + (cosf(degree * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4)) -23 ;
			renderPosHand.y +=     5+  (-sinf(degree * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
		}
		float renderDegree = degree;

		if (isLeft) // 왼쪽을 보고 있음
		{
			renderDegree = 360 - degree;
			if (renderDegree < 0) renderDegree += 360;
		}

		renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		 // 무기의 x좌표
		renderPosWeapon.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y)); // 무기의 y좌표
		renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			 // 손의 x좌표
		renderPosHand.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));	 // 손의 y좌표

		_img->setScale(4); // 이미지 크기 
		_img->setAngle(renderDegree + _angleOffset); // 이미지 각도 
		if (isLeft) // 왼쪽을 보고 있음
		{
			_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight())); // 이미지 회전시킬 중점
		}
		else
		{
			_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight())); // 이미지 회전시킬 중점

		}
		_img->render(renderPosWeapon, isLeft); // 그린다

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		Vector2 last = renderPosHand;
		if (isLeft) // 왼쪽을 보고 있음
		{
			D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, -(renderDegree + _angleOffset), last); // 손의 렉트를 그린다
			D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, -(renderDegree + _angleOffset), last);
		}
		else
		{
			D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, (renderDegree + _angleOffset), last); // 손의 렉트를 그린다
			D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1, (renderDegree + _angleOffset), last);
		}
		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = renderPosHand; // 손의 위치로부터
			float length = _img->getWidth() * 4 * 0.7; // 무기 길이만큼
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_SWING", effectPos, Vector2(35, 35), degree);
		}
	}
}

void ShortSword::displayInfo()
{
}

void ShortSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? -(_img->getWidth() * 0.15f * 4) : (_img->getWidth() * 0.15f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 20; // 플레이어의 중점으로부터 무기를 들고 있는 높이
	// 손으로부터 마우스 에임까지의 각도
	float angle = atan2f(-(_ptMouse.y - renderPosHand.y), (_ptMouse.x - renderPosHand.x)) + PI2;
	if (angle > PI2)
	{
		angle -= PI2;
	}

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _baseAttackDelay;
}

void ShortSword::attack(FloatRect* rect, AttackInfo* info)
{
}

void ShortSword::attack(FloatCircle* circle, AttackInfo* info)
{
}

void ShortSword::attack(Projectile* projectile, AttackInfo* info)
{
}

void ShortSword::getHit(Vector2 const position)
{
}

PlayerStat ShortSword::equip()
{
	return PlayerStat();
}
