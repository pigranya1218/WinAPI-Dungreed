#include "stdafx.h"
#include "MartialArtOfTiger.h"
void MartialArtOfTiger::init()
{
	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	_effect = IMAGE_MANAGER->findImage("EFFECT_TIGERPUNCH");
	_iconImg =IMAGE_MANAGER->findImage("MartialArtOfTiger");
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

void MartialArtOfTiger::release()
{

}

void MartialArtOfTiger::update(Player* player, float const elapsedTime)
{

	if (_currAttackDelay == 0) return;

	if (FLOAT_EQUAL(_currAttackDelay, _baseAttackDelay))
	{


		



	}
	float ratio = elapsedTime / (_baseAttackDelay * 0.15);
	if (_reverseMove)
	{
		

	}
	else
	{
		

		if (_currAttackDelay <= _baseAttackDelay * 0.8)
		{
			_reverseMove = true;
			_drawEffect = true;
		}
	}

	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void MartialArtOfTiger::backRender(Player* player)
{

}






void MartialArtOfTiger::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x));
	
		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = pos; // 손의 위치로부터
			
			effectPos.x = CAMERA->getAbsoluteX(_ptMouse.x) ;
			effectPos.y = CAMERA->getAbsoluteY(_ptMouse.y);
			EFFECT_MANAGER->play("EFFECT_TIGERPUNCH", effectPos, Vector2(200, 200),0.0f);
		}
	
}

void MartialArtOfTiger::displayInfo()
{
}

void MartialArtOfTiger::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;

	// 손으로부터 마우스 에임까지의 각도
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x));
	_reverseMove = false;
	_currAttackDelay = _baseAttackDelay;
}

void MartialArtOfTiger::attack(FloatRect* rect, AttackInfo* info)
{
}

void MartialArtOfTiger::attack(FloatCircle* circle, AttackInfo* info)
{
}

void MartialArtOfTiger::attack(Projectile* projectile, AttackInfo* info)
{
}

void MartialArtOfTiger::getHit(Vector2 const position)
{
}

PlayerStat MartialArtOfTiger::equip()
{
	return PlayerStat();
}
