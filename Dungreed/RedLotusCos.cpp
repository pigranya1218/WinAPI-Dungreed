#include "RedLotusCos.h"

void RedLotusCos::init()
{
	//�ڽ�Ƭ �̸� ����
	_costumeName = "RED_LOTUS";

	//�ڽ�Ƭ ����â�� ������ �����
	_costumeTitle = L"ȫ��";
	_costumeSummary = L"�� �ʸӷ�...��ȭ�ϰ� ���� ������, �״�?";

	_ani = new Animation;

	//���� ����� �̹���
	setSprite(PLAYER_STATE::IDLE, true);

	//���� ����
	_differStat.maxHp = -15;
	_differStat.evasion = 25;

	//���̽� ����
	_baseStat.maxHp = 80;
	_baseStat.maxJumpCount = 1;
	_baseStat.maxDashCount = 5;
	_baseStat.dashCoolTime = 1.5f;
	_baseStat.maxSatiety = 100;
	_baseStat.power = 0;
	_baseStat.minDamage = 0; //0 ~ 4
	_baseStat.maxDamage = 0; //0 ~ 4
	_baseStat.trueDamage = 0;
	_baseStat.criticalChance = 10;
	_baseStat.criticalDamage = 100; // + 100%
	_baseStat.toughness = 0;
	_baseStat.defense = 0;
	_baseStat.block = 0;
	_baseStat.evasion = 0;
	_baseStat.attackSpeed = 0;
	_baseStat.reloadSpeed = 0; // --
	_baseStat.moveSpeed = 350;
	_baseStat.dashXPower = 1700;
	_baseStat.dashYPower = 1500;
	_baseStat.jumpPower = 1400;
	_baseStat.xGravity = 4000;
	_baseStat.yGravity = 4000;
}

