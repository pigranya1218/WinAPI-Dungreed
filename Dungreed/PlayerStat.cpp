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
		else return "����";
	case STAT_TYPE::DEF:
		if (isEnglish) return "UI/STAT/DEF";
		else return "����";
	case STAT_TYPE::TOUGH:
		if (isEnglish) return "UI/STAT/TOUGH";
		else return "������";
	case STAT_TYPE::BLOCK:
		if (isEnglish) return "UI/STAT/BLOCK";
		else return "����";
	case STAT_TYPE::CRITICAL:
		if (isEnglish) return "UI/STAT/CRITICAL";
		else return "ũ��Ƽ�� Ȯ��";
	case STAT_TYPE::CRITICAL_DAMAGE:
		if (isEnglish) return "UI/STAT/CRITICAL_DAMAGE";
		else return "ũ��Ƽ�� ������";
	case STAT_TYPE::EVADE:
		if (isEnglish) return "UI/STAT/EVADE";
		else return "ȸ��";
	case STAT_TYPE::MOVE_SPEED:
		if (isEnglish) return "UI/STAT/MOVE_SPEED";
		else return "�̵��ӵ�";
	case STAT_TYPE::ATTACK_SPEED:
		if (isEnglish) return "UI/STAT/ATTACK_SPEED";
		else return "���ݼӵ�";
	case STAT_TYPE::RELOAD:
		if (isEnglish) return "UI/STAT/RELOAD";
		else return "�������ӵ�";
	case STAT_TYPE::DASH_DAMAGE:
		if (isEnglish) return "UI/STAT/DASH_DAMAGE";
		else return "�뽬 ���ݷ�";
	case STAT_TYPE::TRUE_DAMAGE:
		if (isEnglish) return "UI/STAT/TRUE_DAMAGE";
		else return "���� ������";
	case STAT_TYPE::MAX_HP:
		return "�ִ� ü��";
	case STAT_TYPE::MAX_JUMP_COUNT:
		return "�ִ� ����Ƚ��";
	case STAT_TYPE::MAX_DASH_COUNT:
		return "�ִ� �뽬Ƚ��";
	case STAT_TYPE::MAX_SATIETY:
		return "�ִ� ������"; 
	}
}

string PlayerStat::getStatInfo(STAT_TYPE type)
{
	switch (type)
	{
	case STAT_TYPE::POW:
		return "������ ������ݷ��� ������� �߰����ط��� ������ �ݴϴ�.";
	case STAT_TYPE::DEF:
		return "�޴� ���ظ� �氨�����ݴϴ�.";
	case STAT_TYPE::TOUGH:
		return "������ ��ġ�� ���� �������� ���ظ� �氨�����ݴϴ�.";
	case STAT_TYPE::BLOCK:
		return "���� ������ ���� �� �ִ� Ȯ���� ������ŵ�ϴ�.";
	case STAT_TYPE::CRITICAL:
		return "������ ġ������ ���ظ� ���� �� �ִ� ��ȸ�� �þ�ϴ�.";
	case STAT_TYPE::CRITICAL_DAMAGE:
		return "ũ��Ƽ�� �߰� ���ط��� ��Ÿ���ϴ�.";
	case STAT_TYPE::EVADE:
		return "���� ������ ȸ���� �� �ִ� Ȯ���� ������ŵ�ϴ�.";
	case STAT_TYPE::MOVE_SPEED:
		return "�� ������ �����̰� ���ݴϴ�.";
	case STAT_TYPE::ATTACK_SPEED:
		return "�� ������ ������ �� �ְ� ���ݴϴ�.";
	case STAT_TYPE::RELOAD:
		return "�� ������ �������� �� �ְ� ���ݴϴ�.";
	case STAT_TYPE::DASH_DAMAGE:
		return "�뽬 ���ݷ��� ���� ���ݷ��� %�� ���˴ϴ�.";
	case STAT_TYPE::TRUE_DAMAGE:
		return "���� ���� ���� �����ϰ� ������ ���ظ� �����ϴ�.";
	}
}
