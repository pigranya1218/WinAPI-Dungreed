#pragma once
#include "GameNode.h"

class GameScene : public GameNode
{
private:
	float _timeSpeed; // �ð� ���, 1 = �⺻ �ӵ�


public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����

	// �÷��̾� ���� �Լ�



	// �������� ���� �Լ�



	// UI ���� �Լ�



};

