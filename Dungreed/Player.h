#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "PlayerStat.h"
#include "AttackInfo.h"

class Item;
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

	int		_level;					// 현재 레벨
	int		_currHp;				// 현재 체력
	int		_currJumpCount;			// 현재 남은 점프 카운트
	int		_currDashCount;			// 현재 남은 대쉬 카운트
	float	_currDashCoolTime;		// 현재 대쉬 쿨타임
	int		_currSatiety;			// 현재 포만감
	int		_currGold;				// 현재 골드
	
	Vector2 _force;				// 현재 캐릭터에 가해지는 힘

	PlayerStat _adjustStat; // 각종 요인으로 변화된 최종 스탯

	vector<Item*> _inventory;				// 인벤토리
	vector<Item*> _equippedWeapon;			// 장착된 무기
	int			  _currWeaponIndex;			// 현재 사용하는 무기 인덱스, 0 or 1
	float		  _currWeaponChangeCoolTime;// 무기 교체 딜레이 쿨타임
	vector<Item*> _equippedAcc;				// 장착된 악세사리

private:
	void updateAdjustStat();

public:
	Player() {};
	~Player() {};

	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; };

	// 아이템들이 호출할 함수들
	void attack(FloatRect* rect, AttackInfo* info);
	void attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	virtual void init() override;
	virtual void release() override;
	virtual void update(float const elapsedTime) override;
	virtual void render() override;

	// GETTER & SETTER
	int getLevel() const noexcept { return _level; }
	int getMaxHp() const noexcept { return _adjustStat.maxHp; }
	int getCurrHp() const noexcept { return _currHp; }

	int getGold() const noexcept { return _currGold; }
	int getMaxSatiety() const noexcept { return _adjustStat.maxSatiety; }
	int getSatiety() const noexcept { return _currSatiety; }

	int getMaxDash() const noexcept { return _adjustStat.maxDashCount; }
	int getCurrDash() const noexcept { return _currDashCount; }

	int getWeaponIndex() const noexcept { return _currWeaponIndex; }
	Image* getWeaponImg(int index) const noexcept;
};

