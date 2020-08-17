#pragma once
#include "stdafx.h"

enum class STAT_TYPE : int
{
	POW = 0,
	DEF,
	TOUGH,
	BLOCK,
	CRITICAL,
	CRITICAL_DAMAGE,
	EVADE,
	MOVE_SPEED,
	ATTACK_SPEED,
	RELOAD,
	DASH_DAMAGE,
	TRUE_DAMAGE,
	MIN_DAMAGE,
	MAX_DAMAGE,
	//�߰�
	MAX_HP,
	MAX_JUMP_COUNT,
	MAX_DASH_COUNT,
	MAX_SATIETY
	END
};

class PlayerStat
{
public:
	// ���� ����
	int		maxHp;				// �ִ� ü��
	int		maxJumpCount;		// �ִ� ���� Ƚ��
	int		maxDashCount;		// �ִ� �뽬 Ƚ��
	int		maxSatiety;			// �ִ� ������
	float	dashCoolTime;		// �뽬 ��Ÿ��
	float	power;				// ���� (���� ��ġ 1�� ���ط� 1% ���)
	float	minDamage;			// �ּ� ���� ���ݷ� // ���Ϳ��� ���� ������ = (������ݷ� * (1+����/100))
	float	maxDamage;			// �ִ� ���� ���ݷ� // ���Ϳ��� ���� ������ = (������ݷ� * (1+����/100))
	float	trueDamage;			// ���� ������
	float	criticalChance;		// ũ��Ƽ�� Ȯ��
	float	criticalDamage;		// ũ��Ƽ�� ������
	float	dashDamage;			// �뽬 ���ݷ�
	float	toughness;			// ������
	float	defense;			// ����
	float	block;				// ����
	float	evasion;			// ȸ��
	float	attackSpeed;		// ���ݼӵ�
	float	moveSpeed;			// �̵��ӵ�
	float	reloadSpeed;		// �������ӵ�
	float	dashXPower;			// ��� x �ӵ�
	float	dashYPower;			// ��� y �ӵ�
	float	jumpPower;			// ���� �Ŀ�
	float	xGravity;			// x ����
	float	yGravity;			// y ����

public:
	PlayerStat operator+(const PlayerStat& a);
	float getStat(STAT_TYPE type);

public:
	static string getStatString(STAT_TYPE type, bool isEnglish);
	static string getStatInfo(STAT_TYPE type);

}; 

