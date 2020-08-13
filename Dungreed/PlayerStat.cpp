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

float PlayerStat::getStat(STAT_TYPE type)
{
	switch (type)
	{
	case STAT_TYPE::POW:
		return power;
	case STAT_TYPE::DEF:
		return defense;
	case STAT_TYPE::TOUGH:
		return toughness;
	case STAT_TYPE::BLOCK:
		return block;
	case STAT_TYPE::CRITICAL:
		return criticalChance;
	case STAT_TYPE::CRITICAL_DAMAGE:
		return criticalDamage;
	case STAT_TYPE::EVADE:
		return evasion;
	case STAT_TYPE::MOVE_SPEED:
		return moveSpeed;
	case STAT_TYPE::ATTACK_SPEED:
		return attackSpeed;
	case STAT_TYPE::RELOAD:
		return reloadSpeed;
	case STAT_TYPE::DASH_DAMAGE:
		return dashDamage;
	case STAT_TYPE::TRUE_DAMAGE:
		return trueDamage;
	}
}

string PlayerStat::getStatString(STAT_TYPE type, bool isEnglish)
{
	switch (type)
	{
	case STAT_TYPE::POW:
		if(isEnglish) return "UI/STAT/POW";
		else return "(무기공격력)위력";
		break;
	case STAT_TYPE::DEF:
		if (isEnglish) return "UI/STAT/DEF";
		else return "방어력";
		break;
	case STAT_TYPE::TOUGH:
		if (isEnglish) return "UI/STAT/TOUGH";
		else return "강인함";
		break;
	case STAT_TYPE::BLOCK:
		if (isEnglish) return "UI/STAT/BLOCK";
		else return "막기";
		break;
	case STAT_TYPE::CRITICAL:
		if (isEnglish) return "UI/STAT/CRITICAL";
		else return "크리티컬";
		break;
	case STAT_TYPE::CRITICAL_DAMAGE:
		if (isEnglish) return "UI/STAT/CRITICAL_DAMAGE";
		else return "크리티컬 데미지";
		break;
	case STAT_TYPE::EVADE:
		if (isEnglish) return "UI/STAT/EVADE";
		else return "회피";
		break;
	case STAT_TYPE::MOVE_SPEED:
		if (isEnglish) return "UI/STAT/MOVE_SPEED";
		else return "이동속도";
		break;
	case STAT_TYPE::ATTACK_SPEED:
		if (isEnglish) return "UI/STAT/ATTACK_SPEED";
		else return "공격속도";
		break;
	case STAT_TYPE::RELOAD:
		if (isEnglish) return "UI/STAT/RELOAD";
		else return "재장전속도";
		break;
	case STAT_TYPE::DASH_DAMAGE:
		if (isEnglish) return "UI/STAT/DASH_DAMAGE";
		else return "대쉬 공격력";
		break;
	case STAT_TYPE::TRUE_DAMAGE:
		if (isEnglish) return "UI/STAT/TRUE_DAMAGE";
		else return "고정 데미지";
		break;
	}
}