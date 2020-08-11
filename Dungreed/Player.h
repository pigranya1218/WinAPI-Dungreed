#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "PlayerStat.h"

class Item;
class GameScene;
class Projectile;
class Ability;

// 공격 관련 정보
struct tagAttackInfo
{
	OBJECT_TEAM team;
	int attackID; // 어택 아이디, 공격에 대한 중복검사 판별을 위해서 사용
	float damage; // 대미지
	float knockBack; // 넉백 (밀어내는 힘)
};

class Player : public GameObject
{
Synthesize(DIRECTION, _direction, Direction)

private:
	//애니메이션 재생용 (상태패턴 아님)
	enum class PLAYER_ANIMATION
	{
		DEFAULT,		//점프나 사망과 같이 애니렌더를 사용하지 않는 경우.
		IDLE,
		MOVE		//점프 중이 아닌 경우에만
	};

private:
	GameScene* _gameScene;
	Animation* _ani;	
	Image* _img;	
	PLAYER_ANIMATION _aniState;

	// 현재 상태
	int		_level;					// 현재 레벨
	int		_currHp;				// 현재 체력
	int		_currJumpCount;			// 현재 남은 점프 카운트
	int		_currDashCount;			// 현재 남은 대쉬 카운트
	float	_currDashCoolTime;		// 현재 대쉬 쿨타임
	int		_currSatiety;			// 현재 포만감
	int		_currGold;				// 현재 골드
	
	Vector2 _force;				// 현재 캐릭터에 가해지는 힘

	PlayerStat _baseStat; // 기본 스탯, 아이템으로 변하지 않는 스탯
	PlayerStat _adjustStat; // 아이템으로 변화된 스탯

	vector<Item*> _inventory;				// 인벤토리
	vector<Item*> _equippedWeapon;			// 장착된 무기
	int			  _currWeaponIndex;			// 현재 사용하는 무기 인덱스, 0 or 1
	float		  _currWeaponChangeCoolTime;// 무기 교체 딜레이 쿨타임
	vector<Item*> _equippedAcc;				// 장착된 악세사리

private:
	void setBaseStat();
	void updateAdjustStat();

public:
	Player() {};
	~Player() {};

	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; };

	void setAni(PLAYER_ANIMATION setAni);

	// 아이템들이 호출할 함수들
	void attack(FloatRect* rect, tagAttackInfo* info);
	void attack(FloatCircle* circle, tagAttackInfo* info);
	void attack(Projectile* projectile, tagAttackInfo* info);

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
};

