#pragma once
#include "Item.h"
class Boomerang :
	public Item
{
private:
	Animation* _ani;
	Image* _img;
	Image* _aniImg;
	Image* _effect01;

	Vector2 _position;
	int _minDamage;
	int _maxDamage;
	int _gunType;				//원거리 무기 타입
	float _angle;
	float _renderDegree;
	float _degree;
	bool _isLeft;
	Vector2 _pos;
	Vector2 _gunPos;
	Vector2 _attackPos;
	bool _isAttack;
	FloatRect _attackRect;
	int _timeCount;
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

	virtual void dash(Player* player) {}; // 플레이어가 대쉬했을 때
	virtual void reload(Player* player) {}; // 플레이어가 재장전버튼을 눌렀을 때
	
	virtual void getHit(Vector2 const position); // 플레이어가 피격되었을 때 호출될 함수(피격과 상관없는 아이템이라면 빈 함수로 구현)

	virtual PlayerStat equip(); // 아이템을 장착했을 때 호출될 함수, 스탯이 어떻게 바뀌어야하는지 반환
	int getGunType() { return _gunType; }
};

