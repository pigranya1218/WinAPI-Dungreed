#pragma once
#include <set>

class AttackInfo
{
public:
	size_t attackID; // 어택 아이디, 공격에 대한 중복검사 판별을 위해서 사용
	set<string> _usedItem; // 이것에 반영된 아이템 코드들

	OBJECT_TEAM team; // 공격한 팀
	float minDamage; // 최소 대미지
	float maxDamage; // 최대 대미지
	int critical; // 크리티컬 확률
	int criticalDamage; // 크리티컬 추가대미지
	float knockBack; // 넉백 (밀어내는 힘)
};

