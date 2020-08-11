#pragma once
class PlayerStat
{
public:
	// 스탯 정보
	int		maxHp;				// 최대 체력
	int		maxJumpCount;		// 최대 점프 횟수
	int		maxDashCount;		// 최대 대쉬 횟수
	float	maxSatiety;			// 최대 포만감
	float	power;				// 위력 (위력 수치 1당 피해량 1% 상승)
	float	damage;				// 무기 공격력 // 몬스터에게 들어가는 데미지 = (무기공격력 * (1+위력/100))
	float	trueDamage;			// 고정 데미지
	float	criticalChance;		// 크리티컬 확률
	float	criticalDamage;		// 크리티컬 데미지
	float	dashDamage;			// 대쉬 공격력
	float	toughness;			// 강인함
	float	defense;			// 방어력
	float	block;				// 막기
	float	evasion;			// 회피
	float	attackSpeed;		// 공격속도
	float	moveSpeed;			// 이동속도
	float	dashXPower;			// 대시 x 속도
	float	dashYPower;			// 대시 y 속도
	float	jumpPower;			// 점프 파워
	float	xGravity;			// x 저항
	float	yGravity;			// y 저항

public:
	PlayerStat operator+(const PlayerStat& a);
};

