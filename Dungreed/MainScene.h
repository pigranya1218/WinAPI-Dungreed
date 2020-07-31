#pragma once
#include "gameNode.h"

class MainScene : public GameNode
{
private:
	Image* _birdImage;
	Animation* _ani;

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����
};

