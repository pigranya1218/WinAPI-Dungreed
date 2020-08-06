#pragma once
#include "GameNode.h"

class Player;

class TestScene : public GameNode
{
private:
	Player* _player;

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����

	void setPlayer(Player* player) { _player = player; }
};

