#pragma once
#include "GameNode.h"

class SampleStage;

class SecondTestScene :public GameNode
{
private:
	SampleStage* _stage;

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����
};

