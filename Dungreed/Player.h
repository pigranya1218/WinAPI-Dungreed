#pragma once
#include "GameObject.h"

class TestScene;

//애니메이션 재생용 (상태패턴 아님)
enum class PLAYER_ANIMATION
{
	DEFAULT,		//점프나 사망과 같이 애니렌더를 사용하지 않는 경우.
	IDLE,		
	MOVE		//점프 중이 아닌 경우에만
	// JUMP		//점프 중일 때도 좌 우 이동은 가능하지만 점프 상태는 그대로
	// DIE		//사망
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
	TestScene* _testScene;
	Animation* _ani;
	Image* _img;
	Image* _weapon;
	PLAYER_ANIMATION _aniState;

	// 현재 상태
	int		_currHp;			// 현재 체력
	int		_jumpCount;			// 현재 남은 점프 카운트
	
	Vector2 _force;				// 현재 캐릭터에 가해지는 힘

	const float	_dashPower = 20;	// 대쉬파워
	const float	_jumpPower = 20;	// 점프파워
	float	_xGravity;				// 대쉬 저항
	float	_yGravity;				// 점프 저항
	
	bool	_isJump;				// 점프 처리 (지면과 떨어진 상태)
	bool	_isAttack;				// 마우스 좌클릭시 공격
	tagStat _stat; // 스탯
	FloatRect _leftHand; // 왼손 
	FloatRect _rightHand; // 오른손

public:
	Player() {};
	~Player() {};

	void move(Vector2 force);
	void setAni(PLAYER_ANIMATION setAni);

	void init();
	void release();
	void update();
	void render();
	void attack();

	void setTestScene(TestScene* testScene) { _testScene = testScene; }
};

