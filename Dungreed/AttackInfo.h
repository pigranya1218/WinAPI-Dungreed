#pragma once
class AttackInfo
{
public:
	OBJECT_TEAM team; // 공격한 사람
	int attackID; // 어택 아이디, 공격에 대한 중복검사 판별을 위해서 사용
	float damage; // 대미지
	float knockBack; // 넉백 (밀어내는 힘)
};

