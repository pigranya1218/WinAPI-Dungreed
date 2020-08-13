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
	TRUE_DAMAGE
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
	float	damage;				// ���� ���ݷ� // ���Ϳ��� ���� ������ = (������ݷ� * (1+����/100))
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

public:
	static string getStatString(STAT_TYPE type, bool isEnglish);

}; 

