#include "PlayerStat.h"

PlayerStat PlayerStat::operator+(const PlayerStat& a)
{
	PlayerStat result = *this;
	result.maxHp += a.maxHp;
	result.maxJumpCount += a.maxJumpCount;
	result.maxDashCount += a.maxDashCount;
	result.maxSatiety += a.maxSatiety;
	result.power += a.power;
	result.minDamage += a.minDamage;
	result.maxDamage += a.maxDamage;
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
	case STAT_TYPE::MIN_DAMAGE:
		return minDamage;
	case STAT_TYPE::MAX_DAMAGE:
		return maxDamage;
	case STAT_TYPE::MAX_HP:
		return maxHp;
	case STAT_TYPE::MAX_JUMP_COUNT:
		return maxJumpCount;
	case STAT_TYPE::MAX_DASH_COUNT:
		return maxDashCount;
	case STAT_TYPE::MAX_SATIETY:
		return maxSatiety;
	case STAT_TYPE::CURR_HP:
		return currHp;
	case STAT_TYPE::CURR_SATIETY:
		return currSatiety;
	}
}

string PlayerStat::getStatString(STAT_TYPE type, bool isEnglish)
{
	switch (type)
	{
	case STAT_TYPE::POW:
		if(isEnglish) return "UI/STAT/POW";
		else return "위력";
	case STAT_TYPE::DEF:
		if (isEnglish) return "UI/STAT/DEF";
		else return "방어력";
	case STAT_TYPE::TOUGH:
		if (isEnglish) return "UI/STAT/TOUGH";
		else return "강인함";
	case STAT_TYPE::BLOCK:
		if (isEnglish) return "UI/STAT/BLOCK";
		else return "막기";
	case STAT_TYPE::CRITICAL:
		if (isEnglish) return "UI/STAT/CRITICAL";
		else return "크리티컬 확률";
	case STAT_TYPE::CRITICAL_DAMAGE:
		if (isEnglish) return "UI/STAT/CRITICAL_DAMAGE";
		else return "크리티컬 데미지";
	case STAT_TYPE::EVADE:
		if (isEnglish) return "UI/STAT/EVADE";
		else return "회피";
	case STAT_TYPE::MOVE_SPEED:
		if (isEnglish) return "UI/STAT/MOVE_SPEED";
		else return "이동속도";
	case STAT_TYPE::ATTACK_SPEED:
		if (isEnglish) return "UI/STAT/ATTACK_SPEED";
		else return "공격속도";
	case STAT_TYPE::RELOAD:
		if (isEnglish) return "UI/STAT/RELOAD";
		else return "재장전속도";
	case STAT_TYPE::DASH_DAMAGE:
		if (isEnglish) return "UI/STAT/DASH_DAMAGE";
		else return "대쉬 공격력";
	case STAT_TYPE::TRUE_DAMAGE:
		if (isEnglish) return "UI/STAT/TRUE_DAMAGE";
		else return "고정 데미지";
	case STAT_TYPE::MAX_HP:
		return "최대 체력";
	case STAT_TYPE::MAX_JUMP_COUNT:
		return "최대 점프횟수";
	case STAT_TYPE::MAX_DASH_COUNT:
		return "최대 대쉬횟수";
	case STAT_TYPE::MAX_SATIETY:
		return "최대 포만감"; 
	}
}

string PlayerStat::getStatInfo(STAT_TYPE type)
{
	switch (type)
	{
	case STAT_TYPE::POW:
		return "위력은 무기공격력을 기반으로 추가피해량에 영향을 줍니다.";
	case STAT_TYPE::DEF:
		return "받는 피해를 경감시켜줍니다.";
	case STAT_TYPE::TOUGH:
		return "강인함 수치에 따라 고정값의 피해를 경감시켜줍니다.";
	case STAT_TYPE::BLOCK:
		return "적의 공격을 막을 수 있는 확률을 증가시킵니다.";
	case STAT_TYPE::CRITICAL:
		return "적에게 치명적인 피해를 입힐 수 있는 기회가 늘어납니다.";
	case STAT_TYPE::CRITICAL_DAMAGE:
		return "크리티컬 추가 피해량을 나타냅니다.";
	case STAT_TYPE::EVADE:
		return "적의 공격을 회피할 수 있는 확률을 증가시킵니다.";
	case STAT_TYPE::MOVE_SPEED:
		return "더 빠르게 움직이게 해줍니다.";
	case STAT_TYPE::ATTACK_SPEED:
		return "더 빠르게 공격할 수 있게 해줍니다.";
	case STAT_TYPE::RELOAD:
		return "더 빠르게 재장전할 수 있게 해줍니다.";
	case STAT_TYPE::DASH_DAMAGE:
		return "대쉬 공격력은 무기 공격력의 %로 계산됩니다.";
	case STAT_TYPE::TRUE_DAMAGE:
		return "적의 방어력 등을 무시하고 고정된 피해를 입힙니다.";
	}
}
