#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Item;
class GameScene;
class Projectile;

//애니메이션 재생용 (상태패턴 아님)
enum class PLAYER_ANIMATION
{
	DEFAULT,		//점프나 사망과 같이 애니렌더를 사용하지 않는 경우.
	IDLE,		
	MOVE		//점프 중이 아닌 경우에만
	// JUMP		//점프 중일 때도 좌 우 이동은 가능하지만 점프 상태는 그대로
	// DIE		//사망
};

// 공격 관련 정보
struct tagAttackInfo
{
	OBJECT_TEAM team;
	int attackID; // 어택 아이디, 공격에 대한 중복검사 판별을 위해서 사용
	float damage; // 대미지
	float knockBack; // 넉백 (밀어내는 힘)
};

struct tagStat
{
	// 스탯 정보
	int		_maxJumpCount;		// 최대 점프 횟수
	int		_maxHp;				// 최대 체력
	int		_maxDashCount;		// 최대 대쉬 횟수
	float	_satiety;			// 포만감
	float	_power;				// 위력 (위력 수치 1당 피해량 1% 상승)
	float	_damage;			// 무기 공격력 // 몬스터에게 들어가는 데미지 = (무기공격력 * (1+위력/100))
	float	_trueDamage;		// 고정 데미지
	float	_criticalChance;	// 크리티컬 확률
	float	_criticalDamage;	// 크리티컬 데미지
	float	_dashDamage;		// 대쉬 공격력
	float	_toughness;			// 강인함
	float	_defense;			// 방어력
	float	_block;				// 막기
	float	_evasion;			// 회피
	float	_attackSpeed;		// 공격속도
	float	_moveSpeed;			// 이동속도
};

class Player : public GameObject
{
Synthesize(DIRECTION, _direction, Direction)

private:
	GameScene* _gameScene;
	Animation* _ani;
	Image* _img;
	PLAYER_ANIMATION _aniState;

	// 현재 상태
	int		_currHp;			// 현재 체력
	int		_jumpCount;			// 현재 남은 점프 카운트
	
	Vector2 _force;				// 현재 캐릭터에 가해지는 힘

	float	_dashPower = 1100;	// 대쉬파워
	float	_jumpPower = 800;	// 점프파워
	float	_xGravity = 2000;	// x 저항
	float	_yGravity = 1600;	// y 저항
	
	bool	_isLanded;			// 공중에 떠있는지 판단하는 불 변수

	tagStat _baseStat; // 기본 스탯, 아이템으로 변하지 않는 스탯
	tagStat _adjustStat; // 아이템으로 변화된 스탯

	vector<Item*> _inventory; // 인벤토리
	vector<Item*> _equippedWeapon; // 장착된 무기
	int _currWeaponIndex; // 현재 사용하는 무기 인덱스, 0 or 1
	vector<Item*> _equippedAcc; // 장착된 악세사리

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
};

