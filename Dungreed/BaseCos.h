#pragma once
#include "Costume.h"

class BaseCos : public Costume
{
private:

public:
	virtual void init() override;
	virtual void release() override;
	virtual void update(float elaspedTime) override;
	virtual void render(Vector2 pos, DIRECTION dir) override;
	virtual void setSprite(PLAYER_STATE state, bool isForced) override;	// 애니메이션을 재생시킬 함수
};

