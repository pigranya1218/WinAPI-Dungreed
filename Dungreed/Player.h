#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "PlayerStat.h"
#include "AttackInfo.h"

class Item;
class Food;
class GameScene;
class Projectile;
class Ability;
class Costume;

class Player : public GameObject
{
Synthesize(DIRECTION, _direction, Direction)

private:
	GameScene* _gameScene;

	// 현재 상태
	Costume* _costume;				// 현재 장착한 코스튬
	vector<size_t>		_attackedId; // 최근 공격받았던 공격들의 아이디 값들을 저장하는 벡터, 최대 10칸 정도 저장하면 적당할 듯

	int		_level;					// 현재 레벨
	int		_currHp;				// 현재 체력
	int		_currJumpCount;			// 현재 남은 점프 카운트
	int		_currDashCount;			// 현재 남은 대쉬 카운트
	float	_currDashCoolTime;		// 현재 대쉬 쿨타임
	float	_currDashTime;			// 현재 대쉬 남은 유지시간
	float	_currEffectTime;		// 현재 대쉬 이펙트 체크 시간
	int		_currSatiety;			// 현재 포만감
	int		_currGold;				// 현재 골드
	
	float	_walkEffectDelay = 0;

	float	_currHitTime;			// 피격 타임
	
	Vector2 _force;				// 현재 캐릭터에 가해지는 힘
	
	PlayerStat _abilityStat;// 어빌리티 추가 스탯
	PlayerStat _adjustStat; // 각종 요인으로 변화된 최종 스탯

	Item*		_hand; // 주먹질
	vector<Item*> _inventory;				// 인벤토리
	vector<Item*> _equippedWeapon;			// 장착된 무기
	int			  _currWeaponIndex;			// 현재 사용하는 무기 인덱스, 0 or 1
	float		  _currWeaponChangeCoolTime;// 무기 교체 딜레이 쿨타임
	vector<Item*> _equippedAcc;				// 장착된 악세사리
	vector<Item*> _specialAbility;
	vector<Food*> _ateFood;					// 먹은 음식들

	Animation* _dashEffectAni;				// 대쉬할 때 먼지날리는 이펙트 애니메이션

private:
	void swap(Item* &a, Item* &b);

public:
	Player() {};
	~Player() {};

	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; };

	// 아이템들이 호출할 함수들
	bool attack(FloatRect* rect, AttackInfo* info);
	bool attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	virtual void init() override;
	virtual void release() override;
	virtual void update(float const elapsedTime) override;
	virtual void render() override;

	// 피격 체크를 위해 호출
	bool isHit(FloatRect* rc, AttackInfo* info);
	bool isHit(FloatCircle* circle, AttackInfo* info);
	bool isHit(Projectile* projectile, bool isOnceCollision);

	// 만약 피격되었다면 호출될 가상함수
	bool hitEffect(FloatRect* rc, AttackInfo* info);
	bool hitEffect(FloatCircle* circle, AttackInfo* info);
	bool hitEffect(Projectile* projectile);

	// GETTER & SETTER
	int getLevel() const noexcept { return _level; }
	int getMaxHp() const noexcept { return _adjustStat.maxHp; }
	int getCurrHp() const noexcept { return _currHp; }
	void setCurrHp(int hp) { _currHp = max(0, min(_adjustStat.maxHp, hp)); }

	int getGold() const noexcept { return _currGold; }
	void setGold(int gold) { _currGold = max(0, gold); }
	int getMaxSatiety() const noexcept { return _adjustStat.maxSatiety; }
	int getSatiety() const noexcept { return _currSatiety; }
	void setSatiety(int satiety) { _currSatiety = max(0, satiety); }

	int getMaxDash() const noexcept { return _adjustStat.maxDashCount; }
	int getCurrDash() const noexcept { return _currDashCount; }

	int getWeaponIndex() const noexcept { return _currWeaponIndex; }
	Item* getWeapon(int index) const { return _equippedWeapon[index]; };
	Item* getAcc(int index) const { return _equippedAcc[index]; }
	Item* getInvenItem(int index) const { return _inventory[index]; }
	Image* getWeaponImg(int index) const;

	void equipItem(int index);		// 인벤토리에 있던 아이템을 장착함
	void unequipWeapon(int index);	// 무기 장착중이던 아이템을 해제함
	void unequipAcc(int index);		// 악세사리 장착중이던 아이템을 해제함
	void swapItem(int indexA, int indexB);
	bool collisionItem(Item* item);

	bool ateFood(Food* food); // true면 먹었음, false면 먹지 못했음

	PlayerStat getCurrStat() { return _adjustStat; };
	void setAbilityStat(PlayerStat abilityStat) { _abilityStat = abilityStat; updateAdjustStat(); _currHp = _adjustStat.maxHp; }	// 어빌리티 스탯 설정자
	void setSpecialAbility(vector<Item*> specialAbility);

	Costume* getCurrCostume() { return _costume; }
	void setCurrCostume(Costume* costume);
	float getAttackSpeed();
	float getReloadSpeed();
	float getMinDamage();
	float getMaxDamage();

	// 스테이지 관련 함수
	Vector2 getEnemyPos(Vector2 pos);
	vector<FloatRect> getEnemyRects();
	void moveRoom(Vector2 dir);

	void updateAdjustStat();

	void sellItem(int index);
	bool buyItem(Item* item); // 구매에 성공하면 true 반환
};

