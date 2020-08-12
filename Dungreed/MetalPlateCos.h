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
	virtual void setAni(PLAYER_ANIMATION aniState) override;	// �ִϸ��̼��� �����ų �Լ�
	virtual PlayerStat getBaseStat() override; // �ڽ�Ƭ�� �⺻ ������ ��ȯ
};

