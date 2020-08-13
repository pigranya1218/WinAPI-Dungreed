#pragma once
#include "PlayerStat.h"
#include "stdafx.h"

enum class COSTUME_TYPE : int
{
	BASE = 0,
	METAL_PLATE,
	PICKAX,
	ALICE,
	RED_LOTUS
};

enum class PLAYER_STATE : int
{
	IDLE = 0, // USE ANI
	MOVE, // USE ANI
	JUMP, // NO ANI
	DIE // NO ANI
};

class Costume
{
protected:
	string _costumeName; // 이미지를 찾기 위해 활용되는 코스튬별 이름

	PlayerStat _baseStat; // 각 코스튬별 기본 스탯

	Image* _img;
	Animation* _ani;
	PLAYER_STATE _imgState;

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(float elaspedTime) = 0;
	virtual void render(Vector2 pos, DIRECTION dir) = 0;
	virtual void setSprite(PLAYER_STATE state, bool isForced) = 0;	// 애니메이션을 재생시킬 함수
	
	PlayerStat const getBaseStat() { return _baseStat; } // 코스튬의 기본 스탯을 반환
};

