#pragma once

enum class DEBUG_TYPE : unsigned int
{
	END
};

enum class OBJECT_TEAM : unsigned int
{
	PLAYER,
	ENEMY
};

enum class DIRECTION : unsigned int
{
	LEFT,
	RIGHT
};

enum class PIVOT : int
{
	LEFT_TOP, 
	CENTER, 
	BOTTOM
};

enum class ACTION_TYPE
{
	MOVE_UP = 0, // 위로 이동
	MOVE_DOWN, // 아래로 이동
	MOVE_LEFT, // 왼쪽으로 이동
	MOVE_RIGHT, // 오른쪽으로 이동
	JUMP, // 점프
	ATTACK, // 공격 
	MAIN_SKILL, // 스킬
	SUB_SKILL, // 보조스킬
	DASH, // 대쉬
	RELOAD, // 재장전
	INVENTORY, // 캐릭터 인벤토리
	MAP, // 지도 열기
	STAT, // 캐릭터 능력치
	INTERACTION, // 상호작용
	CHANGE_WEAPON, // 무기 교체
	END
};

enum class SOUND_TYPE
{
	BGM, // 배경음
	EFFECT // 효과음
};
