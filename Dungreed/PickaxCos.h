#pragma once
#include "Costume.h"

class PickaxCos : public Costume
{
private:

public:
	virtual void init() override;
	virtual void release() override;
	virtual void update(float elaspedTime) override;
	virtual void render(Vector2 pos, DIRECTION dir, PLAYER_ANIMATION state) override;
	virtual void setAni(PLAYER_ANIMATION aniState) override;	// �ִϸ��̼��� �����ų �Լ�
	//getter
	virtual PlayerStat getBaseStat() override; // �ڽ�Ƭ�� �⺻ ������ ��ȯ
};

