#pragma once
#include "Item.h"
#include "NormalProjectile.h"

class MagicStick : public Item
{
private:
	Image* _img;

	Image* _reloadEffect;
	Animation* _reloadAni;

	float _currAttackDelay; // 남은 공격 쿨타임
	int _maxBullet; // 최대 총알 갯수
	int _currBullet; // 현재 총알 갯수
	float _currReloadDelay; // 남은 재장전 쿨타임
	bool _drawEffect; // 이번 render 함수에서 이펙트를 시작할 것인지 판단
	bool _oneAttack;
	NormalProjectile* projectile;
	Vector2 renderPosWeapon;
	Vector2 _attackMove;
	float _width;
	float _height;
	FloatRect _hand;
	Vector2 _handSize;
	float _angleOffset;
public:
	virtual void init() override;
	virtual void release() override;
	virtual void update(Player* player, float const elapsedTime) override;
	virtual void backRender(Player* player) override;
	virtual void frontRender(Player* player) override;
	virtual void displayInfo(); // 인벤토리에서 보여질 정보들

	virtual void attack(Player* player) override; // 플레이어가 공격버튼을 누를때 호출될 함수(공격과 상관없는 아이템이라면 빈 함수로 구현)
	virtual void attack(Player* player, FloatRect* rect, AttackInfo* info) override; // 공격 렉트를 변경시키는 함수 
	virtual void attack(Player* player, FloatCircle* circle, AttackInfo* info) override; // 공격 써클을 변경시키는 함수
	virtual void attack(Player* player, Projectile* projectile, AttackInfo* info) override; // 탄환을 변경시키는 함수

	virtual void reload(Player* player) override; // 재장전 버튼을 누를때 호출될 함수
	virtual void getHit(Vector2 const position) override; // 플레이어가 피격되었을 때 호출될 함수(피격과 상관없는 아이템이라면 빈 함수로 구현)

	virtual void equip(Player* player) override; // 아이템을 장착했을 때 호출될 함수, 스탯이 어떻게 바뀌어야하는지 반환

	virtual wstring getBulletUI() override;
	virtual float getBulletRatio() override;
};

