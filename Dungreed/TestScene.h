#pragma once
#include "stdafx.h"
#include "gameNode.h"


struct tagTestPlayer
{
	float x, y;
	FloatRect rc;


};

class TestScene : public GameNode
{

	

private:








public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����
	
};

