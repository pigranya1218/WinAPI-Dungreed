#pragma once
#include "DamageInfo.h"
//#include <set>

class AttackInfo
{
public:
	size_t attackID; // 어택 아이디, 공격에 대한 중복검사 판별을 위해서 사용
	//set<int> _usedItem; // 이것에 반영된 아이템 코드들

	OBJECT_TEAM team; // 공격한 팀
	float minDamage = 0; // 최소 대미지
	float maxDamage = 0; // 최대 대미지
	float trueDamage = 0; // 트루 대미지
	int critical = 0; // 크리티컬 확률 (critical%)
	int criticalDamage = 0; // 크리티컬 추가대미지 ((100 + criticalDamage)%)
	float knockBack = 0; // 넉백 (밀어내는 힘)

public:
	//~AttackInfo() {/* if (!_usedItem.empty()) { _usedItem.clear(); } */}
	DamageInfo getDamageInfo();
};

