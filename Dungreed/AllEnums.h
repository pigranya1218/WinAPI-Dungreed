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

enum class ENEMY_TYPE : unsigned int
{
	BANSHEE,			// 수녀
	BAT_BOMB,			// 박쥐 자폭
	BAT_RED,			// 박쥐 빨강
	BAT_NORMAL,			// 박쥐 기본
	BAT_ICE,			// 박쥐 얼음
	BAT_GIANT_RED,		// 박쥐 거대 빨강
	BAT_GIANT_NORMAL,	// 박쥐 거대 기본
	GHOST,				// 유령
	LILITH,				// 서큐버스
	SKEL_BIG_NORMAL,	// 해골기사 기본
	SKEL_BIG_ICE,		// 해골기사 얼음
	SKEL_DOG,			// 해골강아지
	SKEL_MAGICIAN_ICE	// 해골마법사 얼음
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

enum class KEY_TYPE
{
	MOVE_UP = 0, // 위로 이동
	MOVE_DOWN, // 아래로 이동
	MOVE_LEFT, // 왼쪽으로 이동
	MOVE_RIGHT, // 오른쪽으로 이동
	ATTACK, // 공격 
	MAIN_SKILL, // 스킬
	SUB_SKILL, // 보조스킬
	DASH, // 대쉬
	RELOAD, // 재장전
	INVENTORY, // 캐릭터 인벤토리
	MAP, // 지도 열기
	STAT, // 캐릭터 능력치
	INTERACTION // 상호작용
};

enum class SOUND_TYPE
{
	BGM, // 배경음
	EFFECT // 효과음
};
