#pragma once
#include "Player.h"
#include "ProjectileManager.h"
#include "AttackInfo.h"

enum class ITEM_TYPE : int
{
	WEAPON_ONE_HAND = 0x01000, // 한손 무기
	WEAPON_TWO_HAND = 0x02000, // 양손 무기
	ACC = 0x03000, // 악세사리
	WEAPON_SUB = 0x04000, // 보조 무기
	FOOD = 0x05000
};

enum class ITEM_RANK : int
{
	NORMAL = 0x00100, // 일반
	HIGH = 0x00200, // 고급
	RARE = 0x00300, // 희귀
	LEGEND = 0x00400 // 전설
};
//한손 전설 - 0x014xx;
//근거리 0x0xx00~
//원거리 0x0xx60~

class Item
{
protected:
	int _itemCode; // 아이템 코드
	vector<string> _displayInfos; // 아이템 능력에 대한 설명

	// ITEM_TYPE _type; // 아이템 타입
	// ITEM_RANK _rank; // 아이템 등급
	Image* _iconImg; // 아이템 이미지

	
	int _price; // 가격
	PlayerStat _addStat; // 아이템 스탯 옵션
	
	ProjectileManager* _projecttileMng;		//투사체 매니저

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(Player* player, float const elapsedTime) = 0;
	virtual void backRender(Player* player) = 0;
	virtual void frontRender(Player* player) = 0;
	virtual void displayInfo() = 0; // 인벤토리에서 보여질 정보들

	virtual void attack(Player* player) = 0; // 플레이어가 공격버튼을 누를때 호출될 함수(공격과 상관없는 아이템이라면 빈 함수로 구현)
	virtual void attack(FloatRect* rect, AttackInfo* info) = 0; // 공격 렉트를 변경시키는 함수 
	virtual void attack(FloatCircle* circle, AttackInfo* info) = 0; // 공격 써클을 변경시키는 함수
	virtual void attack(Projectile* projectile, AttackInfo* info) = 0; // 탄환을 변경시키는 함수

	virtual void dash(Player* player) {}; // 플레이어가 대쉬했을 때
	virtual void reload(Player* player) {}; // 플레이어가 재장전버튼을 눌렀을 때

	virtual void getHit(Vector2 const position) = 0; // 플레이어가 피격되었을 때 호출될 함수(피격과 상관없는 아이템이라면 빈 함수로 구현)

	virtual void equip(Player* player) const {}; // 아이템을 장착했을 때 호출될 함수
	
	virtual wstring getBulletUI() { return L""; }
	virtual float getBulletRatio() { return 0.f; }

	int getItemCode() const noexcept { return _itemCode; }
	int getPrice() const noexcept { return _price; }
	vector<string> getDisplayInfos() { return _displayInfos; }
	Image* getIconImg() const noexcept { return _iconImg; }
	PlayerStat getAddStat() const noexcept { return _addStat; }
	
};