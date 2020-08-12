#pragma once
#include "Item.h"
#include "PlayerBullet.h"

class MatchLockGun : public Item
{
private:

	Image* _shootEffect;
	Image* _dustEffect;
	Animation* _effectAni01;
	Animation* _effectAni02;

	int _minDamage;
	int _maxDamage;
	int _gunType;				//원거리 무기 타입
	float _angle;
	bool _isLeft;
	Vector2 _gunPos;

	bool _isAttack;

	//GunBullet* _bullet;
	PlayerBullet* _bullet;

	Vector2 _attackMove;
	float _baseAttackDelay; // 공격 쿨타임
	float _currAttackDelay; // 남은 공격 쿨타임
	float _attackAngle;
	bool _reverseMove;
	bool _drawEffect;
	FloatRect _hand;
	Vector2 _handSize;
public:

	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
	virtual void displayInfo(); // 인벤토리에서 보여질 정보들

	virtual void attack(Player* player); // 플레이어가 공격버튼을 누를때 호출될 함수(공격과 상관없는 아이템이라면 빈 함수로 구현)
	virtual void attack(FloatRect* rect, tagAttackInfo* info); // 공격 렉트를 변경시키는 함수 
	virtual void attack(FloatCircle* circle, tagAttackInfo* info); // 공격 써클을 변경시키는 함수
	virtual void attack(Projectile* projectile, tagAttackInfo* info); // 탄환을 변경시키는 함수

	virtual void getHit(Vector2 const position); // 플레이어가 피격되었을 때 호출될 함수(피격과 상관없는 아이템이라면 빈 함수로 구현)

	virtual PlayerStat equip(); // 아이템을 장착했을 때 호출될 함수, 스탯이 어떻게 바뀌어야하는지 반환
	int getGunType() { return _gunType; }
};

