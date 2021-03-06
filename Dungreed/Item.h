#pragma once
#include "Player.h"
#include "ProjectileManager.h"
#include "AttackInfo.h"

enum class ITEM_TYPE : int
{
	WEAPON_ONE_HAND = 0x01000, // 한손 무기
	WEAPON_TWO_HAND = 0x02000, // 양손 무기
	ACC = 0x03000, // 악세사리
	SPECIAL_ABILITY = 0x04000, // 특수 능력
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

	wstring _itemName; // 아이템 이름
	vector<wstring> _displayInfos; // 아이템 능력에 대한 설명
	wstring _displayText; // 아이템 잡담

	// ITEM_TYPE _type; // 아이템 타입
	// ITEM_RANK _rank; // 아이템 등급
	Image* _iconImg; // 아이템 이미지


	int _price; // 가격
	PlayerStat _addStat; // 아이템 스탯 옵션 (플레이어의 스탯에 더해지는 스탯)
	PlayerStat _adjustStat; // 플레이어의 스탯이 반영된 무기 스탯 (현재는 attackSpeed, reloadSpeed만 신경씀)

public:
	virtual void init() {};
	virtual void release() {};
	virtual void update(Player* player, float const elapsedTime) {};
	virtual void backRender(Player* player) {};
	virtual void frontRender(Player* player) {};

	virtual void attack(Player* player) {}; // 플레이어가 공격버튼을 누를때 호출될 함수(공격과 상관없는 아이템이라면 빈 함수로 구현)
	virtual void attack(Player* player, FloatRect* rect, AttackInfo* info) {}; // 공격 렉트를 변경시키는 함수 
	virtual void attack(Player* player, FloatCircle* circle, AttackInfo* info) {}; // 공격 써클을 변경시키는 함수
	virtual void attack(Player* player, Projectile* projectile, AttackInfo* info) {}; // 탄환을 변경시키는 함수

	virtual void dash(Player* player) {}; // 플레이어가 대쉬했을 때
	virtual void reload(Player* player) {}; // 플레이어가 재장전버튼을 눌렀을 때

	virtual bool isHit(Projectile* projectile) { return false; };
	virtual void getHit(Vector2 const position) {}; // 플레이어가 피격되었을 때 호출될 함수(피격과 상관없는 아이템이라면 빈 함수로 구현)

	virtual void equip(Player* player) {}; // 아이템을 장착했을 때 호출될 함수(플레이어 스탯에 비례하여 장비 스탯 변화, 장비 위치 변화 등)
	
	virtual wstring getBulletUI() { return L""; }
	virtual float getBulletRatio() { return 0.f; }

	int getItemCode() const noexcept { return _itemCode; }
	ITEM_TYPE getItemType() const noexcept;
	ITEM_RANK getItemRank() const noexcept;
	int getPrice() const noexcept { return _price; }
	wstring getItemName() const noexcept { return _itemName; }
	vector<wstring> getDisplayInfos() const noexcept { return _displayInfos; }
	wstring getDisplayText() const noexcept { return _displayText; }
	Image* getIconImg() const noexcept { return _iconImg; }
	PlayerStat getAddStat() const noexcept { return _addStat; }
	float getAttackSpeed() { return _adjustStat.attackSpeed; }
	float getReloadSpeed() { return _adjustStat.reloadSpeed; }
	float getMinDamage() { return _addStat.minDamage; }
	float getMaxDamage() { return _addStat.maxDamage; }

};