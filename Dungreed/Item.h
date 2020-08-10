#pragma once

class Player;

enum class ITEM_TYPE
{
	WEAPON_ONE_HAND, // 한손 무기
	WEAPON_TWO_HAND, // 양손 무기
	ACC // 악세사리
};

enum class ITEM_RANK
{
	NORMAL, // 일반
	HIGH, // 고급
	RARE, // 희귀
	LEGEND // 전설
};

class Item
{
private:
	ITEM_TYPE _type; // 아이템 타입
	ITEM_RANK _rank; // 아이템 등급
	Image* _img; // 아이템 이미지
	int _price; // 가격

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(float const elapsedTime) = 0;
	virtual void render(Vector2 pos, float angle) = 0;
	virtual void displayInfo() = 0; // 인벤토리에서 보여질 정보들

	virtual void attack(Vector2 const position, Vector2 const angle) = 0; // 플레이어가 공격버튼을 누를때 호출될 함수(공격과 상관없는 아이템이라면 빈 함수로 구현)
	virtual void attack(FloatRect* rect, tagAttackInfo* info) = 0; // 공격 렉트를 변경시키는 함수 
	virtual void attack(FloatCircle* circle, tagAttackInfo* info) = 0; // 공격 써클을 변경시키는 함수
	virtual void attack(Projectile* projectile, tagAttackInfo* info) = 0; // 탄환을 변경시키는 함수

	virtual void getHit(Vector2 const position) = 0; // 플레이어가 피격되었을 때 호출될 함수(피격과 상관없는 아이템이라면 빈 함수로 구현)

	virtual void equip(Player& player) = 0; // 아이템을 장착했을 때 호출될 함수, 플레이어의 스탯을 변경
	
	ITEM_TYPE getType() const noexcept { return _type; }

	int getPrice() const noexcept { return _price; }
};