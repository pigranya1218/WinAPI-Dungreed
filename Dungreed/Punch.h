#pragma once
#include "Item.h"

class Punch : public Item
{
private:
	// 공격 관련
	Image*	_effect;
	int	_minDamage;
	int _maxDamage;
	Vector2 _attackMove;
	float _baseAttackDelay; // 공격 쿨타임
	float _currAttackDelay; // 남은 공격 쿨타임
	float _attackAngle;
	bool _reverseMove;

	// 손 이미지 관련
	FloatRect _leftHand;	// 왼손
	FloatRect _rightHand;	// 오른손
	Vector2 _handSize;		// 손의 크기

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
	virtual void displayInfo(); // 인벤토리에서 보여질 정보들

	virtual void attack(Player* player); // 플레이어가 공격버튼을 누를때 호출될 함수(공격과 상관없는 아이템이라면 빈 함수로 구현)
	virtual void attack(FloatRect* rect, AttackInfo* info); // 공격 렉트를 변경시키는 함수 
	virtual void attack(FloatCircle* circle, AttackInfo* info); // 공격 써클을 변경시키는 함수
	virtual void attack(Projectile* projectile, AttackInfo* info); // 탄환을 변경시키는 함수

	virtual void getHit(Vector2 const position); // 플레이어가 피격되었을 때 호출될 함수(피격과 상관없는 아이템이라면 빈 함수로 구현)

	virtual void equip(Player* player); // 아이템을 장착했을 때 호출될 함수, 스탯이 어떻게 바뀌어야하는지 반환
};

