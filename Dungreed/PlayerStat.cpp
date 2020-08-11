#include "stdafx.h"
#include "PlayerStat.h"

PlayerStat PlayerStat::operator+(const PlayerStat& a)
{
	PlayerStat result = *this;
	result.maxHp += a.maxHp;
	result.maxJumpCount += a.maxJumpCount;
	result.maxDashCount += a.maxDashCount;
	result.maxSatiety += a.maxSatiety;
	result.power += a.power;
	result.damage += a.damage;
	result.trueDamage += a.trueDamage;
	result.criticalChance += a.criticalChance;
	result.criticalDamage += a.criticalDamage;
	result.dashDamage += a.dashDamage;
	result.toughness += a.toughness;
	result.defense += a.defense;
	result.block += a.block;
	result.evasion += a.evasion;
	result.attackSpeed += a.attackSpeed;
	result.moveSpeed += a.moveSpeed;
	result.dashXPower += a.dashXPower;
	result.dashYPower += a.dashYPower;
	result.jumpPower += a.jumpPower;
	result.xGravity += a.xGravity;
	result.yGravity += a.yGravity;

	return result;
}
