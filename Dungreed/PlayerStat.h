#pragma once
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
};

