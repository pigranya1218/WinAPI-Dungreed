#pragma once
#include "Costume.h"

class MetalPlateCos : public Costume
{
private:

public:
	virtual void init() override;
	virtual void release() override;
	virtual void update(float elaspedTime) override;
	virtual void render(Vector2 pos, DIRECTION dir, PLAYER_ANIMATION state) override;
	virtual void setAni(PLAYER_ANIMATION aniState) override;	// 애니메이션을 재생시킬 함수
	virtual PlayerStat getBaseStat() override; // 코스튬의 기본 스탯을 반환
};

