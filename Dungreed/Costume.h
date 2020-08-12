#pragma once
#include "stdafx.h"
#include "PlayerStat.h"
#include "Player.h"

enum class COSTUME_TYPE
{
	DEFAULT = 0,
	METAL_PLATE,
	PICKAX
};

enum class PLAYER_ANIMATION;

class Costume
{
protected:
	Image* _img;
	Image* _idle;
	Image* _move;
	Image* _jump;
	Image* _die;

	Animation* _ani;
	
	PlayerStat _baseStat;

	PLAYER_ANIMATION _aniState;

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(float elaspedTime) = 0;
	virtual void render(Vector2 pos, DIRECTION dir, PLAYER_ANIMATION state) = 0;
	virtual void setAni(PLAYER_ANIMATION aniState) = 0;	// 애니메이션을 재생시킬 함수
	virtual PlayerStat getBaseStat() = 0; // 코스튬의 기본 스탯을 반환
};

