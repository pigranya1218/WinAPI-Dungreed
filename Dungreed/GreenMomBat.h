#pragma once
#include "Item.h"
class GreenMomBat : public Item
{
private:
	Image* _img;
	Animation* _ani;


	Vector2 _renderPos;
	Vector2 _batPos;

	DIRECTION _direction;

	float _baseAttackDelay;   // 공격 쿨타임
	float _currAttackDelay;   // 남은 공격 쿨타임
	int _maxBullet;           // 최대 총알 갯수
	int _currBullet;          // 현재 총알 갯수
	float _baseReloadDelay;   // 재장전 쿨타임
	float _currReloadDelay;   // 남은 재장전 쿨타임
	bool _drawEffect;         // 이번 render 함수에서 이펙트를 시작할 것인지 판단

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);

	virtual void attack(Player* player)override; // 플레이어가 공격버튼을 누를때 호출될 함수(공격과 상관없는 아이템이라면 빈 함수로 구현)
	
};

